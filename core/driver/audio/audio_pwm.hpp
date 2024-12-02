/**
 * \file audio_pwm.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "active_component_interface.hpp"
#include "audio_defines.hpp"
#include "soc_variant.hpp"

#include <queue>

namespace core
{
    namespace driver
    {
        namespace audio
        {
            struct AudioPwm : public pulp::ActiveComponentInterface
            {
                static const uint8_t VERBOSITY_MASK_ERROR = 0x01;
                static const uint8_t VERBOSITY_MASK_WARNING = 0x02;
                static const uint8_t VERBOSITY_MASK_LOG = 0x04;

                static const uint8_t VERBOSITY_MASK = VERBOSITY_MASK_ERROR | VERBOSITY_MASK_WARNING | VERBOSITY_MASK_LOG;

                AudioPwm(core::soc::Variant &);

                virtual void initialize();
                virtual void shutdown();
                virtual void perform();

                void set_loudness(const uint8_t _loudness) { loudness = _loudness; }
                uint8_t get_loudness(void) const { return loudness; }

                void play(const Signal _sequence);
                void play(const Signal _sequence[], const size_t _size);

                bool is_busy(void) const { return !sound.empty(); }

              private:
                core::soc::Variant &soc;
                bool delay{false};
                std::queue<Signal> sound;
                uint64_t play_timeout_ms{0};
                uint8_t loudness;
            };
        }
    }
}
