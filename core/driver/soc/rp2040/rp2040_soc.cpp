/**
 * \file rp2040_soc.cpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include "rp2040_soc.hpp"

#include "chunk.h"
#include "soc_variant.hpp"

#include <hardware/gpio.h>
#include <hardware/i2c.h>
#include <hardware/spi.h>
#include <pico/assert.h>
#include <pico/binary_info.h>
#include <pico/stdlib.h>
#include <stdint.h>

namespace core
{
    namespace soc
    {
        static absolute_time_t time_reference;

        RP2040::RP2040() :
            stopwatch(time_reference)
        {
        }

        void RP2040::initialize()
        {
            ticker.initialize();
            watchdog.initialize();
            watchdog.start();
            pwm.initialize();
            gpio.initialize();
            stopwatch.initialize();
            temperature.initialize();
        }

        void RP2040::shutdown()
        {
            temperature.shutdown();
            gpio.shutdown();
            pwm.shutdown();
            ticker.shutdown();
            stopwatch.shutdown();
            watchdog.shutdown();

            // watchdog.reboot();
        }

        void RP2040::set_pwm_frequency(const uint32_t _value) { pwm.set_pwm_frequency(_value); }

        void RP2040::set_pwm_duty_cycle(const uint16_t _value) { pwm.set_pwm_duty_cycle(_value); }

        void RP2040::pwm_enable()
        {
            if (!pwm.is_enabled())
                pwm.enable();
        }

        void RP2040::pwm_disable()
        {
            if (pwm.is_enabled())
                pwm.disable();
        }

        bool RP2040::is_pwm_enabled() const { return pwm.is_enabled(); }

        void RP2040::perform() { watchdog.update(); }

        static bool scan_over_i2c(chunk_t *const _result);

        void RP2040::i2c_scan(void)
        {
            uint8_t devices_space[3];
            chunk_t devices = {devices_space, 3};
            while (!scan_over_i2c(&devices))
                ;
        }

        static bool scan_over_i2c(chunk_t *const _result)
        {
            bool found_flag = false;
            uint8_t result_address = 0;
            for (size_t i = 0; i < _result->size; ++i)
            {
                _result->space[i] = 0;
            }

            for (uint8_t addr = 0; addr < (1 << 7); ++addr)
            {
                // Skip over any reserved addresses.
                int ret;
                if ((addr & 0x78) == 0 || (addr & 0x78) == 0x78)
                {
                    ret = PICO_ERROR_GENERIC;
                }
                else
                {
                    uint8_t buffer;
                    ret = i2c_read_blocking(i2c_default, addr, &buffer, 1, false);
                    if (ret > 0)
                    {
                        found_flag = true;
                        if (result_address < _result->size)
                        {
                            _result->space[result_address++] = addr;
                        }
                    }
                }
            }

            return found_flag;
        }
    }
}
