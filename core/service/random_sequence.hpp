/**
 * \file random.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief Random number and sequences generator

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#pragma once

#include "chunk.h"
#include "component_interface.hpp"
#include "component_state.hpp"
#include "temperature_interface.hpp"

namespace core::service
{
    struct RandomSequence : public pulp::ComponentInterface
    {
        RandomSequence(pulp::temperature::Interface &_temperature) :
            temperature(_temperature)
        {
        }
        virtual ~RandomSequence() {}

        virtual void initialize() override;
        virtual void shutdown() override;

        void create(chunk_t &) const;

      private:
        pulp::temperature::Interface &temperature;
        pulp::COMPONENT_STATE state{pulp::COMPONENT_STATE::UNDEFINED};
    };
}
