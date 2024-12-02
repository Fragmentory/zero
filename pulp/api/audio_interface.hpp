/**
 * \file audio_interface.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <cstdint>

namespace pulp
{
    namespace audio
    {
        struct Interface
        {
            virtual void beep(void) = 0;
            virtual void boop(void) = 0;
            virtual void toot(void) = 0;
            virtual void taat(void) = 0;
            virtual void play_alert(void) = 0;
            virtual void play_done(void) = 0;
            virtual void play_init(void) = 0;
            virtual void play_relax(void) = 0;
            virtual void play_service(void) = 0;
            virtual void play_start(void) = 0;
            virtual void play_work(void) = 0;
        };
    }
}