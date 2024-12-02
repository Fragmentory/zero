/**
 * \file uart_first.hpp
 * \author Roman Koch koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "active_component_interface.hpp"
#include "uart_buffer.hpp"
#include "uart_handler.hpp"
#include "uart_variant.hpp"

#include <cstdio>
#include <hardware/sync.h>
#include <pico/stdlib.h>

namespace core
{
    namespace driver
    {
        namespace uart
        {
            class InterruptGuard
            {
              public:
                InterruptGuard() :
                    state(save_and_disable_interrupts())
                {
                }
                ~InterruptGuard() { restore_interrupts(state); }

                InterruptGuard(const InterruptGuard &) = delete;
                InterruptGuard &operator=(const InterruptGuard &) = delete;
                InterruptGuard(InterruptGuard &&) = delete;
                InterruptGuard &operator=(InterruptGuard &&) = delete;

              private:
                uint32_t state;
            };

            template <typename V>
            struct Instance : public pulp::ActiveComponentInterface
            {
                static Instance &get_instance()
                {
                    static Instance instance;
                    return instance;
                }
                Instance(Instance const &) = delete;
                void operator=(Instance const &) = delete;

                virtual void initialize() override
                {
                    bytering_init(&uart_buffer.rx_buffer, uart_buffer.rx_space, V::USART_SPACE_SIZE);
                    bytering_init(&uart_buffer.tx_buffer, uart_buffer.tx_space, V::USART_SPACE_SIZE);

                    uart_deinit(uart_instance);
                    uart_init(uart_instance, V::BAUD_RATE);

                    gpio_set_function(V::UART_TX_PIN, GPIO_FUNC_UART);
                    gpio_set_function(V::UART_RX_PIN, GPIO_FUNC_UART);

                    int __unused actual = uart_set_baudrate(uart_instance, V::BAUD_RATE);

                    uart_set_hw_flow(uart_instance, false, false);
                    uart_set_format(uart_instance, V::DATA_BITS, V::STOP_BITS, V::PARITY);
                    uart_set_fifo_enabled(uart_instance, false);

                    irq_set_exclusive_handler(V::UART_IRQ, on_uart_irq);
                    irq_set_enabled(V::UART_IRQ, true);

                    /* enable RX-IRQ */
                    uart_set_irq_enables(uart_instance, true, false);
                }

                virtual void shutdown() override
                {
                    uart_set_irq_enables(uart_instance, false, false);
                    uart_deinit(uart_instance);
                    gpio_set_function(V::UART_TX_PIN, GPIO_FUNC_NULL);
                    gpio_set_function(V::UART_RX_PIN, GPIO_FUNC_NULL);
                }

                virtual void perform() override
                {
                    InterruptGuard guard;

                    if (rx_tx_handler != NULL)
                    {
                        /* data handler needs to be set */
                        rx_tx_handler(&uart_buffer.rx_buffer, &uart_buffer.tx_buffer);
                    }
                    else
                    {
                        uart_buffer.echo();
                    }

                    if (uart_buffer.tx_buffer.number_of_free_items < V::USART_SPACE_SIZE)
                    {
                        /* enable TX-IRQ */
                        uart_set_irq_enables(uart_instance, true, true);
                        send_bytes();
                    }
                    else
                    {
                        uart_set_irq_enables(uart_instance, true, false);
                    }
                }

                void set_handler(rx_tx_handler_t handler) { rx_tx_handler = handler; }

                void send_bytes() { _send_byte_to_tx(); }

                /**
                    \brief Print a byte

                    This function should be used in emergency case only.
                    All the timings can be destroyed trough this call.
                */
                void last_whisper(uint8_t const _byte) { uart_putc(uart_instance, _byte); }

                /**
                    \brief Definition of the output function for printf
                */
                int uart_putchar(char c, FILE *stream)
                {
                    (void)stream;
                    InterruptGuard guard;
                    bytering_write(&uart_buffer.tx_buffer, c);
                    return 0;
                }

              private:
                rx_tx_handler_t rx_tx_handler = nullptr;

                static Buffer uart_buffer;

                /* Attention: Buffer size should be a power of 2 value (l.u. byte ring implementation) */
                static uint8_t rx_space[V::USART_SPACE_SIZE];
                static uint8_t tx_space[V::USART_SPACE_SIZE];

                static uart_inst_t *uart_instance;

                Instance()
                {
                    uart_buffer.rx_space = rx_space;
                    uart_buffer.tx_space = tx_space;

                    uart_instance = ((uart_inst_t *)((uart_hw_t *)V::UART_BASE));
                }

                static void on_uart_irq()
                {
                    /* todo: handle error flags */
                    while (uart_is_readable(uart_instance))
                    {
                        const uint8_t byte = uart_getc(uart_instance);
                        bytering_write(&uart_buffer.rx_buffer, byte);
                    }
                    _send_byte_to_tx();
                }

                static void _send_byte_to_tx()
                {
                    uint8_t byte;
                    if (bytering_peek(&uart_buffer.tx_buffer, 0, &byte))
                    {
                        if (uart_is_writable(uart_instance))
                        {
                            bytering_read(&uart_buffer.tx_buffer, &byte);
                            uart_putc(uart_instance, byte);
                        }
                    }
                    else
                    {
                        uart_set_irq_enables(uart_instance, true, false);
                    }
                }
            };

            template <typename V>
            Buffer Instance<V>::uart_buffer;

            template <typename V>
            uint8_t Instance<V>::rx_space[V::USART_SPACE_SIZE];

            template <typename V>
            uint8_t Instance<V>::tx_space[V::USART_SPACE_SIZE];

            template <typename V>
            uart_inst_t *Instance<V>::uart_instance;
        }
    }
}
