/**
 * \file soc_type.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "core_defines.hpp"
#include "revision.h"
#include "rp2040_soc_proto.hpp"
#include "rp2040_soc_serie.hpp"

namespace core
{
    namespace soc
    {
        namespace variant
        {
            template <core::defines::IDENTIFIER>
            struct Entity
            {
                using Type = core::Undefined;
            };

            template <>
            struct Entity<core::defines::IDENTIFIER::PLATFORM_PROTO>
            {
                using Type = core::soc::RP2040PlatformProto;
            };

            template <>
            struct Entity<core::defines::IDENTIFIER::PLATFORM_SERIE>
            {
                using Type = core::soc::RP2040PlatformSerie;
            };
        }
        using Variant = core::soc::variant::Entity<core::defines::IDENTIFIER(identity::hardware::IDENTIFIER)>::Type;
    }
}
