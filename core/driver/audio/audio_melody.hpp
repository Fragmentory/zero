/**
 * \file audio_melody.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "audio_defines.hpp"

#include <cstdlib>

namespace core
{
    namespace audio
    {
        using Signal = core::driver::audio::Signal;

        enum THEME : uint8_t
        {
            BACH_TOCCATA,
            BAD_GUY,
            ENJOY_THE_SILENCE,
            FUNERAL_MARCH,
            FUR_ELISE,
            HAYDN_SURPRISE,
            IMPERIAL_MARCH,
            LET_IT_GO,
            ODE_TO_JOY,
            REQUIEM_DIES_IRAE,
            SCALE,
            SHAPE_OF_YOU,
            STAR_WARS,
            SUPER_MARIO,
            TETRIS_MELODY,
            MELODY_COUNT // Number of melodies
        };

        struct Note
        {
            // Frequenzen für Noten
            static const uint32_t A1 = 55;
            static const uint32_t A2 = 110;
            static const uint32_t A3 = 220;
            static const uint32_t A4 = 440;
            static const uint32_t A5 = 880;
            static const uint32_t A6 = 1760;
            static const uint32_t A7 = 3520;
            static const uint32_t AS1 = 58;
            static const uint32_t AS2 = 117;
            static const uint32_t AS3 = 233;
            static const uint32_t AS4 = 466;
            static const uint32_t AS5 = 932;
            static const uint32_t AS6 = 1865;
            static const uint32_t AS7 = 3729;
            static const uint32_t B0 = 31;
            static const uint32_t B1 = 62;
            static const uint32_t B2 = 123;
            static const uint32_t B3 = 247;
            static const uint32_t B4 = 494;
            static const uint32_t B5 = 988;
            static const uint32_t B6 = 1976;
            static const uint32_t B7 = 3951;
            static const uint32_t Bb4 = 466; // Bb4
            static const uint32_t C1 = 33;
            static const uint32_t C2 = 65;
            static const uint32_t C3 = 131;
            static const uint32_t C4 = 262;
            static const uint32_t C5 = 523;
            static const uint32_t C6 = 1047;
            static const uint32_t C7 = 2093;
            static const uint32_t C8 = 4186;
            static const uint32_t CS1 = 35;
            static const uint32_t CS2 = 69;
            static const uint32_t CS3 = 139;
            static const uint32_t CS4 = 277;
            static const uint32_t CS5 = 554;
            static const uint32_t CS6 = 1109;
            static const uint32_t CS7 = 2217;
            static const uint32_t CS8 = 4435;
            static const uint32_t D1 = 37;
            static const uint32_t D2 = 73;
            static const uint32_t D3 = 147;
            static const uint32_t D4 = 294;
            static const uint32_t D5 = 587;
            static const uint32_t D6 = 1175;
            static const uint32_t D7 = 2349;
            static const uint32_t D8 = 4699;
            static const uint32_t DS1 = 39;
            static const uint32_t DS2 = 78;
            static const uint32_t DS3 = 156;
            static const uint32_t DS4 = 311;
            static const uint32_t DS5 = 622;
            static const uint32_t DS6 = 1245;
            static const uint32_t DS7 = 2489;
            static const uint32_t DS8 = 4978;
            static const uint32_t E1 = 41;
            static const uint32_t E2 = 82;
            static const uint32_t E3 = 165;
            static const uint32_t E4 = 330;
            static const uint32_t E5 = 659;
            static const uint32_t E6 = 1319;
            static const uint32_t E7 = 2637;
            static const uint32_t Eb4 = 311; // Eb4
            static const uint32_t Eb5 = 622; // Eb5
            static const uint32_t F1 = 44;
            static const uint32_t F2 = 87;
            static const uint32_t F3 = 175;
            static const uint32_t F4 = 349;
            static const uint32_t F5 = 698;
            static const uint32_t F6 = 1397;
            static const uint32_t F7 = 2794;
            static const uint32_t FS1 = 46;
            static const uint32_t FS2 = 93;
            static const uint32_t FS3 = 185;
            static const uint32_t FS4 = 370;
            static const uint32_t FS5 = 740;
            static const uint32_t FS6 = 1480;
            static const uint32_t FS7 = 2960;
            static const uint32_t G1 = 49;
            static const uint32_t G2 = 98;
            static const uint32_t G3 = 196;
            static const uint32_t G4 = 392;
            static const uint32_t G5 = 784;
            static const uint32_t G6 = 1568;
            static const uint32_t G7 = 3136;
            static const uint32_t Gb4 = 370; // Gb4
            static const uint32_t GS1 = 52;
            static const uint32_t GS2 = 104;
            static const uint32_t GS3 = 208;
            static const uint32_t GS4 = 415;
            static const uint32_t GS5 = 831;
            static const uint32_t GS6 = 1661;
            static const uint32_t GS7 = 3322;
            static const uint32_t REST = 0;
        };

        extern const Signal bach_toccata[];
        extern const Signal bad_guy[];
        extern const Signal enjoy_the_silence[];
        extern const Signal funeral_march[];
        extern const Signal fur_elise[];
        extern const Signal haydn_surprise[];
        extern const Signal imperial_march[];
        extern const Signal let_it_go[];
        extern const Signal ode_to_joy[];
        extern const Signal requiem_dies_irae[];
        extern const Signal scale[];
        extern const Signal shape_of_you[];
        extern const Signal star_wars[];
        extern const Signal super_mario[];
        extern const Signal tetris_melody[];

        extern const size_t bach_toccata_size;
        extern const size_t bad_guy_size;
        extern const size_t enjoy_the_silence_size;
        extern const size_t funeral_march_size;
        extern const size_t fur_elise_size;
        extern const size_t haydn_surprise_size;
        extern const size_t imperial_march_size;
        extern const size_t let_it_go_size;
        extern const size_t ode_to_joy_size;
        extern const size_t requiem_dies_irae_size;
        extern const size_t scale_size;
        extern const size_t shape_of_you_size;
        extern const size_t star_wars_size;
        extern const size_t super_mario_size;
        extern const size_t tetris_melody_size;
    }
}
