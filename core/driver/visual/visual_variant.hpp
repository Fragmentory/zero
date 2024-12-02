/**
 * \file visual_variant.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "core_defines.hpp"
#include "revision.h"
#include "visual_proto.hpp"
#include "visual_proto_inolux.hpp"
#include "visual_serie.hpp"

namespace core::driver::visual
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
            //using Type = VisualPrototype;
            using Type = VisualPrototypeInolux;
        };
        template <>
        struct Entity<core::defines::IDENTIFIER::PLATFORM_SERIE>
        {
            using Type = VisualSerie;
        };
    }
    using Variant = visual::variant::Entity<core::defines::IDENTIFIER(identity::hardware::IDENTIFIER)>::Type;
}
