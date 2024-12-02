/**
 * \file rp2040_stopwatch.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief Stopwatch

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#pragma once

#include "component_interface.hpp"

#include <pico/time.h>
#include <stdint.h>

namespace core
{
    namespace soc
    {
        struct RP2040Stopwatch : public pulp::ComponentInterface
        {
            RP2040Stopwatch(absolute_time_t &);
            virtual ~RP2040Stopwatch() {}

            virtual void initialize(void) override {}
            virtual void shutdown(void) override {}

            void restart(void);
            uint64_t get_value(void) const;

          protected:
            absolute_time_t &time_reference;
        };
    }
}
