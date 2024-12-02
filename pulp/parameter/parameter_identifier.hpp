/**
 * \file parameter_identifier.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <cstdint>

namespace pulp
{
    namespace registry
    {
        namespace parameter
        {
            /**
                \brief Parameter identifier type
            */
            enum class IDENTIFIER : uint8_t
            {
                ADDRESS = 0xB0,
                AUDIO_FEEDBACK = 0xA1,
                CHARGER_CALIB = 0x53,
                DEVICE_NAME = 0x25,
                FEATURES = 0x51,
                LOAD_CALIB = 0x54,
                MAINTAINER = 0x23,
                POSITION = 0x24,
                SERIAL_NUMBER = 0x11,
                UNIQUE_IDENTIFIER = 0x12,
                USER = 0x70,
                VISUAL_FEEDBACK = 0xA2,

                UNDEFINED = 0xff,
            };

            extern IDENTIFIER to_identifier(const uint8_t);
        }
    }
}