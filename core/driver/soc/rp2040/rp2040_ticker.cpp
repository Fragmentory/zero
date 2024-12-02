/**
 * \file rp2040_ticker.cpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief Ticker

    Create a repeating timer that calls timer callback.

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include "rp2040_ticker.hpp"

#include "macros.hpp"
#include "soc_variant.hpp"

#include <assert.h>
#include <cstdio>
#include <hardware/gpio.h>
#include <pico/stdlib.h>
#include <pico/time.h>

namespace core
{
    namespace soc
    {
        pulp::ticker::Callback *callback = nullptr;

        const int32_t RP2040Ticker::TICKER_DELAY = Variant::DEFAULT_TICKER_DELAY_US;

        struct repeating_timer timer;
        static bool timer_callback(struct repeating_timer *const _timer);

        void RP2040Ticker::set_callback(pulp::ticker::Callback &_callback)
        {
            /* Attention: set callback before initialization! */
            assert(state == pulp::COMPONENT_STATE::UNDEFINED);

            callback = &_callback;
        }

        /**
            \brief Start a repeating timer that calls timer callback.

            If the delay is > 0 then this is the delay between the previous callback ending and the next starting.
            If the delay is negative (see below) then the next call to the callback will be exactly TICKER_DELAY ms
            after the start of the call to the last callback.
        */
        void RP2040Ticker::initialize(void)
        {
            assert(state == pulp::COMPONENT_STATE::UNDEFINED);
            state = pulp::COMPONENT_STATE::IDLE;

            assert(callback != nullptr && "ticket callback not set");
            add_repeating_timer_us(TICKER_DELAY, core::soc::timer_callback, NULL, &core::soc::timer);
        }

        void RP2040Ticker::shutdown(void)
        {
            assert(state != pulp::COMPONENT_STATE::UNDEFINED);
            cancel_repeating_timer(&core::soc::timer);
        }

        void RP2040Ticker::delay_ms(uint32_t value) { sleep_ms(value); }

        static bool timer_callback(struct repeating_timer *const _timer)
        {
            (void)_timer;
            if (callback != nullptr)
            {
                static bool execution_flag = false;
                // assert on execution_flag
                if (!execution_flag)
                {
                    execution_flag = true;
                    callback->invoke();
                    execution_flag = false;
                }
            }
            return true;
        }
    }
}
