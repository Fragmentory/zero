/**
 * \file pulp_variant.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "pulp_defines.hpp"
#include "pulp_defines_proto.hpp"
#include "pulp_defines_serie.hpp"
#include "revision.h"

namespace pulp
{
    namespace variant
    {
        template <pulp::defines::Identifier>
        struct Entity
        {
            using Type = pulp::Undefined;
        };

        template <>
        struct Entity<pulp::defines::Identifier::TEST_APPLICATION>
        {
            using Type = pulp::defines::AppProto;
        };

        template <>
        struct Entity<pulp::defines::Identifier::APPLICATION>
        {
            using Type = pulp::defines::AppSerie;
        };
    }
    using Variant = pulp::variant::Entity<pulp::defines::Identifier(identity::firmware::IDENTIFIER)>::Type;
}
