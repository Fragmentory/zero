/**
 * \file rp2040_pwm.cpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include "rp2040_pwm.hpp"

#include "component_state.hpp"
#include "soc_variant.hpp"

#include <assert.h>
#include <cstdint>
#include <hardware/clocks.h>
#include <hardware/pwm.h>
#include <pico/stdlib.h>

namespace core
{
    namespace soc
    {
        pulp::COMPONENT_STATE state = pulp::COMPONENT_STATE::UNDEFINED;

        void RP2040Pwm::initialize()
        {
            assert(state == pulp::COMPONENT_STATE::UNDEFINED);
            state = pulp::COMPONENT_STATE::IDLE;

            gpio_set_function(soc::Variant::SOUND_PIN, GPIO_FUNC_PWM);
            const uint slice_num = pwm_gpio_to_slice_num(soc::Variant::SOUND_PIN);
            pwm_set_wrap(slice_num, 65535);
            pwm_set_enabled(slice_num, true);
        }

        void RP2040Pwm::shutdown()
        {
            assert(state != pulp::COMPONENT_STATE::UNDEFINED);
            state = pulp::COMPONENT_STATE::UNDEFINED;
        }

        void RP2040Pwm::set_pwm_frequency(const uint32_t _frequency)
        {
            assert(state == pulp::COMPONENT_STATE::IDLE);

            uint slice_num = pwm_gpio_to_slice_num(soc::Variant::SOUND_PIN);
            float clock_divider = (float)clock_get_hz(clk_sys) / (static_cast<float>(_frequency) * 65536.0f);
            pwm_set_clkdiv(slice_num, clock_divider);
        }

        void RP2040Pwm::set_pwm_duty_cycle(const uint16_t _duty_cycle)
        {
            assert(state == pulp::COMPONENT_STATE::IDLE);

            pwm_set_gpio_level(soc::Variant::SOUND_PIN, _duty_cycle);
        }

        void RP2040Pwm::enable()
        {
            assert(state == pulp::COMPONENT_STATE::IDLE);
            state = pulp::COMPONENT_STATE::ACTIVE;

            uint slice_num = pwm_gpio_to_slice_num(soc::Variant::SOUND_PIN);
            pwm_set_enabled(slice_num, true);
        }

        void RP2040Pwm::disable()
        {
            assert(state == pulp::COMPONENT_STATE::ACTIVE);
            state = pulp::COMPONENT_STATE::IDLE;

            uint slice_num = pwm_gpio_to_slice_num(soc::Variant::SOUND_PIN);
            pwm_set_enabled(slice_num, false);
        }

        bool RP2040Pwm::is_enabled() const { return (state == pulp::COMPONENT_STATE::ACTIVE) ? true : false; }
    }
}
