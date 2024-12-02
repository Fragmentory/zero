/**
 * \file parameter.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief Configuration parameter storage

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#pragma once

#include "macros.hpp"
#include "registry_defines.hpp"

#include <cstdint>

namespace pulp
{
    namespace registry
    {
        namespace parameter
        {
            extern result_t param_load(void);
            extern result_t param_format(void);
            extern result_t param_check(void);
            extern result_t param_save(void);

            extern result_t param_backup_check(void);
            extern result_t param_backup_create(void);
            extern result_t param_backup_restore(void);

            extern void debug_out_mem();

            extern uint8_t *const g_param_address;
            extern uint8_t *const g_param_audio;
            extern uint8_t *const g_param_charger;
            extern uint8_t *const g_param_features;
            extern uint8_t *const g_param_load;
            extern uint8_t *const g_param_maintainer;
            extern uint8_t *const g_param_name;
            extern uint8_t *const g_param_position;
            extern uint8_t *const g_param_serial_number;
            extern uint8_t *const g_param_unique_identifier;
            extern uint8_t *const g_param_user;
            extern uint8_t *const g_param_visual;

            extern result_t address_store(uint8_t *const _param);
            extern result_t audio_store(uint8_t *const _param);
            extern result_t charger_store(uint8_t *const _param);
            extern result_t features_store(uint8_t *const _param);
            extern result_t load_store(uint8_t *const _param);
            extern result_t maintainer_store(uint8_t *const _param);
            extern result_t name_store(uint8_t *const _param);
            extern result_t position_store(uint8_t *const _param);
            extern result_t serial_number_store(uint8_t *const _param);
            extern result_t unique_identifier_store(uint8_t *const _param);
            extern result_t user_store(uint8_t *const _param);
            extern result_t visual_store(uint8_t *const _param);

            extern result_t address_load(uint8_t *const _source);
            extern result_t audio_load(uint8_t *const _source);
            extern result_t charger_load(uint8_t *const _source);
            extern result_t features_load(uint8_t *const _source);
            extern result_t load_load(uint8_t *const _source);
            extern result_t maintainer_load(uint8_t *const _source);
            extern result_t name_load(uint8_t *const _source);
            extern result_t position_load(uint8_t *const _source);
            extern result_t serial_number_load(uint8_t *const _source);
            extern result_t unique_identifier_load(uint8_t *const _source);
            extern result_t user_load(uint8_t *const _source);
            extern result_t visual_load(uint8_t *const _source);
        }
    }
}