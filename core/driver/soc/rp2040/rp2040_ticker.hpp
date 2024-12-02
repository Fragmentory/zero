/**
 * \file rp2040_ticker.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief ticker

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#pragma once

#include "board_defines.hpp"
#include "component_interface.hpp"
#include "component_state.hpp"

#include <cmath>
#include <hardware/timer.h>

namespace core
{
    namespace soc
    {
        struct RP2040Ticker : public pulp::ComponentInterface
        {
            virtual ~RP2040Ticker() {}

            /*
                Negative delay so means we will call timer callback, and call it again
                TICKER_DELAY us later regardless of how long the callback took to execute.
            */
            static const int32_t TICKER_DELAY;

            void set_callback(pulp::ticker::Callback &);

            virtual void initialize(void) override;
            virtual void shutdown(void) override;

            uint32_t time_ms2ticks(const float _time_ms) const
            {
                return static_cast<uint32_t>(std::round(_time_ms * 1000.0f / static_cast<float>(std::abs(TICKER_DELAY))));
            }

            /* please do not use this function in productive code */
            void delay_ms(uint32_t);

          private:
            pulp::COMPONENT_STATE state{pulp::COMPONENT_STATE::UNDEFINED};
        };
    }
}
