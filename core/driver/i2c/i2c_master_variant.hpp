/**
 * \file i2c_master_variant.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "core_defines.hpp"
#include "i2c_master_proto.hpp"
#include "i2c_master_serie.hpp"
#include "revision.h"

namespace core
{
    namespace driver
    {
        namespace i2c
        {
            namespace master
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
                        using Type = core::driver::i2c::master::Proto;
                    };

                    template <>
                    struct Entity<core::defines::IDENTIFIER::PLATFORM_SERIE>
                    {
                        using Type = core::driver::i2c::master::Serie;
                    };
                }
                using Variant = core::driver::i2c::master::variant::Entity<core::defines::IDENTIFIER(identity::hardware::IDENTIFIER)>::Type;
            }
        }
    }
}
