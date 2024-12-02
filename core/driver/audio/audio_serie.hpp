/**
 * \file audio_serie.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "audio_defines.hpp"
#include "audio_pwm.hpp"

namespace core
{
    namespace driver
    {
        namespace audio
        {
            struct AudioSerie : public AudioPwm
            {
                AudioSerie(core::soc::Variant &_soc) :
                    AudioPwm(_soc)
                {
                }

                static constexpr SEQUENCE DEFAULT_SEQUENCE = SEQUENCE::UNDEFINED;

                static const uint8_t VERBOSITY_DEFAULT = VERBOSITY_MASK_ERROR | VERBOSITY_MASK_WARNING;
                static const uint8_t LOUDNESS_DEFAULT = 80;

                static constexpr uint16_t PERIOD_BLINK_MS = 100;
                static constexpr uint16_t PERIOD_SHORT_MS = 300;
                static constexpr uint16_t PERIOD_SEQUENCE_MS = 200;
                static constexpr uint16_t PERIOD_SECOND_MS = 1000;
                static constexpr uint16_t PERIOD_LONG_MS = 5000;

                static constexpr uint32_t BEEP_FREQUENCY = 2000;
                static constexpr uint32_t BOOP_FREQUENCY = 1000;
                static constexpr uint32_t TOOT_FREQUENCY = 500;
                static constexpr uint32_t TAAT_FREQUENCY = 250;
                static constexpr uint32_t UNDEFINED_FREQUENCY = 0;

                static constexpr uint32_t BEEP_LOUDNESS = 100;
                static constexpr uint32_t BOOP_LOUDNESS = 100;
                static constexpr uint32_t TOOT_LOUDNESS = 80;
                static constexpr uint32_t TAAT_LOUDNESS = 95;

                static constexpr Signal SIGNAL_BEEP = {BEEP_FREQUENCY, 100, BEEP_LOUDNESS};
                static constexpr Signal SIGNAL_BOOP = {BOOP_FREQUENCY, 200, BOOP_LOUDNESS};
                static constexpr Signal SIGNAL_TOOT = {TOOT_FREQUENCY, 400, TOOT_LOUDNESS};
                static constexpr Signal SIGNAL_TAAT = {TAAT_FREQUENCY, 600, TAAT_LOUDNESS};

                static constexpr Signal DELAY_BLINK = {UNDEFINED_FREQUENCY, PERIOD_BLINK_MS, 100};
                static constexpr Signal DELAY_SHORT = {UNDEFINED_FREQUENCY, PERIOD_SHORT_MS, 100};
                static constexpr Signal DELAY_LONG = {UNDEFINED_FREQUENCY, PERIOD_LONG_MS, 100};
            };
        }
    }
}
