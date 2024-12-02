/**
 * \file neopixel_variant.hpp
 * \author Roman Koch koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "core_defines.hpp"
#include "inolux5050.hpp"
#include "revision.h"
#include "ws2812.hpp"

namespace core
{
    namespace driver
    {
        namespace neopixel
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
                    //using Type = core::driver::ws2812::Instance;
                    using Type = core::driver::inolux5050::Instance;
                };

                template <>
                struct Entity<core::defines::IDENTIFIER::PLATFORM_SERIE>
                {
                    using Type = core::driver::inolux5050::Instance;
                };
            }
            using Variant = core::driver::neopixel::variant::Entity<core::defines::IDENTIFIER(identity::hardware::IDENTIFIER)>::Type;
        }
    }
}
