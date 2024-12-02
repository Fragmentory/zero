/**
 * \file audio_pwm.cpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include "audio_pwm.hpp"

#include "audio_defines.hpp"
#include "audio_melody.hpp"
#include "audio_variant.hpp"
#include "core.hpp"

namespace core
{
    namespace driver
    {
        namespace audio
        {

            AudioPwm::AudioPwm(core::soc::Variant &_soc) :
                soc(_soc),
                loudness(Variant::LOUDNESS_DEFAULT)
            {
            }

            void AudioPwm::initialize() {}

            void AudioPwm::shutdown() {}

            void AudioPwm::perform()
            {
                static uint64_t timestamp = soc.get_stopwatch();
                const uint64_t us_diff = soc.get_stopwatch() - timestamp;

                if (soc.is_pwm_enabled())
                {
                    if (us_diff >= play_timeout_ms * 1000)
                    {
                        soc.pwm_disable();
                    }
                }
                else if (delay)
                {
                    if (us_diff >= play_timeout_ms * 1000)
                    {
                        delay = false;
                    }
                }
                else
                {
                    if (!sound.empty())
                    {
                        const Signal signal = sound.front();
                        sound.pop();
                        timestamp = soc.get_stopwatch();

                        play_timeout_ms = signal.duration_ms;
                        if (signal.frequency != Variant::UNDEFINED_FREQUENCY)
                        {
                            soc.set_pwm_frequency(signal.frequency);
                            const uint16_t duty_cycle = static_cast<uint16_t>(signal.loudness / 100.0 * (loudness / 100.0) * 0x7fff);
                            soc.set_pwm_duty_cycle(duty_cycle);
                            soc.pwm_enable();
                        }
                        else
                        {
                            delay = true;
                        }
                    }
                }
            }

            void AudioPwm::play(const Signal _signal) { sound.push(_signal); }

            void AudioPwm::play(const Signal _sequence[], const size_t _size)
            {
                for (size_t i = 0; i < _size; ++i)
                {
                    sound.push(_sequence[i]);
                }
            }
        }
    }
}
