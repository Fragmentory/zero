/**
 * \file visual.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "temperature_interface.hpp"
#include "visual_interface.hpp"
#include "visual_variant.hpp"

namespace core
{
    struct Visual : public pulp::visual::Interface
    {
        using Hardware = core::driver::visual::Variant;

        Visual(Hardware &_visual_hardware) :
            visual_hardware(_visual_hardware)
        {
        }

        virtual void active(void) override;
        virtual void alert(void) override;
        virtual void freeze(void) override;
        virtual void idle(void) override;
        virtual void off(void) override;
        virtual void ready(void) override;
        virtual void service(void) override;

        virtual void cold(void) override;
        virtual void warm(void) override;
        virtual void hot(void) override;
        virtual void scale(const pulp::temperature::Interface &) override;

      private:
        static const uint16_t INIT_STEP_TIMEOUT = 10;
        static const uint16_t FREEZE_STEP_TIMEOUT = 100;

        static constexpr float BORDER_1 = 0.10f;
        static constexpr float BORDER_2 = 0.40f;
        static constexpr float BORDER_3 = 0.60f;
        static constexpr float BORDER_4 = 0.90f;
        static constexpr float DELTA = 0.01f;

        Hardware &visual_hardware;

        float buffer[16] = {0};
        int index = 0;
        float sum = 0;

        float max_temperature{Hardware::MAX_TEMPERATURE};
        float min_temperature{Hardware::MIN_TEMPERATURE};
    };
}
