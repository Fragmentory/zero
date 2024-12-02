/**
 * \file visual_smart_led.hpp
 * \author Roman Koch, koch.roman@gmail.com
 * 
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "visual_color.hpp"

#include <cassert>
#include <cstdint>
#include <cstdio>

namespace core::driver::visual
{
    struct SmartLed
    {
        struct morph_control_t
        {
            double increment;
            double summe;
        };

        morph_control_t morph_control[4];

        Color current;
        Color next;
        bool changed{false};

        bool is_stable() const { return current == next; }

        void set_current(const Color &_color)
        {
            current = _color;
            next = _color;
        }
        void set_next(const Color &_color, const uint64_t _steps)
        {
            next = _color;
            for (int i = 0; i < 4; ++i)
            {
                if (next.value[i] == current.value[i])
                {
                    morph_control[i].increment = 0;
                    morph_control[i].summe = 0;
                }
                else
                {
                    double delta = static_cast<double>(next.value[i] - current.value[i]);
                    morph_control[i].increment = delta / static_cast<double>(_steps);
                    morph_control[i].summe = 0;
                }
            }
        }

        void perform()
        {
            changed = false;
            if (current != next)
            {
                changed = true;
                auto color_changer = [](uint8_t &_current, const uint8_t _next, morph_control_t &_control)
                {
                    auto delta_calculator = [](morph_control_t &_control) -> int
                    {
                        int delta = 0;
                        _control.summe += _control.increment;
                        if (_control.summe > 1)
                        {
                            delta = static_cast<uint8_t>(_control.summe);
                            _control.summe -= delta;
                        }
                        return delta;
                    };
                    if (_current != _next)
                    {
                        const int delta = delta_calculator(_control);
                        const int new_current = ((_current + delta) < 0) ? 0 : ((_current + delta) > 0xff) ? 0xff : (_current + delta);
                        _current = (new_current < _next) ? static_cast<uint8_t>(new_current) : _next;
                    }
                    else
                    {
                        _current = _next;
                    }
                };

                color_changer(current.rgbw.r, next.rgbw.r, morph_control[0]);
                color_changer(current.rgbw.g, next.rgbw.g, morph_control[1]);
                color_changer(current.rgbw.b, next.rgbw.b, morph_control[2]);
                color_changer(current.rgbw.w, next.rgbw.w, morph_control[3]);

                if (current == next)
                {
                    for (int i = 0; i < 4; ++i)
                    {
                        morph_control[i].increment = 0;
                        morph_control[i].summe = 0;
                    }
                }
            }
        }
    };
}
