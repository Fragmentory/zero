/**
 * \file audio_mode.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdint.h>

namespace core
{
    namespace driver
    {
        namespace audio
        {
            enum class SEQUENCE : uint8_t
            {
                ALERT = 0x00,
                SERVICE = 0x02,
                START = 0x01,
                UPDATE = 0x03,

                UNDEFINED = 0xff,
            };

            enum class VERBOSITY : uint8_t
            {
                ALERT = 0x00,
                SERVICE = 0x02,
                START = 0x01,
                UPDATE = 0x03,

                UNDEFINED = 0xff,
            };

            struct Signal
            {
                uint32_t frequency;
                uint16_t duration_ms;
                uint8_t loudness;
            };
        }
    }
}
