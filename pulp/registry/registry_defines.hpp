/**
 * \file registry_defines.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "macros.hpp"

#include <cstdint>
#include <cstdlib>

namespace pulp
{
    namespace registry
    {
        static const size_t PARAMETER_BUFFER_SIZE{128};

        enum result_t
        {
            SUCCESS = common::result::SUCCESS,
            FAILURE = common::result::FAILURE,
            ERROR = common::result::ERROR,
        };
    }
}