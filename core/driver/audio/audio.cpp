/**
 * \file audio.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include "audio.hpp"

#include "audio_variant.hpp"

namespace core
{
    void Audio::beep() { audio_hardware.play(Driver::SIGNAL_BEEP); }

    void Audio::boop() { audio_hardware.play(Driver::SIGNAL_BOOP); }

    void Audio::toot() { audio_hardware.play(Driver::SIGNAL_TOOT); }

    void Audio::taat() { audio_hardware.play(Driver::SIGNAL_TAAT); }

    void Audio::play_alert()
    {
        const audio::Signal beep{Driver::BEEP_FREQUENCY, Driver::PERIOD_SEQUENCE_MS, Driver::BEEP_LOUDNESS};
        const audio::Signal boop{Driver::BOOP_FREQUENCY, Driver::PERIOD_SEQUENCE_MS, Driver::BOOP_LOUDNESS};
        audio_hardware.play(beep);
        audio_hardware.play(boop);
        audio_hardware.play(beep);
        audio_hardware.play(boop);
        audio_hardware.play(Driver::DELAY_SHORT);
    }

    void Audio::play_done()
    {
        const audio::Signal taat{Driver::TAAT_FREQUENCY, Driver::PERIOD_SEQUENCE_MS, Driver::TAAT_LOUDNESS};
        const audio::Signal boop{Driver::BOOP_FREQUENCY, Driver::PERIOD_SEQUENCE_MS, Driver::BOOP_LOUDNESS};
        audio_hardware.play(boop);
        audio_hardware.play(taat);
        audio_hardware.play(Driver::DELAY_SHORT);
    }

    void Audio::play_init()
    {
        const audio::Signal beep{Driver::BEEP_FREQUENCY, Driver::PERIOD_SEQUENCE_MS, Driver::BEEP_LOUDNESS};
        audio_hardware.play(beep);
        audio_hardware.play(Driver::DELAY_SHORT);
    }

    void Audio::play_relax()
    {
        const audio::Signal taat{Driver::TAAT_FREQUENCY, Driver::PERIOD_SEQUENCE_MS, Driver::TAAT_LOUDNESS};
        const audio::Signal toot{Driver::TOOT_FREQUENCY, Driver::PERIOD_SEQUENCE_MS, Driver::TOOT_LOUDNESS};
        audio_hardware.play(toot);
        audio_hardware.play(taat);
        audio_hardware.play(Driver::DELAY_SHORT);
    }

    void Audio::play_service()
    {
        const audio::Signal beep{Driver::BEEP_FREQUENCY, Driver::PERIOD_SEQUENCE_MS, Driver::BEEP_LOUDNESS};
        const audio::Signal toot{Driver::TOOT_FREQUENCY, Driver::PERIOD_SEQUENCE_MS, Driver::TOOT_LOUDNESS};
        audio_hardware.play(toot);
        audio_hardware.play(beep);
        audio_hardware.play(Driver::DELAY_SHORT);
    }

    void Audio::play_start()
    {
        const audio::Signal boop{Driver::BOOP_FREQUENCY, Driver::PERIOD_SEQUENCE_MS, Driver::BOOP_LOUDNESS};
        audio_hardware.play(boop);
        audio_hardware.play(Driver::DELAY_SHORT);
    }

    void Audio::play_work()
    {
        const audio::Signal taat{Driver::TAAT_FREQUENCY, 200, Driver::TAAT_LOUDNESS};
        const audio::Signal toot{Driver::TOOT_FREQUENCY, 200, Driver::TOOT_LOUDNESS};
        audio_hardware.play(taat);
        audio_hardware.play(toot);
        audio_hardware.play(Driver::DELAY_SHORT);
    }

    void Audio::play_theme(const audio::THEME _theme)
    {
        switch (_theme)
        {
            case audio::HAYDN_SURPRISE:
                audio_hardware.play(audio::haydn_surprise, audio::haydn_surprise_size);
                break;
            case audio::BACH_TOCCATA:
                audio_hardware.play(audio::bach_toccata, audio::bach_toccata_size);
                break;
            case audio::ODE_TO_JOY:
                audio_hardware.play(audio::ode_to_joy, audio::ode_to_joy_size);
                break;
            case audio::SUPER_MARIO:
                audio_hardware.play(audio::super_mario, audio::super_mario_size);
                break;
            case audio::IMPERIAL_MARCH:
                audio_hardware.play(audio::imperial_march, audio::imperial_march_size);
                break;
            case audio::REQUIEM_DIES_IRAE:
                audio_hardware.play(audio::requiem_dies_irae, audio::requiem_dies_irae_size);
                break;
            case audio::FUNERAL_MARCH:
                audio_hardware.play(audio::funeral_march, audio::funeral_march_size);
                break;
            case audio::FUR_ELISE:
                audio_hardware.play(audio::fur_elise, audio::fur_elise_size);
                break;
            case audio::STAR_WARS:
                audio_hardware.play(audio::star_wars, audio::star_wars_size);
                break;
            case audio::LET_IT_GO:
                audio_hardware.play(audio::let_it_go, audio::let_it_go_size);
                break;
            case audio::SHAPE_OF_YOU:
                audio_hardware.play(audio::shape_of_you, audio::shape_of_you_size);
                break;
            case audio::BAD_GUY:
                audio_hardware.play(audio::bad_guy, audio::bad_guy_size);
                break;
            case audio::ENJOY_THE_SILENCE:
                audio_hardware.play(audio::enjoy_the_silence, audio::enjoy_the_silence_size);
                break;
            case audio::SCALE:
                audio_hardware.play(audio::scale, audio::scale_size);
                break;
            case audio::TETRIS_MELODY:
                audio_hardware.play(audio::tetris_melody, audio::tetris_melody_size);
                break;
            case audio::MELODY_COUNT:
            default:
                break;
        }
    }
}