/**
 * \file rp2040_gpio.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
    \brief Handle gpio

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#pragma once

#include "board_defines.hpp"
#include "component_interface.hpp"
#include "instance_array.hpp"

#include <stdint.h>

namespace core
{
    namespace soc
    {
        struct RP2040Gpio : public pulp::ComponentInterface
        {
            virtual ~RP2040Gpio() {}

            virtual void initialize(void) override;
            virtual void shutdown(void) override;

            void enable_event(core::board::callback_t);
            void disable_event(void);

            core::board::DIRECTION get_direction(const uint8_t) const;
            void set_direction(const uint8_t, const core::board::DIRECTION);

            void set_pulls(const uint8_t, const bool, const bool);

            core::board::VALUE get_value(const uint8_t) const;
            void set_value(const uint8_t, const core::board::VALUE) const;

            pulp::InstanceArray<uint8_t, 2> gpio_instance;
        };
    }
}
