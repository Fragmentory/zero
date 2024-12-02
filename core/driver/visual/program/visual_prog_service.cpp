/**
 * \file visual_prog_service.cpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include "visual_prog_service.hpp"

#include "visual_smart_led.hpp"
#include "visual_variant.hpp"

namespace core::driver::visual
{
    namespace program::service
    {
        void Instance::start()
        {
            neopixel.color(UPDATE_LOW_COLOR, UPDATE_LOW_COLOR, 0);
            neopixel.color(UPDATE_TOP_COLOR, UPDATE_TOP_COLOR, Variant::BLINK_UPDATE_TIMEOUT);
        }

        void Instance::step()
        {
            SmartLed &left = neopixel.get_left();
            SmartLed &right = neopixel.get_right();

            if (left.is_stable() && right.is_stable())
            {
                if (right.current == UPDATE_TOP_COLOR)
                {
                    static int status{0};
                    if (status++ < 3)
                    {
                        neopixel.color(COLOR_BLACK, COLOR_BLACK, 0);
                        neopixel.color(UPDATE_TOP_COLOR, UPDATE_TOP_COLOR, Variant::FLASH_UPDATE_TIMEOUT);
                    }
                    else
                    {
                        status = 0;
                        neopixel.color(UPDATE_LOW_COLOR, UPDATE_LOW_COLOR, Variant::BLINK_UPDATE_TIMEOUT);
                    }
                }
                else
                {
                    neopixel.color(UPDATE_TOP_COLOR, UPDATE_TOP_COLOR, Variant::BLINK_UPDATE_TIMEOUT);
                }
            }
            neopixel.draw();
        }
    }
}