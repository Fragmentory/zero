/**
 * \file visual_defines.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "visual_color.hpp"

#include <stdint.h>

namespace core::driver::visual
{
    enum class PROGRAM : uint8_t
    {
        ACTIVE = 0x04,
        ALERT = 0x00,
        FREEZE = 0x01,
        IDLE = 0x09,
        OFF = 0x05,
        READY = 0x08,
        SERVICE = 0x0a,
        SET = 0x06,
        UNDEFINED = 0xff,
    };
}
