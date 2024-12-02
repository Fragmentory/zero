/**
 * \file visual_prog_idle.cpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include "visual_prog_idle.hpp"

#include "visual_smart_led.hpp"

namespace core::driver::visual
{
    namespace program::idle
    {
        static const Color sequence_left[] = {
            visual::COLOR_RED_X,
            visual::COLOR_YELLOW,
            visual::COLOR_GREEN_X,
            visual::COLOR_CYAN,
            visual::COLOR_BLUE_X,
            visual::COLOR_MAGENTA,
        };
        static const Color sequence_right[] = {
            visual::COLOR_BLUE_X,
            visual::COLOR_MAGENTA,
            visual::COLOR_RED_X,
            visual::COLOR_YELLOW,
            visual::COLOR_GREEN_X,
            visual::COLOR_CYAN,
        };

        static constexpr size_t SEQUENCE_SIZE = sizeof(sequence_left) / sizeof(Color);
        static constexpr uint64_t STEPS = 100;

        void Instance::start()
        {
            identifier = 0;
            neopixel.color(sequence_left[identifier], sequence_right[identifier], STEPS);
        }

        void Instance::step()
        {
            neopixel.draw();

            SmartLed &left = neopixel.get_left();
            SmartLed &right = neopixel.get_right();

            if (left.is_stable() && right.is_stable())
            {
                identifier = ((identifier + 1) < SEQUENCE_SIZE) ? identifier + 1 : 0;
                neopixel.color(sequence_left[identifier], sequence_right[identifier], STEPS);
            }
        }
    }
}
