/**
 * \file reboot_watcher.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

namespace core::service
{
    namespace reboot
    {
        namespace defines
        {
            enum Mode
            {
                RESTART,
                BOOTSEL
            };
        }

        struct Watcher
        {
            Watcher();
            ~Watcher();

            static void set_mode_restart() { mode = defines::RESTART; }
            static void set_mode_bootsel() { mode = defines::BOOTSEL; }

          private:
            static defines::Mode mode;
        };
    }
}