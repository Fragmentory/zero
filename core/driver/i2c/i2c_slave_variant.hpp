/**
 * \file i2c_slave_variant.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "core_defines.hpp"
#include "i2c_slave_proto.hpp"
#include "i2c_slave_serie.hpp"
#include "revision.h"

namespace core
{
    namespace driver
    {
        namespace i2c
        {
            namespace slave
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
                        using Type = core::driver::i2c::slave::Proto;
                    };

                    template <>
                    struct Entity<core::defines::IDENTIFIER::PLATFORM_SERIE>
                    {
                        using Type = core::driver::i2c::slave::Serie;
                    };
                }
                using Variant = core::driver::i2c::slave::variant::Entity<core::defines::IDENTIFIER(identity::hardware::IDENTIFIER)>::Type;
            }
        }
    }
}
