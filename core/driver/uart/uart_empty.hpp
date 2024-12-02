/**
 * \file uart_empty.hpp
 * \author Roman Koch koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "uart_handler.hpp"

#include <cstdio>
#include <hardware/uart.h>

namespace core
{
    namespace driver
    {
        namespace uart
        {
            struct Empty
            {
                static Empty &get_instance()
                {
                    static Empty instance;
                    return instance;
                }
                Empty(Empty const &) = delete;
                void operator=(Empty const &) = delete;

                static const unsigned int USART_SPACE_SIZE = 0;
                static const int BAUD_RATE = 0;
                static const int DATA_BITS = 0;
                static const int STOP_BITS = 0;
                static const uart_parity_t PARITY = UART_PARITY_NONE;
                static const int UART_TX_PIN = -1;
                static const int UART_RX_PIN = -1;
                static const int UART_IRQ = -1;

                void initialize() {}
                void shutdown() {}
                void perform() {}
                void set_handler(rx_tx_handler_t) {}
                void last_whisper(uint8_t) {}
                int uart_putchar(char, FILE *) { return 0; }

              private:
                Empty() {}
            };
        }
    }
}
