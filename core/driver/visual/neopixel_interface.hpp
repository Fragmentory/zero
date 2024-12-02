/**
 * \file neopixel_interface.hpp
 * \author Roman Koch koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "visual_color.hpp"

namespace core::driver
{
    namespace neopixel
    {
        struct Interface
        {
            virtual void put_pixel(const visual::rgbw::Color &) = 0;
        };
    }
}