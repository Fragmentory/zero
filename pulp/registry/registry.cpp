/**
 * \file registry.cpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief configure node components with persistent parameter

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include "registry.hpp"

#include "checksum.hpp"
#include "chunk.h"
#include "macros.hpp"
#include "parameter.hpp"
#include "pulp.hpp"

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/* If FORMAT_PARAMETER_REGISTRY was defined, the registry memory and backup will be recreated */
#define _FORMAT_PARAMETER_REGISTRY

namespace pulp
{
    namespace registry
    {
        /** \brief Node configuration state */
        typedef enum
        {
            UNDEFINED,
            READY,
        } status_t;

        static status_t status = UNDEFINED;

        static void node_config_init(void);

        void Instance::initialize(void)
        {

#if defined(FORMAT_PARAMETER_REGISTRY)
            /* format parameter storage */
            parameter::param_format();
            parameter::param_backup_create();
#endif
            /* configure node */
            if (parameter::param_check() == FAILURE)
            {
                parameter::param_format();
                notification::Event event{notification::CAUSE::RESET, notification::EVENT::PARAMETER_MISSED};
                notify.handle(event);
            }

            node_config_init();
            if (is_ready() == SUCCESS)
            {
                if (parameter::param_backup_check() == FAILURE)
                {
                    parameter::param_backup_create();
                    notification::Event event{notification::CAUSE::RESET, notification::EVENT::BACKUP_CREATED};
                    notify.handle(event);
                }
            }
            else
            {
                notification::Event event{notification::CAUSE::RESET, notification::EVENT::CRITICAL_ERROR};
                notify.handle(event);
                if (parameter::param_backup_restore() != SUCCESS)
                {
                    parameter::param_backup_create();
                    notification::Event event{notification::CAUSE::RESET, notification::EVENT::BACKUP_CREATED};
                    notify.handle(event);
                }
            }
        }

        /**
            \brief cancel configuration
        */
        void Instance::shutdown(void)
        {
            assert(status == READY); // state should be initialized
            /* do nothing */
            status = UNDEFINED;
        }

        /**
            \brief Function returns success if node configuration state is valid
        */
        result_t Instance::is_ready(void) const
        {
            if (status == READY)
            {
                return SUCCESS;
            }
            return FAILURE;
        }

        /**
        \brief Initialize parameter storage and load parameter from persistent memory

        This function load stored parameter values from persistent memory.
        Parameter-Functions sets the proper values.
        */
        static void node_config_init(void)
        {
            assert(status == UNDEFINED); // state should be undefined

            if (parameter::param_load() == FAILURE)
                return;

            /* all right */
            status = READY;
        }
    }
}
