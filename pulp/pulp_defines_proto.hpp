/**
 * \file pulp_defines_proto.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <cstdint>

namespace pulp
{
    namespace defines
    {
        struct AppProto
        {
            static const bool ENABLE_SERAIL_INTERFACE_ON_START = true;
            static const bool ENABLE_USB_INTERFACE_ON_START = true;

            static constexpr const char *INTRO = "APP_PROTO";
        };
    }
}
