/**
 * \file visual_prog_active.cpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
*/

#include "visual_prog_active.hpp"

#include "visual_smart_led.hpp"
#include "visual_variant.hpp"

namespace core::driver::visual
{
    namespace program::active
    {
        void Instance::start() { neopixel.color(Variant::ACTIVE_BACKLIGHT_LEFT, Variant::ACTIVE_BACKLIGHT_RIGHT, Variant::FLASH_ACTIVE_TIMEOUT); }

        void Instance::step()
        {
            neopixel.draw();

            SmartLed &left = neopixel.get_left();
            SmartLed &right = neopixel.get_right();

            if (left.is_stable() && right.is_stable())
            {
                if (right.current == Variant::ACTIVE_BACKLIGHT_RIGHT)
                {
                    neopixel.color(Variant::ACTIVE_BACKLIGHT_RIGHT, Variant::ACTIVE_BACKLIGHT_RIGHT, Variant::BLINK_ACTIVE_TIMEOUT);
                }
                else
                {
                    neopixel.color(Variant::ACTIVE_BACKLIGHT_RIGHT, Variant::ACTIVE_BACKLIGHT_RIGHT, Variant::BLINK_ACTIVE_TIMEOUT);
                }
            }
        }
    }
}
