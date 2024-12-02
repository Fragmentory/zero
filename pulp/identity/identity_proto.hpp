/**
 * \file identity_proto.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <cstdint>

namespace engine
{
    namespace identity
    {
        struct IdentityProto
        {
            static const uint16_t IDENTIFIER_DEFAULT = 0x0000;
            static const uint16_t HW_REVISION_DEFAULT = 0;
            static const uint16_t FW_REVISION_DEFAULT = 0;

            static constexpr float MAGIC_LATITUDE = 49.44162320135808f;
            static constexpr float MAGIC_LONGITUDE = 11.053797038031261f;
        };
    }
}
