/**
 * \file registry.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief Configuration parameter

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#pragma once

#include "component_interface.hpp"
#include "macros.hpp"
#include "random_sequence.hpp"
#include "registry_defines.hpp"
#include "registry_notification.hpp"

namespace pulp
{
    namespace registry
    {
        struct Instance : public pulp::ComponentInterface
        {
            Instance(notification::Interface &_notify, core::service::RandomSequence &_random_sequence) :
                notify(_notify),
                random_sequence(_random_sequence)
            {
            }
            virtual ~Instance() {}

            virtual void initialize(void) override;
            virtual void shutdown(void) override;

            virtual result_t is_ready(void) const;

          private:
            notification::Interface &notify;
            core::service::RandomSequence &random_sequence;
        };
    }
}
