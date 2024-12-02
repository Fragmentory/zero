/**
 * \file visual_prog_off.cpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include "visual_prog_off.hpp"

#include "visual_smart_led.hpp"
#include "visual_variant.hpp"

namespace core::driver::visual
{
    namespace program::off
    {
        void Instance::start()
        {
            SmartLed &left = neopixel.get_left();
            SmartLed &right = neopixel.get_right();
            neopixel.color(left.current, right.current, Variant::PROGRAM_OFF_TIMEOUT);
        }

        void Instance::step()
        {
            SmartLed &left = neopixel.get_left();
            SmartLed &right = neopixel.get_right();

            if (left.is_stable() && right.is_stable())
            {
                static bool started{false};
                if (!started)
                {
                    started = true;
                    neopixel.color(COLOR_BLACK, COLOR_BLACK, Variant::PROGRAM_OFF_TIMEOUT);
                }
            }

            neopixel.draw();
        }
    }
}