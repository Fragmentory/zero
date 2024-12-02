/**
 * \file visual_prog_service.hpp
 * \author Roman Koch, koch.roman@gmail.com
 * 
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "visual_color_defines.hpp"
#include "visual_executor_interface.hpp"

namespace core::driver::visual
{
    namespace program::service
    {
        struct Instance
        {
            Instance(ExecutorInterface &_neopixel) :
                neopixel(_neopixel)
            {
            }

            void start();
            void step();

          private:
            ExecutorInterface &neopixel;
        };
    }
}
