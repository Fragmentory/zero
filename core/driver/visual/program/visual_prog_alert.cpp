/**
 * \file visual_prog_alert.cpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include "visual_prog_alert.hpp"

#include "visual_smart_led.hpp"
#include "visual_variant.hpp"

namespace core::driver::visual
{
    namespace program::alert
    {
        void Instance::start() { neopixel.color(ALERT_TOP_COLOR, ALERT_LOW_COLOR, Variant::FLASH_ALERT_TIMEOUT); }

        void Instance::step()
        {
            neopixel.draw();

            SmartLed &left = neopixel.get_left();
            SmartLed &right = neopixel.get_right();

            if (left.is_stable() && right.is_stable())
            {
                if (right.current == ALERT_TOP_COLOR)
                {
                    static int status{0};
                    if (status++ < 3)
                    {
                        neopixel.color(COLOR_BLACK, COLOR_BLACK, 0);
                        neopixel.color(ALERT_LOW_COLOR, ALERT_TOP_COLOR, Variant::FLASH_ALERT_TIMEOUT);
                    }
                    else
                    {
                        status = 0;
                        neopixel.color(ALERT_TOP_COLOR, ALERT_LOW_COLOR, Variant::BLINK_ALERT_TIMEOUT);
                    }
                }
                else
                {
                    static int status{0};
                    if (status++ < 3)
                    {
                        neopixel.color(COLOR_BLACK, COLOR_BLACK, 0);
                        neopixel.color(ALERT_TOP_COLOR, ALERT_LOW_COLOR, Variant::FLASH_ALERT_TIMEOUT);
                    }
                    else
                    {
                        status = 0;
                        neopixel.color(ALERT_LOW_COLOR, ALERT_TOP_COLOR, Variant::BLINK_ALERT_TIMEOUT);
                    }
                }
            }
        }
    }
}