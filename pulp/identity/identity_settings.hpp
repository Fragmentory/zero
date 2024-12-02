/**
 * \file identity_settings.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "identity_proto.hpp"
#include "identity_serie.hpp"
#include "pulp_defines.hpp"
#include "revision.h"

namespace identity
{
    namespace variant
    {
        template <pulp::defines::Identifier>
        struct Entity
        {
            using Settings = pulp::Undefined;
        };

        template <>
        struct Entity<pulp::defines::Identifier::TEST_APPLICATION>
        {
            using Settings = engine::identity::IdentityProto;
        };

        template <>
        struct Entity<pulp::defines::Identifier::APPLICATION>
        {
            using Settings = engine::identity::IdentitySerie;
        };
    }
    using Settings = identity::variant::Entity<pulp::defines::Identifier(identity::firmware::IDENTIFIER)>::Settings;
}
