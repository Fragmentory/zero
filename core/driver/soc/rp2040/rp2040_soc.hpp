/**
 * \file rp2040_soc.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "board_defines.hpp"
#include "component_interface.hpp"
#include "rp2040_gpio.hpp"
#include "rp2040_pwm.hpp"
#include "rp2040_stopwatch.hpp"
#include "rp2040_temperature.hpp"
#include "rp2040_ticker.hpp"
#include "rp2040_watchdog.hpp"

#include <cstdint>

namespace core
{
    namespace soc
    {
        using DIRECTION = core::board::DIRECTION;
        using VALUE = core::board::VALUE;

        struct RP2040 : public pulp::ComponentInterface
        {
            RP2040();
            virtual ~RP2040() {}

            virtual void initialize(void) override;
            virtual void shutdown(void) override;

            float get_temperature(void) const { return temperature.get_value(); }
            uint16_t get_temperature_raw(void) const { return temperature.get_raw_value(); }

            void ticker_set_callback(pulp::ticker::Callback &_handler) { ticker.set_callback(_handler); }
            uint32_t time_ms2tick(const float _time_ms) const { return ticker.time_ms2ticks(_time_ms); }

            uint64_t get_stopwatch(void) const { return stopwatch.get_value(); }

            void set_pwm_frequency(const uint32_t);
            void set_pwm_duty_cycle(const uint16_t);
            void pwm_enable();
            void pwm_disable();
            bool is_pwm_enabled() const;

            void perform();

            void i2c_scan();

            RP2040Gpio gpio;
            RP2040Pwm pwm;
            RP2040Ticker ticker;
            RP2040Stopwatch stopwatch;
            RP2040Temperature temperature;
            RP2040Watchdog watchdog;
        };
    }
}
