/**
 * \file visual_executor.cpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include "visual_executor.hpp"

#include "board_assembly.hpp"
#include "core.hpp"
#include "visual_color_defines.hpp"
#include "visual_variant.hpp"
#include "ws2812.hpp"

#include <iostream>
#include <pico/assert.h>
#include <pico/stdio.h>
#include <pico/time.h>

namespace core::driver::visual
{
    void Executor::initialize()
    {
        assert(state == pulp::COMPONENT_STATE::UNDEFINED);
        state = pulp::COMPONENT_STATE::IDLE;

        set_program(PROGRAM::IDLE);
    }

    void Executor::shutdown()
    {
        assert(state != pulp::COMPONENT_STATE::UNDEFINED);

        left.set_current(COLOR_BLACK);
        right.set_current(COLOR_BLACK);
        draw();

        state = pulp::COMPONENT_STATE::UNDEFINED;
    }

    void Executor::perform()
    {
        assert(state == pulp::COMPONENT_STATE::IDLE);

        switch (program)
        {
            case PROGRAM::ACTIVE:
                active_program.step();
                break;
            case PROGRAM::ALERT:
                alert_program.step();
                break;
            case PROGRAM::FREEZE:
                freeze_program.step();
                break;
            case PROGRAM::IDLE:
                idle_program.step();
                break;
            case PROGRAM::OFF:
                off_program.step();
                break;
            case PROGRAM::READY:
                ready_program.step();
                break;
            case PROGRAM::SERVICE:
                service_program.step();
                break;
            case PROGRAM::SET:
                break;
            case PROGRAM::UNDEFINED:
            default:
                break;
        }
    }

    void Executor::set_program(const PROGRAM _mode)
    {
        assert(state == pulp::COMPONENT_STATE::IDLE);

        program = _mode;
        switch (program)
        {
            case PROGRAM::ACTIVE:
                active_program.start();
                break;
            case PROGRAM::ALERT:
                alert_program.start();
                break;
            case PROGRAM::FREEZE:
                freeze_program.start();
                break;
            case PROGRAM::IDLE:
                idle_program.start();
                break;
            case PROGRAM::OFF:
                off_program.start();
                break;
            case PROGRAM::READY:
                ready_program.start();
                break;
            case PROGRAM::SERVICE:
                service_program.start();
                break;
            case PROGRAM::SET:
                break;
            case PROGRAM::UNDEFINED:
                break;
            default:
                break;
        }
    }

    void Executor::color(const Color &_left, const Color &_right, const uint64_t _steps)
    {
        if (_steps > 0)
        {
            left.set_next(_left, _steps);
            right.set_next(_right, _steps);
        }
        else
        {
            left.set_current(_left);
            right.set_current(_right);
        }
    }

    void Executor::clean()
    {
        for (size_t i = 0; i < Variant::NUMBER_OF_BEACONS; i++)
        {
            neopixel.put_pixel(COLOR_BLACK);
        }
    }

    void Executor::draw()
    {
        auto draw_depended = [this](const Color &_left, const Color &_right)
        {
            Color beacon_color[Variant::NUMBER_OF_BEACONS];

            beacon_color[0] = _left;
            beacon_color[Variant::NUMBER_OF_BEACONS - 1] = _right;

            for (size_t i = 1; i < Variant::NUMBER_OF_BEACONS - 1; i++)
            {
                const float right_factor = static_cast<float>(i) / static_cast<float>(Variant::NUMBER_OF_BEACONS - 1);
                const float left_factor = 1 - right_factor;

                const float r = _left.rgbw.r * left_factor + _right.rgbw.r * right_factor;
                const float g = _left.rgbw.g * left_factor + _right.rgbw.g * right_factor;
                const float b = _left.rgbw.b * left_factor + _right.rgbw.b * right_factor;
                const float w = _left.rgbw.w * left_factor + _right.rgbw.w * right_factor;

                const Color median{
                    .rgbw = {
                             .r = static_cast<uint8_t>(r),
                             .g = static_cast<uint8_t>(g),
                             .b = static_cast<uint8_t>(b),
                             .w = static_cast<uint8_t>(w),
                             }
                };
                beacon_color[i] = median;
            }

            for (size_t i = 0; i < Variant::NUMBER_OF_BEACONS; i++)
            {
                this->neopixel.put_pixel(beacon_color[Variant::BEACON_POSITION[i]]);
            }
        };

        left.perform();
        right.perform();
        if (left.changed || right.changed)
        {
            draw_depended(left.current, right.current);
        }
    }
}
