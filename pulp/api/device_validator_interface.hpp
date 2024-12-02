/**
 * \file device_validator_interface.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "active_component_interface.hpp"

#include <cstdint>

namespace pulp
{
    namespace check
    {
        struct DeviceValidator : public ActiveComponentInterface
        {
            virtual bool is_done() = 0;
        };
    }
}