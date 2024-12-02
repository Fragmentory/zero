/**
 * \file visual_color.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <cstdint>
#include <iomanip>

namespace core::driver
{
    namespace visual
    {
        namespace rgb
        {
            union Color
            {
                uint8_t value[3];
                struct
                {
                    uint8_t r;
                    uint8_t g;
                    uint8_t b;
                } rgb;
            };
        }

        namespace rgbw
        {
            union Color
            {
                uint8_t value[4];
                struct
                {
                    uint8_t r;
                    uint8_t g;
                    uint8_t b;
                    uint8_t w;
                } rgbw;
            };

        }

        using Color = rgbw::Color;

        static bool operator==(const visual::Color &left, const visual::Color &right)
        {
            if ((left.value[0] == right.value[0]) && (left.value[1] == right.value[1]) && (left.value[2] == right.value[2])
                && (left.value[3] == right.value[3]))
            {
                return true;
            }

            return false;
        }

        static bool operator!=(const visual::Color &left, const visual::Color &right)
        {
            if ((left.value[0] != right.value[0]) || (left.value[1] != right.value[1]) || (left.value[2] != right.value[2])
                || (left.value[3] != right.value[3]))
            {
                return true;
            }

            return false;
        }
    }
}

static std::ostream &operator<<(std::ostream &os, const core::driver::visual::Color &_color)
{
    os << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(_color.rgbw.r) << " ";
    os << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(_color.rgbw.g) << " ";
    os << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(_color.rgbw.b) << " ";
    os << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(_color.rgbw.w) << " ";
    return os;
}
