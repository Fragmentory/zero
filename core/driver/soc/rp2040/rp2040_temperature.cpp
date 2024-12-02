/**
 * \file rp2040_temperature.cpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief Handle internal temperature sensor

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include "rp2040_temperature.hpp"

#include "component_state.hpp"

#include <hardware/adc.h>
#include <pico/stdlib.h>

namespace core
{
    namespace soc
    {
        static pulp::COMPONENT_STATE status = pulp::COMPONENT_STATE::UNDEFINED;

        /**
         * \brief Initialize ADC and internal temperature sensor
         */
        void RP2040Temperature::initialize(void)
        {
            assert(status == pulp::COMPONENT_STATE::UNDEFINED);
            status = pulp::COMPONENT_STATE::IDLE;

            adc_init();
            adc_set_temp_sensor_enabled(true);
            adc_select_input(4);
            // adc_disable();
        }

        void RP2040Temperature::shutdown() {}

        /**
            \brief Return ADC value
        */
        uint16_t RP2040Temperature::get_raw_value(void) const
        {
            assert(status == pulp::COMPONENT_STATE::IDLE);

            (void)adc_read();
            return adc_read();
        }

        /**
         * \brief Get current chip temperature from internal sensor
         *
         * \return scaled float temperature value
         */
        float RP2040Temperature::get_value(void) const
        {
            uint16_t raw = get_raw_value();
            const float conversion = 3.3f / (1 << 12);
            float voltage = raw * conversion;
            float value = 27.0f - (voltage - 0.706f) / 0.001721f;
            return value;
        }
    }
}
