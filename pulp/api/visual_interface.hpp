/**
 * \file visual_interface.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "temperature_interface.hpp"

#include <cstdint>

namespace pulp
{
    namespace visual
    {
        struct Interface
        {
            virtual void active(void) = 0;
            virtual void alert(void) = 0;
            virtual void freeze(void) = 0;
            virtual void idle(void) = 0;
            virtual void off(void) = 0;
            virtual void ready(void) = 0;
            virtual void service(void) = 0;

            virtual void cold(void) = 0;
            virtual void warm(void) = 0;
            virtual void hot(void) = 0;
            virtual void scale(const pulp::temperature::Interface &) = 0;
        };
    }
}