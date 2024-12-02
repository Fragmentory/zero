/**
 * \file visual_programmer_interface.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "visual_color.hpp"
#include "visual_smart_led.hpp"

#include <cstdint>

namespace core::driver::visual
{
    struct ExecutorInterface
    {
        virtual SmartLed &get_left() = 0;
        virtual SmartLed &get_right() = 0;
        virtual void color(const Color &_left, const Color &_right, const uint64_t _steps) = 0;
        virtual void draw() = 0;
    };
}
