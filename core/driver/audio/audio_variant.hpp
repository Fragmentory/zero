/**
 * \file audio_variant.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "audio_proto.hpp"
#include "audio_serie.hpp"
#include "core_defines.hpp"
#include "revision.h"

namespace core
{
    namespace driver
    {
        namespace audio
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
                    using Type = core::driver::audio::AudioProto;
                };

                template <>
                struct Entity<core::defines::IDENTIFIER::PLATFORM_SERIE>
                {
                    using Type = core::driver::audio::AudioSerie;
                };
            }
            using Variant = audio::variant::Entity<core::defines::IDENTIFIER(identity::firmware::IDENTIFIER)>::Type;
        }
    }
}
