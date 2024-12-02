/**
 * \file event_scheduler.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "component_state.hpp"
#include "engine.hpp"
#include "event_bus.hpp"

#include <cassert>
#include <deque>
#include <iostream>
#include <memory>

namespace pulp
{
    namespace event
    {
        template <int32_t TICKER_DELAY_VALUE_US>
        struct Scheduler : public pulp::ComponentInterface
        {
            static const bool VERBOSITY_ON = false;

            static constexpr uint32_t TICKER_DELAY_US{TICKER_DELAY_VALUE_US >= 0 ? TICKER_DELAY_VALUE_US : -TICKER_DELAY_VALUE_US};
            static constexpr uint32_t TRIGGER_DELAY_MS{static_cast<uint32_t>(TICKER_DELAY_US * pulp::event::Perform::HEARTBEAT_COUNTER / 1000.0)};

            Scheduler(Bus &_event_bus) :
                event_bus(_event_bus)
            {
                event_bus.subscribe<pulp::event::Perform>([this](const pulp::event::Item &_event) { this->on_event(_event); });

                VERBOSITY_ON &&printf("TICKER_DELAY_US %d\n", TICKER_DELAY_US);
                VERBOSITY_ON &&printf("TRIGGER_DELAY_MS %d\n", TRIGGER_DELAY_MS);
            }

            virtual void initialize() override
            {
                assert(state == pulp::COMPONENT_STATE::UNDEFINED);
                state = pulp::COMPONENT_STATE::IDLE;
            }

            virtual void shutdown() override
            {
                assert(state != pulp::COMPONENT_STATE::UNDEFINED);
                state = pulp::COMPONENT_STATE::UNDEFINED;
                scheduled_events.clear();
            }

            template <typename T>
            void once(const uint32_t _delay_ms)
            {
                assert(state != pulp::COMPONENT_STATE::UNDEFINED);
                static_assert(std::is_base_of<Item, T>::value, "T must derive from Item");
                scheduled_events.emplace_back(_delay_ms, _delay_ms, std::make_shared<T>(), 1);
            }

            template <typename T>
            void start(const uint32_t _period_ms, const size_t _number = 0)
            {
                assert(state != pulp::COMPONENT_STATE::UNDEFINED);
                static_assert(std::is_base_of<Item, T>::value, "T must derive from Item");
                scheduled_events.emplace_back(_period_ms, 0, std::make_shared<T>(), _number);
            }

            template <typename T>
            void stop(const uint32_t _period_ms)
            {
                auto it = std::find_if(scheduled_events.begin(),
                                       scheduled_events.end(),
                                       [_period_ms](const ScheduledEvent &event)
                                       {
                                           VERBOSITY_ON &&printf("item: %lu %llu\n", event.period_ms, event.event);
                                           return event.period_ms == _period_ms && event.event != nullptr;
                                       });

                if (it != scheduled_events.end())
                {
                    it->number = 1;
                    it->remaining_number = 0;
                    it->remaining_time_ms = 0;

                    VERBOSITY_ON &&printf("found %lu\n", _period_ms);
                }
                else
                {
                    VERBOSITY_ON &&printf("not found %lu\n", _period_ms);
                }
            }

          private:
            struct ScheduledEvent
            {
                uint32_t period_ms;
                uint32_t remaining_time_ms;
                std::shared_ptr<Item> event;
                size_t number;
                size_t remaining_number;

                ScheduledEvent(const uint32_t _period_ms, const uint32_t _offset_ms, std::shared_ptr<Item> _event, const size_t _number) :
                    period_ms(_period_ms),
                    remaining_time_ms(_offset_ms),
                    event(_event),
                    number(_number),
                    remaining_number(_number)
                {
                    VERBOSITY_ON &&printf("%lu %lu %li\n", period_ms, remaining_time_ms, number);
                }
            };

            Bus &event_bus;
            std::deque<ScheduledEvent> scheduled_events; // ring buffer for planed events
            pulp::COMPONENT_STATE state{pulp::COMPONENT_STATE::UNDEFINED};

            void on_event(const pulp::event::Item &_event)
            {
                (void)_event;

                static uint32_t counter{0};

                for (auto &scheduled : scheduled_events)
                {
                    if (scheduled.remaining_time_ms > TRIGGER_DELAY_MS)
                    {
                        scheduled.remaining_time_ms -= TRIGGER_DELAY_MS;
                        VERBOSITY_ON &&printf("remaining time %lu\n", scheduled.remaining_time_ms);
                    }
                    else
                    {
                        scheduled.remaining_time_ms = 0;
                        VERBOSITY_ON &&printf("time over\n");
                    }

                    if (scheduled.remaining_time_ms <= 0)
                    {
                        if (scheduled.number == 0)
                        {
                            scheduled.event->tick = counter;
                            scheduled.remaining_time_ms = scheduled.period_ms;
                            event_bus.notify(*scheduled.event);
                        }
                        else
                        {
                            if (scheduled.remaining_number > 0)
                            {
                                scheduled.event->tick = counter;
                                scheduled.remaining_number--;
                                scheduled.remaining_time_ms = scheduled.period_ms;
                                event_bus.notify(*scheduled.event);
                            }
                        }
                    }
                }

                scheduled_events.erase(std::remove_if(scheduled_events.begin(),
                                                      scheduled_events.end(),
                                                      [](const ScheduledEvent &scheduled) { return scheduled.remaining_time_ms == 0; }),
                                       scheduled_events.end());

                counter++;
            }
        };
    }
}
