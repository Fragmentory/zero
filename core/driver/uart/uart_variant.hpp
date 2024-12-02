/**
 * \file uart_variant.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "core_defines.hpp"
#include "revision.h"
#include "uart_empty.hpp"
#include "uart_first_proto.hpp"
#include "uart_first_serie.hpp"
#include "uart_second_proto.hpp"
#include "uart_second_serie.hpp"

namespace core
{
    namespace driver
    {
        namespace uart
        {
            template <typename V>
            struct Instance;

            namespace first
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
                        using Type = core::driver::uart::Instance<core::driver::uart::first::Proto>;
                    };

                    template <>
                    struct Entity<core::defines::IDENTIFIER::PLATFORM_SERIE>
                    {
                        using Type = core::driver::uart::Instance<core::driver::uart::first::Serie>;
                    };
                }
                using Variant = core::driver::uart::first::variant::Entity<core::defines::IDENTIFIER(identity::hardware::IDENTIFIER)>::Type;
            }
            namespace second
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
                        using Type = core::driver::uart::Instance<core::driver::uart::second::Proto>;
                    };

                    template <>
                    struct Entity<core::defines::IDENTIFIER::PLATFORM_SERIE>
                    {
                        using Type = core::driver::uart::Instance<core::driver::uart::second::Serie>;
                    };
                }
                using Variant = core::driver::uart::second::variant::Entity<core::defines::IDENTIFIER(identity::hardware::IDENTIFIER)>::Type;
            }
        }
    }
}
