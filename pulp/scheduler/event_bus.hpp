/**
 * \file component_state.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "component_interface.hpp"
#include "component_state.hpp"

#include <cassert>
#include <cstdint>
#include <cstdio>
#include <functional>
#include <memory>
#include <pico/time.h>
#include <type_traits>
#include <unordered_map>
#include <vector>

namespace pulp
{
    namespace event
    {
        struct Item
        {
            virtual ~Item() = default;
            virtual std::uint64_t type() const = 0;
            uint32_t tick{0};
        };

        template <typename T>
        struct Type : public Item
        {
            static std::uint64_t typeId()
            {
                static std::uint64_t id = reinterpret_cast<std::uint64_t>(&typeId);
                return id;
            }

            std::uint64_t type() const override { return typeId(); }
        };

        /*
            Event example:

            class ReadyEvent  : public Type<ReadyEvent> {};
            class AlertEvent  : public Type<AlertEvent> {};
            class CustomEvent : public Type<CustomEvent> {};
        */

        struct Bus : public pulp::ComponentInterface
        {
            using Handler = std::function<void(const Item &)>;

            static const bool VERBOSITY_ON = false;

            Bus() {}
            virtual ~Bus() = default;

            virtual void initialize() override
            {
                assert(state == pulp::COMPONENT_STATE::UNDEFINED);
                state = pulp::COMPONENT_STATE::IDLE;
            }

            virtual void shutdown() override
            {
                assert(state != pulp::COMPONENT_STATE::UNDEFINED);
                state = pulp::COMPONENT_STATE::UNDEFINED;
            }

            template <typename T>
            void subscribe(Handler handler)
            {
                static_assert(std::is_base_of<Item, T>::value, "T must derive from Item");
                handlers[T::typeId()].push_back(handler);

                VERBOSITY_ON &&printf("subscribe %llu %08x\n", T::typeId(), handler);
            }

            void notify(const Item &event)
            {
                assert(state != pulp::COMPONENT_STATE::UNDEFINED);

                /*
                    Attention: cyclic notification cascade possible.
                    todo:
                    1. store not std::function instance; better struct{std::function, bool}
                    2. mark call on invocation
                    3. not allow the same call: programmer fault
                 */
                auto it = handlers.find(event.type());
                if (it != handlers.end())
                {
                    for (const auto &handler : it->second)
                    {
                        VERBOSITY_ON &&printf("notify %llu %08x\n", event.type(), handler);
                        handler(event);
                    }
                }
            }

          private:
            std::unordered_map<std::uint64_t, std::vector<Handler>> handlers;
            pulp::COMPONENT_STATE state{pulp::COMPONENT_STATE::UNDEFINED};
        };

        /*
            How to use:

            eventBus.subscribe<ReadyEvent>([](const pulp::event::Item& event) { onReady(); });

            eventBus.notify(ReadyEvent());
        */
    }
}
