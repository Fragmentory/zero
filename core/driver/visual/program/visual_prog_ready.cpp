/**
 * \file visual_prog_ready.cpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include "visual_prog_ready.hpp"

#include "visual_smart_led.hpp"
#include "visual_variant.hpp"

namespace core::driver::visual
{
    namespace program::ready
    {
        void Instance::start()
        {
            neopixel.color(READY_LOW_COLOR, READY_LOW_COLOR, 0);
            neopixel.color(READY_TOP_COLOR, READY_TOP_COLOR, Variant::BLINK_READY_UP_TIMEOUT);
        }

        void Instance::step()
        {
            SmartLed &left = neopixel.get_left();
            SmartLed &right = neopixel.get_right();

            if (left.is_stable() && right.is_stable())
            {
                if (right.current == READY_TOP_COLOR)
                {
                    static int status{0};
                    if (status++ < 1)
                    {
                        neopixel.color(COLOR_BLACK, COLOR_BLACK, 0);
                        neopixel.color(READY_TOP_COLOR, READY_TOP_COLOR, Variant::FLASH_READY_TIMEOUT);
                    }
                    else
                    {
                        status = 0;
                        neopixel.color(READY_LOW_COLOR, READY_LOW_COLOR, Variant::BLINK_READY_DOWN_TIMEOUT);
                    }
                }
                else
                {
                    neopixel.color(READY_TOP_COLOR, READY_TOP_COLOR, Variant::BLINK_READY_UP_TIMEOUT);
                }
            }
            neopixel.draw();
        }
    }
}