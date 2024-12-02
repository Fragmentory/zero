/**
 * \file param_visual.cpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief Parameter "visual-feedback"

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include "param_visual.hpp"

#include "macros.hpp"
#include "visual_variant.hpp"

#include <stdlib.h>
#include <string.h>

namespace pulp
{
    namespace registry
    {
        namespace parameter
        {
            namespace visual
            {
                register_t g_register = {
                    .byte = {0xff, 0xff}
                };

                /**
                    \brief Initialize field with default values
                */
                void register_t::initialize(void)
                {
                    value.mode = core::driver::visual::Variant::DEFAULT_MODE;
                    value.verbosity = core::driver::visual::Variant::DEFAULT_VERBOSITY;
                    value.timeout = core::driver::visual::Variant::BLINK_ACTIVE_TIMEOUT;
                }

                /**
                    \brief Deserialize parameter value
                */
                void register_t::deserialize(uint8_t const *const _space)
                {
                    /* ATTENTION: NO CHECKS */
                    const uint8_t *ptr = _space;
                    /*
                    value.program = static_cast<engine::backlight::PROGRAM>(*ptr++);
                    value.left.rgb.r = *ptr++;
                    value.left.rgb.g = *ptr++;
                    value.left.rgb.b = *ptr++;
                    value.right.rgb.r = *ptr++;
                    value.right.rgb.g = *ptr++;
                    value.right.rgb.b = *ptr++;
                    */
                    value.mode = (uint8_t)*ptr++;
                    value.verbosity = (uint8_t)*ptr++;
                    value.timeout = deserialize_word(&ptr);
                }

                /**
                    \brief Serialize parameter value
                */
                void register_t::serialize(uint8_t **_ptr) const
                {
                    /* ATTENTION: NO CHECKS */
                    /*
                     *(*_ptr)++ = (uint8_t)value.program;
                     *(*_ptr)++ = (uint8_t)value.left.rgb.r;
                     *(*_ptr)++ = (uint8_t)value.left.rgb.g;
                     *(*_ptr)++ = (uint8_t)value.left.rgb.b;
                     *(*_ptr)++ = (uint8_t)value.right.rgb.r;
                     *(*_ptr)++ = (uint8_t)value.right.rgb.g;
                     *(*_ptr)++ = (uint8_t)value.right.rgb.b;
                     */
                    *(*_ptr)++ = (uint8_t)value.mode;
                    *(*_ptr)++ = (uint8_t)value.verbosity;
                    serialize_word(value.timeout, _ptr);
                }
            }
        }
    }
}