/**
 * \file visual_color_defines.hpp
 * \author Roman Koch koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "visual_color.hpp"

namespace core::driver::visual
{
    static const Color COLOR_BLACK{
        .rgbw = {.r = 0, .g = 0, .b = 0, .w = 0}
    };
    static const Color COLOR_WHITE{
        .rgbw = {.r = 0xff, .g = 0xff, .b = 0xff, .w = 0x0f}
    };
    static const Color COLOR_RED{
        .rgbw = {.r = 0xff, .g = 0x00, .b = 0x00, .w = 0x0f}
    };
    static const Color COLOR_RED_X{
        .rgbw = {.r = 0xff, .g = 0x0f, .b = 0x0f, .w = 0x0f}
    };
    static const Color COLOR_YELLOW{
        .rgbw = {.r = 0xff, .g = 0xff, .b = 0x00, .w = 0x0f}
    };
    static const Color COLOR_GREEN{
        .rgbw = {.r = 0x00, .g = 0xff, .b = 0x00, .w = 0x0f}
    };
    static const Color COLOR_GREEN_X{
        .rgbw = {.r = 0x0f, .g = 0xff, .b = 0x0f, .w = 0x0f}
    };
    static const Color COLOR_CYAN{
        .rgbw = {.r = 0x00, .g = 0xff, .b = 0xff, .w = 0x0f}
    };
    static const Color COLOR_BLUE{
        .rgbw = {.r = 0x00, .g = 0x00, .b = 0xff, .w = 0x0f}
    };
    static const Color COLOR_BLUE_X{
        .rgbw = {.r = 0x0f, .g = 0x0f, .b = 0xff, .w = 0x0f}
    };
    static const Color COLOR_MAGENTA{
        .rgbw = {.r = 0xff, .g = 0x00, .b = 0xff, .w = 0x0f}
    };
    static const Color COLOR_RED_DARK{
        .rgbw = {.r = 0xff, .g = 0x00, .b = 0x00, .w = 0x00}
    };
    static const Color COLOR_YELLOW_DARK{
        .rgbw = {.r = 0xff, .g = 0xff, .b = 0x00, .w = 0x00}
    };
    static const Color COLOR_GREEN_DARK{
        .rgbw = {.r = 0x00, .g = 0xff, .b = 0x00, .w = 0x00}
    };
    static const Color COLOR_CYAN_DARK{
        .rgbw = {.r = 0x00, .g = 0xff, .b = 0xff, .w = 0x00}
    };
    static const Color COLOR_BLUE_DARK{
        .rgbw = {.r = 0x00, .g = 0x00, .b = 0xff, .w = 0x00}
    };
    static const Color COLOR_MAGENTA_DARK{
        .rgbw = {.r = 0xff, .g = 0x00, .b = 0xff, .w = 0x00}
    };

    static const Color ALERT_TOP_COLOR{
        .rgbw = {.r = 0xff, .g = 0x01, .b = 0, .w = 0x0f}
    };
    static const Color ALERT_LOW_COLOR{
        .rgbw = {.r = 0x07, .g = 0x01, .b = 0, .w = 0x03}
    };

    static const Color READY_TOP_COLOR{
        .rgbw = {.r = 0xff, .g = 0xff, .b = 0, .w = 0x0f}
    };
    static const Color READY_LOW_COLOR{
        .rgbw = {.r = 0x05, .g = 0x05, .b = 0, .w = 0x03}
    };

    static const Color UPDATE_TOP_COLOR = {
        .rgbw = {.r = 0xff, .g = 0x6f, .b = 0x00, .w = 0x0f}
    };
    static const Color UPDATE_LOW_COLOR = {
        .rgbw = {.r = 0x05, .g = 0x02, .b = 0x00, .w = 0x03}
    };

    static constexpr Color HOT_COLOR = {
        .rgbw = {.r = 0x7f, .g = 0x05, .b = 0x00, .w = 0x0f}
    };
    static constexpr Color COLD_COLOR = {
        .rgbw = {.r = 0x00, .g = 0x05, .b = 0xff, .w = 0x03}
    };
}