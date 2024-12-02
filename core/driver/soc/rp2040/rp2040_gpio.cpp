/**
 * \file rp2040_gpio.cpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief Handle internal gpio sensor

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include "rp2040_gpio.hpp"

#include "component_state.hpp"
#include "soc_variant.hpp"

#include <hardware/gpio.h>
#include <pico/stdlib.h>

namespace core
{
    namespace soc
    {
        core::board::callback_t gpio_handler = nullptr;

        static pulp::COMPONENT_STATE status = pulp::COMPONENT_STATE::UNDEFINED;

        void gpio_callback(uint _gpio, uint32_t _events)
        {
            static bool pin_state[Variant::DEBUG_PIN_NUMBER] = {false};

            if (gpio_handler == nullptr)
                return;

            uint8_t identifier = 0xff;
            for (uint8_t i = 0; i < Variant::DEBUG_PIN_NUMBER; ++i)
            {
                if (_gpio == Variant::DEBUG_PIN[i])
                {
                    identifier = Variant::DEBUG_PIN[i];
                    break;
                }
            }

            bool state_changed = false;
            if (_events & 0x01)
            {
                /* low level */
            }
            else if (_events & 0x02)
            {
                /* high level */
            }
            else if (_events & 0x04)
            {
                /* fall edge */
                if (pin_state[identifier] == true)
                {
                    state_changed = true;
                    pin_state[identifier] = false;
                }
            }
            else if (_events & 0x08)
            {
                /* rise edge */
                if (pin_state[identifier] == false)
                {
                    state_changed = true;
                    pin_state[identifier] = true;
                }
            }

            if (state_changed)
            {
                state_changed = false;
                gpio_handler(identifier, pin_state[identifier]);
            }
        }

        /**
         * \brief Initialize ADC and internal gpio sensor
         */
        void RP2040Gpio::initialize(void)
        {
            assert(status == pulp::COMPONENT_STATE::UNDEFINED);
            status = pulp::COMPONENT_STATE::IDLE;

            for (uint8_t i = 0; i < Variant::DEBUG_PIN_NUMBER; ++i)
            {
                gpio_instance[i] = Variant::DEBUG_PIN[i];
                gpio_init(gpio_instance[i]);
                gpio_set_dir(gpio_instance[i], GPIO_OUT);
            }
        }

        void RP2040Gpio::shutdown()
        {
            assert(status == pulp::COMPONENT_STATE::IDLE);
            status = pulp::COMPONENT_STATE::UNDEFINED;

            /* todo: restore default state */
        }

        void RP2040Gpio::enable_event(core::board::callback_t _callback)
        {
            assert(status == pulp::COMPONENT_STATE::IDLE);

            gpio_handler = _callback;
            for (uint8_t i = 0; i < Variant::DEBUG_PIN_NUMBER; ++i)
            {
                gpio_set_irq_enabled_with_callback(Variant::DEBUG_PIN[i], GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &gpio_callback);
            }
        }

        void RP2040Gpio::disable_event(void)
        {
            assert(status == pulp::COMPONENT_STATE::IDLE);

            for (uint8_t i = 0; i < Variant::DEBUG_PIN_NUMBER; ++i)
            {
                gpio_set_irq_enabled(Variant::DEBUG_PIN[i], GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, false);
            }
            gpio_handler = nullptr;
        }

        core::board::DIRECTION RP2040Gpio::get_direction(const uint8_t _identifier) const
        {
            return gpio_get_dir(gpio_instance[_identifier]) == GPIO_OUT ? DIRECTION::OUTPUT : DIRECTION::INPUT;
        }

        void RP2040Gpio::set_direction(const uint8_t _identifier, const core::board::DIRECTION _direction)
        {
            if (_direction == DIRECTION::INPUT)
            {
                set_pulls(_identifier, true, false);
            }
            else
            {
                set_pulls(_identifier, false, false);
            }
            gpio_set_dir(gpio_instance[_identifier], _direction == DIRECTION::INPUT ? GPIO_IN : GPIO_OUT);
        }

        void RP2040Gpio::set_pulls(const uint8_t _identifier, const bool _up, const bool _down) { gpio_set_pulls(gpio_instance[_identifier], _up, _down); }

        core::board::VALUE RP2040Gpio::get_value(const uint8_t _identifier) const
        {
            if (get_direction(_identifier) != DIRECTION::UNDEFINED)
            {
                return gpio_get(gpio_instance[_identifier]) == 0 ? VALUE::LOW : VALUE::HIGH;
            }

            return VALUE::UNDEFINED;
        }

        void RP2040Gpio::set_value(const uint8_t _identifier, const core::board::VALUE _value) const
        {
            if (get_direction(_identifier) == DIRECTION::OUTPUT)
            {
                gpio_put(gpio_instance[_identifier], _value == VALUE::HIGH ? true : false);
            }
        }
    }
}
