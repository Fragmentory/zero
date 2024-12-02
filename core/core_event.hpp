/**
 * \file core_event.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "engine_defines.hpp"
#include "event_bus.hpp"

namespace core
{
    namespace event
    {
        struct Busy : public pulp::event::Type<Busy>
        {
        };

        struct Free : public pulp::event::Type<Free>
        {
        };

        struct Restart : public pulp::event::Type<Restart>
        {
        };

        struct Bootsel : public pulp::event::Type<Bootsel>
        {
        };
    }
}