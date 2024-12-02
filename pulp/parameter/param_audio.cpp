/**
 * \file param_audio.cpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief Parameter "audio-feedback"

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include "param_audio.hpp"

#include "audio_variant.hpp"
#include "macros.hpp"

#include <stdlib.h>
#include <string.h>

namespace pulp
{
    namespace registry
    {
        namespace parameter
        {
            namespace audio
            {
                register_t g_register = {
                    .byte = {0xff, 0xff}
                };

                /**
                    \brief Initialize field with default values
                */
                void register_t::initialize(void)
                {
                    value.loudness = core::driver::audio::Variant::LOUDNESS_DEFAULT;
                    value.verbosity = core::driver::audio::Variant::VERBOSITY_DEFAULT;
                }

                /**
                    \brief Deserialize parameter value
                */
                void register_t::deserialize(uint8_t const *const _space)
                {
                    /* ATTENTION: NO CHECKS */
                    const uint8_t *ptr = _space;
                    const uint8_t tmp = static_cast<uint8_t>(*ptr++);
                    value.loudness = (tmp <= 100) ? tmp : 100;
                    value.verbosity = (static_cast<uint8_t>(*ptr++)) & (core::driver::audio::Variant::VERBOSITY_MASK);
                }

                /**
                    \brief Serialize parameter value
                */
                void register_t::serialize(uint8_t **_ptr) const
                {
                    /* ATTENTION: NO CHECKS */
                    *(*_ptr)++ = value.loudness;
                    *(*_ptr)++ = value.verbosity;
                }
            }
        }
    }
}