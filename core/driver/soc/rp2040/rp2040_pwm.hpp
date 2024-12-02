/**
 * \file rp2040_pwm.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "component_interface.hpp"

#include <cstdint>

namespace core
{
    namespace soc
    {
        struct RP2040Pwm : public pulp::ComponentInterface
        {
            virtual ~RP2040Pwm() {}

            virtual void initialize(void) override;
            virtual void shutdown(void) override;

            void set_pwm_frequency(const uint32_t frequency);
            void set_pwm_duty_cycle(const uint16_t duty_cycle);

            void enable();
            void disable();
            bool is_enabled() const;
        };
    }
}
