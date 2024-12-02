/**
 * \file visual_executor.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "active_component_interface.hpp"
#include "component_state.hpp"
#include "neopixel_interface.hpp"
#include "visual_color.hpp"
#include "visual_color_defines.hpp"
#include "visual_executor_interface.hpp"
#include "visual_prog_active.hpp"
#include "visual_prog_alert.hpp"
#include "visual_prog_freeze.hpp"
#include "visual_prog_identifier.hpp"
#include "visual_prog_idle.hpp"
#include "visual_prog_off.hpp"
#include "visual_prog_ready.hpp"
#include "visual_prog_service.hpp"
#include "visual_smart_led.hpp"

namespace core::driver::visual
{
    struct Executor : public pulp::ActiveComponentInterface, public ExecutorInterface
    {
        Executor(driver::neopixel::Interface &_neopixel) :
            neopixel(_neopixel),
            active_program(*this),
            alert_program(*this),
            freeze_program(*this),
            idle_program(*this),
            off_program(*this),
            ready_program(*this),
            service_program(*this)
        {
        }

        virtual void initialize();
        virtual void shutdown();
        virtual void perform();

        inline bool is_busy(void) const { return !(left.is_stable() && right.is_stable()); };

        inline virtual SmartLed &get_left() override { return left; }
        inline virtual SmartLed &get_right() override { return right; }

        void set_program(const PROGRAM);
        virtual void color(const Color &_left, const Color &_right, const uint64_t _steps) override;
        virtual void draw() override;
        void clean();

      private:
        neopixel::Interface &neopixel;
        pulp::COMPONENT_STATE state{pulp::COMPONENT_STATE::UNDEFINED};

        SmartLed left;
        SmartLed right;
        PROGRAM program{PROGRAM::UNDEFINED};

        program::active::Instance active_program;
        program::alert::Instance alert_program;
        program::freeze::Instance freeze_program;
        program::idle::Instance idle_program;
        program::off::Instance off_program;
        program::ready::Instance ready_program;
        program::service::Instance service_program;
    };
}
