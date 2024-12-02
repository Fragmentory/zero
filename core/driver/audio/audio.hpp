/**
 * \file audio.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "audio_interface.hpp"
#include "audio_melody.hpp"
#include "audio_variant.hpp"

namespace core
{
    struct Audio : public pulp::audio::Interface
    {
        using Driver = core::driver::audio::Variant;

        Audio(Driver &_audio_hardware) :
            audio_hardware(_audio_hardware)
        {
        }

        virtual void beep(void) override;
        virtual void boop(void) override;
        virtual void toot(void) override;
        virtual void taat(void) override;
        virtual void play_alert(void) override;
        virtual void play_done(void) override;
        virtual void play_init(void) override;
        virtual void play_relax(void) override;
        virtual void play_service(void) override;
        virtual void play_start(void) override;
        virtual void play_work(void) override;

        void play_theme(const audio::THEME);

      private:
        Driver &audio_hardware;
    };
}
