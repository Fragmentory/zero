/**
 * \file param_audio.hpp
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

#pragma once

#include "parameter.hpp"

namespace pulp
{
    namespace registry
    {
        namespace parameter
        {
            namespace audio
            {
                /** \brief Node audio-feedback details */
                struct audio_t
                {
                    uint8_t loudness;
                    uint8_t verbosity;
                } __attribute__((packed));

                static const size_t SIZE = sizeof(audio_t);

                /**
                    \brief Audio default configuration.
                */
                union register_t
                {
                    uint8_t byte[SIZE];
                    audio_t value;

                    void initialize(void);

                    void deserialize(uint8_t const *const);
                    void serialize(uint8_t **) const;
                } __attribute__((packed));

                extern register_t g_register;
            }
        }
    }
}
