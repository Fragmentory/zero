/**
 * \file audio_melody.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include "audio_melody.hpp"

namespace core
{
    namespace audio
    {
        const Signal tetris_melody[] = {
            {Note::E5, 250,  90}, // E5, Viertelnote (250 ms)
            {Note::B4, 125, 100}, // B4, Achtelnote (125 ms)
            {Note::C5, 125, 100}, // C5, Achtelnote (125 ms)
            {Note::D5, 250, 100}, // D5, Viertelnote (250 ms)
            {Note::C5, 125, 100}, // C5, Achtelnote (125 ms)
            {Note::B4, 125, 100}, // B4, Achtelnote (125 ms)
            {Note::A4, 250, 100}, // A4, Viertelnote (250 ms)
            {Note::A4, 125, 100}, // A4, Achtelnote (125 ms)
            {Note::C5, 125, 100}, // C5, Achtelnote (125 ms)
            {Note::E5, 250,  90}, // E5, Viertelnote (250 ms)
            {Note::D5, 125, 100}, // D5, Achtelnote (125 ms)
            {Note::C5, 125, 100}, // C5, Achtelnote (125 ms)
            {Note::B4, 375, 100}, // B4, gepunktete Viertelnote (375 ms)
            {Note::C5, 125, 100}, // C5, Achtelnote (125 ms)
            {Note::D5, 250, 100}, // D5, Viertelnote (250 ms)
            {Note::E5, 250,  90}, // E5, Viertelnote (250 ms)
            {Note::C5, 250, 100},
            {Note::A4, 250, 100},
            {Note::A4, 250, 100},
        };

        const Signal scale[] = {
  // C-Dur Tonleiter, aufsteigend
            {Note::C4, 200, 100}, // C4
            {       0, 200,   0}, // Pause
            {Note::D4, 200, 100}, // D4
            {       0, 200,   0}, // Pause
            {Note::E4, 200, 100}, // E4
            {       0, 200,   0}, // Pause
            {Note::F4, 200, 100}, // F4
            {       0, 200,   0}, // Pause
            {Note::G4, 200, 100}, // G4
            {       0, 200,   0}, // Pause
            {Note::A4, 200, 100}, // A4
            {       0, 200,   0}, // Pause
            {Note::B4, 200, 100}, // B4
            {       0, 200,   0}, // Pause
            {Note::C5, 200, 100}, // C5 (Oktave höher)

  // C-Dur Tonleiter, absteigend
            {       0, 200,   0}, // Pause
            {Note::B4, 200, 100}, // B4
            {       0, 200,   0}, // Pause
            {Note::A4, 200, 100}, // A4
            {       0, 200,   0}, // Pause
            {Note::G4, 200, 100}, // G4
            {       0, 200,   0}, // Pause
            {Note::F4, 200, 100}, // F4
            {       0, 200,   0}, // Pause
            {Note::E4, 200, 100}, // E4
            {       0, 200,   0}, // Pause
            {Note::D4, 200, 100}, // D4
            {       0, 200,   0}, // Pause
            {Note::C4, 200, 100}, // C4
        };

        const Signal haydn_surprise[] = {
            { 659, 400, 100}, // E5
            { 659, 400, 100}, // E5
            { 740, 400, 100}, // F#5
            { 784, 400, 100}, // G5
            { 880, 400, 100}, // A5
            { 988, 400, 100}, // B5
            {1046, 400, 100}, // C6
            {1174, 800, 100}, // D6
            {1318, 400, 100}, // E6
            {1174, 400, 100}, // D6
            {1046, 400, 100}, // C6
            { 988, 400, 100}, // B5
            { 880, 400, 100}, // A5
            { 784, 400, 100}, // G5
            { 740, 400, 100}, // F#5
            { 659, 800, 100}  // E5
        };

        // Bach Toccata and Fugue in D minor - Simplified Theme in Signal Format
        const Signal bach_toccata[] = {
            {Note::D4, 250, 100}, // D4, Viertelnote
            {Note::D4, 250, 100}, // D4, Viertelnote
            {Note::D4, 250, 100}, // D4, Viertelnote
            {Note::D4, 250, 100}, // D4, Viertelnote

            {Note::D4, 125, 100}, // D4, Achtelnote
            {Note::D4, 125, 100}, // D4, Achtelnote
            {Note::D4, 125, 100}, // D4, Achtelnote
            {Note::D4, 125, 100}, // D4, Achtelnote

            {Note::D4, 250, 100}, // D4, Viertelnote
            {Note::A4, 250, 100}, // A4, Viertelnote
            {Note::D4, 250, 100}, // D4, Viertelnote
            {Note::A4, 250, 100}, // A4, Viertelnote

            {Note::D4, 125, 100}, // D4, Achtelnote
            {Note::D4, 125, 100}, // D4, Achtelnote
            {Note::D4, 125, 100}, // D4, Achtelnote
            {Note::D4, 125, 100}, // D4, Achtelnote

            {Note::D4, 250, 100}, // D4, Viertelnote
            {Note::A4, 250, 100}, // A4, Viertelnote
            {Note::D4, 250, 100}, // D4, Viertelnote
            {Note::A4, 250, 100}, // A4, Viertelnote

            {Note::D4, 125, 100}, // D4, Achtelnote
            {Note::D4, 125, 100}, // D4, Achtelnote
            {Note::D4, 125, 100}, // D4, Achtelnote
            {Note::D4, 125, 100}, // D4, Achtelnote
        };

        // Ode to Joy by Ludwig van Beethoven in Signal Format
        const Signal ode_to_joy[] = {
            {Note::E5,  500, 100}, // E5, Halbe Note
            {Note::E5,  500, 100}, // E5, Halbe Note
            {Note::F5,  500, 100}, // F5, Halbe Note
            {Note::G5,  500, 100}, // G5, Halbe Note

            {Note::G5,  500, 100}, // G5, Halbe Note
            {Note::F5,  500, 100}, // F5, Halbe Note
            {Note::E5,  500, 100}, // E5, Halbe Note
            {Note::E5,  500, 100}, // E5, Halbe Note

            {Note::E5,  500, 100}, // E5, Halbe Note
            {Note::D5,  500, 100}, // D5, Halbe Note
            {Note::D5,  500, 100}, // D5, Halbe Note
            {Note::E5,  500, 100}, // E5, Halbe Note

            {Note::E5,  500, 100}, // E5, Halbe Note
            {Note::E5,  500, 100}, // E5, Halbe Note
            {Note::E5, 1000, 100}, // E5, Ganze Note

  /*
  {REST, 500, 0}, // Pause, Halbe Note
  {Note::E5, 500, 100}, // E5, Halbe Note
  {Note::E5, 500, 100}, // E5, Halbe Note
  {Note::F5, 500, 100}, // F5, Halbe Note
  {Note::G5, 500, 100}, // G5, Halbe Note
  
  {Note::G5, 500, 100}, // G5, Halbe Note
  {Note::F5, 500, 100}, // F5, Halbe Note
  {Note::E5, 500, 100}, // E5, Halbe Note
  {Note::E5, 500, 100}, // E5, Halbe Note
  
  {Note::E5, 500, 100}, // E5, Halbe Note
  {Note::D5, 500, 100}, // D5, Halbe Note
  {Note::D5, 500, 100}, // D5, Halbe Note
  {Note::E5, 500, 100}, // E5, Halbe Note
  
  {Note::E5, 500, 100},  // E5, Halbe Note
  {Note::E5, 500, 100},  // E5, Halbe Note
  {Note::E5, 1000, 100}, // E5, Ganze Note
  
  {REST, 500, 0}, // Pause, Halbe Note
  */
        };

        const Signal super_mario[] = {
            { Note::E5, 225, 100},
            { Note::E5, 225, 100},
            {        0, 225, 100},
            { Note::E5, 225, 100},

            {        0, 225, 100},
            { Note::C5, 337, 100},
            { Note::E5, 112, 100},
            {        0, 225, 100},

            { Note::G5, 450, 100},
            {        0, 225, 100},
            {        0, 225, 100},
            {        0, 225, 100},

            { Note::G4, 450, 100},
            {        0, 225, 100},
            {        0, 225, 100},
            {        0, 225, 100},

            { Note::C5, 337, 100},
            {        0, 225, 100},
            {        0, 225, 100},
            { Note::G4, 112, 100},

            {        0, 225, 100},
            {        0, 225, 100},
            { Note::E4, 450, 100},
            {        0, 225, 100},

            {        0, 225, 100},
            { Note::A4, 225, 100},
            {        0, 225, 100},
            { Note::B4, 225, 100},

            {        0, 225, 100},
            {Note::AS4, 112, 100},
            { Note::A4, 112, 100},
            {        0, 225, 100},

            { Note::G4, 337, 100},
            { Note::E5, 112, 100},
            { Note::G5, 450, 100},

            { Note::A5, 450, 100},
            {        0, 225, 100},
            { Note::F5, 225, 100},
            { Note::G5, 112, 100},

            {        0, 225, 100},
            { Note::E5, 225, 100},
            {        0, 225, 100},
            { Note::C5, 337, 100},

            { Note::D5, 112, 100},
            { Note::B4, 450, 100},
        };

        const Signal imperial_march[] = {
            { Note::G4,  500,  80}, // G4
            { Note::G4,  500,  80}, // G4
            { Note::G4,  500,  80}, // G4
            {Note::Eb4,  350, 100}, // Eb4
            {Note::Bb4,  150, 100}, // Bb4
            { Note::G4,  500,  80}, // G4
            {Note::Eb4,  350, 100}, // Eb4
            {Note::Bb4,  150, 100}, // Bb4
            { Note::G4,  950,  80}, // G4
            {        0,   50,  80},
            { Note::D5,  500, 100}, // D5
            { Note::D5,  500, 100}, // D5
            { Note::D5,  500, 100}, // D5
            {Note::Eb5,  350, 100}, // Eb5
            {Note::Bb4,  150, 100}, // Bb4
            {Note::Gb4,  500, 100}, // Gb4
            {Note::Eb4,  350, 100}, // Eb4
            {Note::Bb4,  150, 100}, // Bb4
            { Note::G4, 1000,  80}  // G4
        };

        const Signal requiem_dies_irae[] = {
            {493,  500, 100}, // B4
            {493,  500, 100}, // B4
            {523,  500, 100}, // C5
            {587,  500, 100}, // D5
            {523,  500, 100}, // C5
            {493, 1000, 100}, // B4
            {  0,  500, 100}, // Rest
            {440, 1000, 100}, // A4
            {  0,  500, 100}  // Rest
        };

        const Signal funeral_march[] = {
            {196,  400, 100}, // G3
            {196,  400, 100}, // G3
            {196,  400, 100}, // G3
            {  0,  200, 100}, // Rest
            {196,  400, 100}, // G3
            {196,  400, 100}, // G3
            {196,  400, 100}, // G3
            {  0,  200, 100}, // Rest
            {196,  400, 100}, // G3
            {247,  400, 100}, // B3
            {330,  400, 100}, // E4
            {294, 1200, 100}, // D4
            {196,  400, 100}, // G3
            {247,  400, 100}, // B3
            {330,  400, 100}, // E4
            {294, 1200, 100}  // D4
        };

        const Signal fur_elise[] = {
            {659, 200, 100}, // E5
            {622, 200, 100}, // D#5
            {659, 200, 100}, // E5
            {622, 200, 100}, // D#5
            {659, 200, 100}, // E5
            {493, 200, 100}, // B4
            {587, 200, 100}, // D5
            {523, 200, 100}, // C5
            {440, 600, 100}, // A4
            {  0, 200, 100}, // Rest
            {261, 200, 100}, // C4
            {329, 200, 100}, // E4
            {440, 200, 100}  // A4
        };

        const Signal star_wars[] = {
            {196,  400, 100}, // G3
            {196,  400, 100}, // G3
            {196,  400, 100}, // G3
            {  0,  200, 100}, // Rest
            {196,  400, 100}, // G3
            {196,  400, 100}, // G3
            {196,  400, 100}, // G3
            {  0,  200, 100}, // Rest
            {196,  400, 100}, // G3
            {247,  400, 100}, // B3
            {330,  400, 100}, // E4
            {294, 1200, 100}, // D4
            {196,  400, 100}, // G3
            {247,  400, 100}, // B3
            {330,  400, 100}, // E4
            {294, 1200, 100}  // D4
        };

        const Signal let_it_go[] = {
            {659, 300, 100}, // E5
            {659, 300, 100}, // E5
            {659, 300, 100}, // E5
            {659, 300, 100}, // E5
            {659, 300, 100}, // E5
            {659, 300, 100}, // E5
            {659, 300, 100}, // E5
            {659, 300, 100}, // E5
            {659, 300, 100}, // E5
            {659, 300, 100}, // E5
            {587, 300, 100}, // D5
            {523, 300, 100}, // C5
            {659, 300, 100}, // E5
            {698, 300, 100}, // F5
            {659, 300, 100}, // E5
            {587, 300, 100}, // D5
            {523, 300, 100}, // C5
            {587, 300, 100}, // D5
            {659, 300, 100}  // E5
        };

        const Signal shape_of_you[] = {
            {440,  500, 100}, // A4
            {440,  500, 100}, // A4
            {440,  500, 100}, // A4
            {349,  500, 100}, // F4
            {440,  500, 100}, // A4
            {523,  500, 100}, // C5
            {440,  500, 100}, // A4
            {349,  500, 100}, // F4
            {440, 1000, 100}, // A4
            {349,  500, 100}, // F4
            {523,  500, 100}, // C5
            {440,  500, 100}  // A4
        };

        const Signal bad_guy[] = {
            {220, 400, 100}, // A3
            {220, 400, 100}, // A3
            {220, 400, 100}, // A3
            {220, 400, 100}, // A3
            {174, 400, 100}, // D3
            {174, 400, 100}, // D3
            {174, 400, 100}, // D3
            {174, 400, 100}, // D3
            {220, 800, 100}  // A3
        };

        const Signal enjoy_the_silence[] = {
            {523, 400, 100}, // C5
            {493, 400, 100}, // B4
            {466, 400, 100}, // A#4
            {440, 400, 100}, // A4
            {466, 400, 100}, // A#4
            {493, 400, 100}, // B4
            {523, 400, 100}, // C5
            {  0, 400, 100}, // Rest
            {493, 400, 100}, // B4
            {466, 400, 100}, // A#4
            {440, 400, 100}, // A4
            {466, 400, 100}, // A#4
            {493, 400, 100}, // B4
            {523, 400, 100}, // C5
            {493, 400, 100}, // B4
            {466, 400, 100}, // A#4
            {440, 400, 100}, // A4
            {466, 400, 100}, // A#4
            {493, 400, 100}, // B4
            {523, 400, 100}  // C5
        };

        extern const size_t bach_toccata_size = sizeof(bach_toccata) / sizeof(Signal);
        extern const size_t bad_guy_size = sizeof(bad_guy) / sizeof(Signal);
        extern const size_t enjoy_the_silence_size = sizeof(enjoy_the_silence) / sizeof(Signal);
        extern const size_t funeral_march_size = sizeof(funeral_march) / sizeof(Signal);
        extern const size_t fur_elise_size = sizeof(fur_elise) / sizeof(Signal);
        extern const size_t haydn_surprise_size = sizeof(haydn_surprise) / sizeof(Signal);
        extern const size_t imperial_march_size = sizeof(imperial_march) / sizeof(Signal);
        extern const size_t let_it_go_size = sizeof(let_it_go) / sizeof(Signal);
        extern const size_t ode_to_joy_size = sizeof(ode_to_joy) / sizeof(Signal);
        extern const size_t requiem_dies_irae_size = sizeof(requiem_dies_irae) / sizeof(Signal);
        extern const size_t scale_size = sizeof(scale) / sizeof(Signal);
        extern const size_t shape_of_you_size = sizeof(shape_of_you) / sizeof(Signal);
        extern const size_t star_wars_size = sizeof(star_wars) / sizeof(Signal);
        extern const size_t super_mario_size = sizeof(super_mario) / sizeof(Signal);
        extern const size_t tetris_melody_size = sizeof(tetris_melody) / sizeof(Signal);
    }
}
