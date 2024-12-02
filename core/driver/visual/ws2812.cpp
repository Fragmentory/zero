/**
 * \file ws2812.cpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include "ws2812.hpp"

#include "macros.hpp"
#include "neopixel.pio.h"
#include "visual_variant.hpp"

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <hardware/clocks.h>
#include <hardware/pio.h>
#include <pico/stdlib.h>

namespace core::driver
{
    namespace ws2812
    {
        /*
            ATTENTION: USAGE OF PIO(0|1) IS NOT A VARIANT;
            Set PIO0_BASE or PIO1_BASE to VISUAL_PIO if you use smart led control.
        */
        static const unsigned int VISUAL_PIO_BASE = PIO0_BASE;
        static const unsigned int VISUAL_PIO_STATE_MACHINE = 0;

        const float LUM_R = 1.400f;
        const float LUM_G = 0.700f;
        const float LUM_B = 0.400f;

        const float LUM_R_FACTOR = 1.400f;
        const float LUM_G_FACTOR = 0.700f;
        const float LUM_B_FAKTOR = 0.400f;

        using VisualVariant = core::driver::visual::Variant;

        void Instance::initialize()
        {
            assert(state == pulp::COMPONENT_STATE::UNDEFINED && "multiple initialisation calls");
            state = pulp::COMPONENT_STATE::IDLE;

            PIO pio = ((pio_hw_t *)VISUAL_PIO_BASE);
            int sm = VISUAL_PIO_STATE_MACHINE;
            uint offset = pio_add_program(pio, &neopixel_program);
            neopixel_program_init(pio, sm, offset, VisualVariant::VISUAL_PIN, 800000, false);
            // neopixel_program_init(pio, sm, offset, VisualVariant::VISUAL_PIN, 800000, true);
            pio_sm_clear_fifos(pio, sm);
            gpio_set_pulls(VisualVariant::VISUAL_PIN, true, false);

            sleep_ms(1);
            for (int i = 0; i < 5; ++i)
            {
                pio_sm_put_blocking(pio, sm, 0);
            }
            sleep_ms(10);
        }

        void Instance::shutdown(void)
        {
            assert(state != pulp::COMPONENT_STATE::UNDEFINED && "multiple shutdown calls");
            state = pulp::COMPONENT_STATE::UNDEFINED;

            PIO pio = ((pio_hw_t *)VISUAL_PIO_BASE);
            int sm = VISUAL_PIO_STATE_MACHINE;

            sleep_ms(1);
            for (int i = 0; i < 5; ++i)
            {
                pio_sm_put_blocking(pio, sm, 0);
            }
            sleep_ms(1);
            pio_sm_clear_fifos(pio, sm);
            pio_sm_set_enabled(pio, sm, false);
            pio_clear_instruction_memory(pio);
            sleep_ms(10);
        }

        void Instance::put_pixel(const visual::rgbw::Color &_color)
        {
            assert(state == pulp::COMPONENT_STATE::IDLE && "not initialized");

            PIO pio = ((pio_hw_t *)VISUAL_PIO_BASE);
            const int sm = VISUAL_PIO_STATE_MACHINE;
            uint32_t value = ((uint32_t)(_color.rgbw.r) << 8) | ((uint32_t)(_color.rgbw.g) << 16) | (uint32_t)(_color.rgbw.b);
            pio_sm_put_blocking(pio, sm, value << 8u);
        }
    }
}
