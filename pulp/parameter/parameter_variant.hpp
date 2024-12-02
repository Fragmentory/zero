/**
 * \file parameter_settings.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "parameter_proto.hpp"
#include "parameter_serie.hpp"
#include "pulp_defines.hpp"
#include "revision.h"

namespace pulp
{
    namespace registry
    {
        namespace parameter
        {
            struct Undefined
            {
            };

            namespace variant
            {
                template <pulp::defines::Identifier>
                struct Entity
                {
                    using Defaults = parameter::Undefined;
                };

                template <>
                struct Entity<pulp::defines::Identifier::TEST_APPLICATION>
                {
                    using Defaults = registry::parameter::DefaultProto;
                };

                template <>
                struct Entity<pulp::defines::Identifier::APPLICATION>
                {
                    using Defaults = registry::parameter::DefaultSerie;
                };
            }
            using Defaults = variant::Entity<pulp::defines::Identifier(identity::firmware::IDENTIFIER)>::Defaults;
        }
    }
}
