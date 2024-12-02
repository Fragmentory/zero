/**
 * \file component_state.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdint.h>

namespace pulp
{
    enum class COMPONENT_STATE : uint8_t
    {
        IDLE = 0x00,
        ACTIVE = 0x01,
        PENDING = 0x02,
        UNDEFINED = 0xff,
    };
}
