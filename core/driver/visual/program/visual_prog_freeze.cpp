/**
 * \file visual_prog_freeze.cpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include "visual_prog_freeze.hpp"

#include "visual_smart_led.hpp"
#include "visual_variant.hpp"

namespace core::driver::visual
{
    namespace program::freeze
    {
        void Instance::start()
        {

            SmartLed &left = neopixel.get_left();
            SmartLed &right = neopixel.get_right();

            const uint8_t val_0 = static_cast<uint8_t>(left.current.value[0] / 2) + static_cast<uint8_t>(right.current.value[0] / 2);
            const uint8_t val_1 = static_cast<uint8_t>(left.current.value[1] / 2) + static_cast<uint8_t>(right.current.value[1] / 2);
            const uint8_t val_2 = static_cast<uint8_t>(left.current.value[2] / 2) + static_cast<uint8_t>(right.current.value[2] / 2);
            const uint8_t val_3 = static_cast<uint8_t>(left.current.value[3] / 2) + static_cast<uint8_t>(right.current.value[3] / 2);

            const Color mean{
                .value = {val_0, val_1, val_2, val_3}
            };

            neopixel.color(mean, mean, Variant::PROGRAM_FREEZE_TIMEOUT);
        }

        void Instance::step() { neopixel.draw(); }
    }
}