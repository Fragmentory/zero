/**
 * \file parameter.cpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief Parameter data base

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include "parameter.hpp"

#include "checksum.hpp"
#include "chunk.h"
#include "macros.hpp"
#include "param_address.hpp"
#include "param_audio.hpp"
#include "param_charger.hpp"
#include "param_features.hpp"
#include "param_load.hpp"
#include "param_maintainer.hpp"
#include "param_name.hpp"
#include "param_position.hpp"
#include "param_serial_number.hpp"
#include "param_unique_identifier.hpp"
#include "param_user.hpp"
#include "param_visual.hpp"
#include "parameter_identifier.hpp"

#include <hardware/flash.h>
#include <hardware/sync.h>
#include <string.h>

#define _DEBUG_MEMORY_PRINTOUT

namespace pulp
{
    namespace registry
    {
        namespace parameter
        {
            constexpr size_t REGISTRY_OFFSET = (FLASH_PAGE_SIZE * 4096);
            constexpr size_t REGISTRY_FLASH_START = (XIP_BASE + REGISTRY_OFFSET);
            constexpr size_t REGISTRY_BACKUP_OFFSET = (REGISTRY_OFFSET + FLASH_SECTOR_SIZE);
            constexpr size_t REGISTRY_BACKUP_FLASH_START = (XIP_BASE + REGISTRY_BACKUP_OFFSET);

            constexpr size_t PARAM_CONTENT_OFFSET = 2;

            template <typename T, size_t _offset = PARAM_CONTENT_OFFSET>
            constexpr size_t param_size()
            {
                return sizeof(T) + _offset;
            }

            template <typename T, size_t _offset = PARAM_CONTENT_OFFSET>
            uint8_t *param_ptr(uint8_t *_base)
            {
                return _base + sizeof(T) + _offset;
            }
            /**
                \name Parameter storage (RAM)

                Size of all the parameter and 2 bytes CRC-16 (XMODEM)
            */

            template <typename R, IDENTIFIER _identifier, R &_register>
            result_t param_store(uint8_t *const _param)
            {
                // Speichern der Steuerinformationen
                _param[0] = static_cast<uint8_t>(_identifier);
                _param[1] = sizeof(R);

                // Speichern des Werts
                for (uint8_t i = 0; i < sizeof(R); ++i)
                {
                    _param[2 + i] = _register.byte[i];
                }

                return SUCCESS;
            }

            template <typename R, IDENTIFIER _identifier, R &_register>
            result_t param_load(uint8_t *const _param)
            {
                const IDENTIFIER identifier = static_cast<IDENTIFIER>(_param[0]);
                const uint8_t length = _param[1];

                if (identifier != _identifier || length != sizeof(R))
                {
                    _register.initialize();
                    return FAILURE;
                }

                for (uint8_t i = 0; i < sizeof(R); ++i)
                {
                    _register.byte[i] = _param[2 + i];
                }

                return SUCCESS;
            }

            /* @{ */
            uint8_t *const registry_start = (uint8_t *)REGISTRY_FLASH_START;
            uint8_t *const param_start = registry_start;

            extern uint8_t *const g_param_address = param_start;
            extern uint8_t *const g_param_audio = param_ptr<address::register_t>(g_param_address);
            extern uint8_t *const g_param_charger = param_ptr<audio::register_t>(g_param_audio);
            extern uint8_t *const g_param_features = param_ptr<charger::register_t>(g_param_charger);
            extern uint8_t *const g_param_load = param_ptr<features::register_t>(g_param_features);
            extern uint8_t *const g_param_maintainer = param_ptr<load::register_t>(g_param_load);
            extern uint8_t *const g_param_name = param_ptr<maintainer::register_t>(g_param_maintainer);
            extern uint8_t *const g_param_position = param_ptr<name::register_t>(g_param_name);
            extern uint8_t *const g_param_serial_number = param_ptr<position::register_t>(g_param_position);
            extern uint8_t *const g_param_unique_identifier = param_ptr<serial_number::register_t>(g_param_serial_number);
            extern uint8_t *const g_param_user = param_ptr<unique_identifier::register_t>(g_param_unique_identifier);
            extern uint8_t *const g_param_visual = param_ptr<user::register_t>(g_param_user);

            uint8_t *const param_crc = param_ptr<visual::register_t>(g_param_visual);

            uint8_t *const param_stop = param_ptr<uint16_t, 0>(param_crc);
            /* @} */

            /**
                \name Parameter backup (RAM)

                Size: l.u.
            */
            /* @{ */
            uint8_t *const backup_start = (uint8_t *)REGISTRY_BACKUP_FLASH_START;

            uint8_t *const backup_address = backup_start;
            uint8_t *const backup_audio = param_ptr<address::register_t>(backup_address);
            uint8_t *const backup_charger = param_ptr<audio::register_t>(backup_audio);
            uint8_t *const backup_features = param_ptr<charger::register_t>(backup_charger);
            uint8_t *const backup_load = param_ptr<features::register_t>(backup_features);
            uint8_t *const backup_maintainer = param_ptr<load::register_t>(backup_load);
            uint8_t *const backup_name = param_ptr<maintainer::register_t>(backup_maintainer);
            uint8_t *const backup_position = param_ptr<name::register_t>(backup_name);
            uint8_t *const backup_serial_number = param_ptr<position::register_t>(backup_position);
            uint8_t *const backup_unique_identifier = param_ptr<serial_number::register_t>(backup_serial_number);
            uint8_t *const backup_user = param_ptr<unique_identifier::register_t>(backup_unique_identifier);
            uint8_t *const backup_visual = param_ptr<user::register_t>(backup_user);

            uint8_t *const backup_crc = param_ptr<visual::register_t>(backup_visual);

            uint8_t *const backup_stop = param_ptr<uint16_t, 0>(backup_crc);

            uint8_t *const registry_stop = backup_stop;
            /* @} */

            static uint16_t calculate_crc(uint8_t *const _target, size_t _size);
            static uint16_t checksum_calculation(const uint8_t *_param, const size_t _size, const uint16_t _result);

            static result_t param_save(uint8_t *const _target);

#if defined(DEBUG_MEMORY_PRINTOUT)
#include <stdio.h>
#endif

            extern void debug_out_mem()
            {
#if defined(DEBUG_MEMORY_PRINTOUT)
                {
                    const size_t param_size = param_crc - param_start;
                    const size_t block_size = param_stop - param_start;
                    printf("param  mem %d/%d\n", param_size, block_size);
                    int cntr = 0;
                    for (size_t i = 0; i < block_size; ++i)
                    {
                        printf("%02x ", param_start[i]);
                        if (++cntr > 9)
                        {
                            cntr = 0;
                            printf("\n");
                        }
                    }
                    printf("\n");
                }
                {
                    const size_t param_size = param_crc - param_start;
                    const size_t block_size = param_stop - param_start;
                    printf("backup mem %d/%d\n", param_size, block_size);
                    int cntr = 0;
                    for (size_t i = 0; i < block_size; ++i)
                    {
                        printf("%02x ", backup_start[i]);
                        if (++cntr > 9)
                        {
                            cntr = 0;
                            printf("\n");
                        }
                    }
                    printf("\n");
                }
#endif
            }

            /**
             * \brief Load parameter values from persistent memory
             *
             * \return result_t
             */
            extern result_t param_load(void)
            {
                /* Attention: do not load user parameter */
                if (address_load(g_param_address) == FAILURE || audio_load(g_param_audio) == FAILURE || charger_load(g_param_charger) == FAILURE
                    || features_load(g_param_features) == FAILURE || load_load(g_param_load) == FAILURE || maintainer_load(g_param_maintainer) == FAILURE
                    || name_load(g_param_name) == FAILURE || position_load(g_param_position) == FAILURE || serial_number_load(g_param_serial_number) == FAILURE
                    || unique_identifier_load(g_param_unique_identifier) == FAILURE || visual_load(g_param_visual) == FAILURE)
                {
                    return FAILURE;
                }

                srand((int)parameter::unique_identifier::g_unique_key);

                debug_out_mem();

                return SUCCESS;
            }

            /**
                \brief Erase a sector with parameter data page and backup page

                Unsafe.
            */
            extern result_t param_format(void)
            {
                /* clean up memory */
                uint32_t ints = save_and_disable_interrupts();
                flash_range_erase(REGISTRY_OFFSET, FLASH_SECTOR_SIZE);
                restore_interrupts(ints);

                /* create node parameter */
                address::g_register.initialize();
                audio::g_register.initialize();
                charger::g_register.initialize();
                features::g_register.initialize();
                load::g_register.initialize();
                maintainer::g_register.initialize();
                name::g_register.initialize();
                position::g_register.initialize();
                serial_number::g_register.initialize();
                unique_identifier::g_register.initialize();
                user::g_register.initialize();
                visual::g_register.initialize();

                result_t save_result = param_save(registry_start);

                debug_out_mem();

                return save_result;
            }

            /**
                \brief Calculate and check parameter CRC-16
            */
            extern result_t param_check(void)
            {
                const uint16_t old_crc_value = common::macro::SETWORD(param_crc[0], param_crc[1]);
                const size_t size = param_crc - param_start;
                const uint16_t new_crc_value = calculate_crc(param_start, size);
#if defined(DEBUG_MEMORY_PRINTOUT)
                printf("param check old crc: %04x\n", old_crc_value);
                printf("param check new crc %d: %04x\n", size, new_crc_value);
#endif
                if (old_crc_value == new_crc_value)
                {
                    return SUCCESS;
                }
                return FAILURE;
            }

            /**
                \brief Store parameter persistently
            */
            extern result_t param_save(void) { return param_save(registry_start); }

            /**
                \brief Calculate and check backup CRC-16
            */
            extern result_t param_backup_check(void)
            {
                const uint16_t old_crc_value = common::macro::SETWORD(backup_crc[0], backup_crc[1]);
                const size_t size = backup_crc - backup_start;
                const uint16_t new_crc_value = calculate_crc(backup_start, size);
#if defined(DEBUG_MEMORY_PRINTOUT)
                printf("backup check old crc: %04x\n", old_crc_value);
                printf("backup check new crc %d: %04x\n", size, new_crc_value);
#endif
                if (old_crc_value == new_crc_value)
                {
                    return SUCCESS;
                }
                return FAILURE;
            }

            /**
                \brief a very, very simple implementation

                store data
            */
            extern result_t param_backup_create(void)
            {
                /* load node parameter */
                address_load(g_param_address);
                audio_load(g_param_audio);
                charger_load(g_param_load);
                features_load(g_param_features);
                load_load(g_param_load);
                maintainer_load(g_param_maintainer);
                name_load(g_param_name);
                position_load(g_param_position);
                serial_number_load(g_param_serial_number);
                unique_identifier_load(g_param_unique_identifier);
                user_load(g_param_user);
                visual_load(g_param_visual);

                return param_save(backup_start);
            }

            /**
                \brief a very, very simple implementation

                CRC calculation over the params?
            */
            extern result_t param_backup_restore(void)
            {
                /* node parameter */
                address_load(backup_address);
                audio_load(backup_audio);
                charger_load(backup_charger);
                features_load(backup_features);
                load_load(backup_load);
                maintainer_load(backup_maintainer);
                name_load(backup_name);
                position_load(backup_position);
                serial_number_load(backup_serial_number);
                unique_identifier_load(backup_unique_identifier);
                user_load(backup_user);
                visual_load(backup_visual);

                param_save(registry_start);

                /* Check restore process result */
                uint16_t param_crc_value = common::macro::SETWORD(param_crc[0], param_crc[1]);
                uint16_t backup_crc_value = common::macro::SETWORD(backup_crc[0], backup_crc[1]);

                if (backup_crc_value == param_crc_value)
                {
                    return SUCCESS;
                }
                return FAILURE;
            }

            static uint16_t checksum_calculation(const uint8_t *_param, const size_t _size, const uint16_t _result)
            {
                uint16_t result = _result;

                for (uint8_t i = 0; i < _size; ++i)
                {
                    result = checksum_crc_byte(_param[i], result);
                }
                return result;
            }

            /**
                \brief CRC-16 calculation
            */
            static uint16_t calculate_crc(uint8_t *const _target, size_t _size)
            {
                const uint16_t value = checksum_calculation(_target, _size, 0);
                return value;
            }

            static result_t param_save(uint8_t *const _target)
            {
                /* read flash page */
                uint8_t data[FLASH_PAGE_SIZE] = {0xff};
                for (uint32_t i = 0; i < FLASH_PAGE_SIZE; ++i)
                {
                    data[i] = _target[i];
                }

                uint8_t const *const start = data;
                uint8_t *data_ptr = data;

                /* store parameter into the RAM array */
                address_store(data_ptr);
                data_ptr += param_size<address::register_t>();

                audio_store(data_ptr);
                data_ptr += param_size<audio::register_t>();

                charger_store(data_ptr);
                data_ptr += param_size<charger::register_t>();

                features_store(data_ptr);
                data_ptr += param_size<features::register_t>();

                load_store(data_ptr);
                data_ptr += param_size<load::register_t>();

                maintainer_store(data_ptr);
                data_ptr += param_size<maintainer::register_t>();

                name_store(data_ptr);
                data_ptr += param_size<name::register_t>();

                position_store(data_ptr);
                data_ptr += param_size<position::register_t>();

                serial_number_store(data_ptr);
                data_ptr += param_size<serial_number::register_t>();

                unique_identifier_store(data_ptr);
                data_ptr += param_size<unique_identifier::register_t>();

                user_store(data_ptr);
                data_ptr += param_size<user::register_t>();

                visual_store(data_ptr);
                data_ptr += param_size<visual::register_t>();

                const size_t size = data_ptr - start;
                const uint16_t crc = calculate_crc(data, size);
#if defined(DEBUG_MEMORY_PRINTOUT)
                printf("param save new crc %d: ", size);
                printf("%04x\n", crc);
#endif
                *data_ptr = common::macro::HIBYTE(crc);
                data_ptr++;
                *data_ptr = common::macro::LOBYTE(crc);
                data_ptr++;

                /* store byte to the flash */
                uint32_t offset = (uint32_t)_target - XIP_BASE;

                uint32_t ints = save_and_disable_interrupts();
                flash_range_erase(offset, FLASH_SECTOR_SIZE);
                flash_range_program(offset, data, FLASH_PAGE_SIZE);
                restore_interrupts(ints);

                bool mismatch = false;
                for (uint32_t i = 0; i < FLASH_PAGE_SIZE; ++i)
                {
                    if (data[i] != _target[i])
                    {
                        mismatch = true;
                    }
                }

                if (mismatch == true)
                {
                    return FAILURE;
                }

                return SUCCESS;
            }

            extern result_t address_store(uint8_t *const _param) { return param_store<address::register_t, IDENTIFIER::ADDRESS, address::g_register>(_param); }

            extern result_t audio_store(uint8_t *const _param) { return param_store<audio::register_t, IDENTIFIER::AUDIO_FEEDBACK, audio::g_register>(_param); }

            extern result_t charger_store(uint8_t *const _param)
            {
                return param_store<charger::register_t, IDENTIFIER::CHARGER_CALIB, charger::g_register>(_param);
            }

            extern result_t features_store(uint8_t *const _param)
            {
                return param_store<features::register_t, IDENTIFIER::FEATURES, features::g_register>(_param);
            }

            extern result_t load_store(uint8_t *const _param) { return param_store<load::register_t, IDENTIFIER::LOAD_CALIB, load::g_register>(_param); }

            extern result_t maintainer_store(uint8_t *const _param)
            {
                return param_store<maintainer::register_t, IDENTIFIER::MAINTAINER, maintainer::g_register>(_param);
            }

            extern result_t name_store(uint8_t *const _param) { return param_store<name::register_t, IDENTIFIER::DEVICE_NAME, name::g_register>(_param); }

            extern result_t position_store(uint8_t *const _param)
            {
                return param_store<position::register_t, IDENTIFIER::POSITION, position::g_register>(_param);
            }

            extern result_t serial_number_store(uint8_t *const _param)
            {
                return param_store<serial_number::register_t, IDENTIFIER::SERIAL_NUMBER, serial_number::g_register>(_param);
            }

            extern result_t unique_identifier_store(uint8_t *const _param)
            {
                return param_store<unique_identifier::register_t, IDENTIFIER::UNIQUE_IDENTIFIER, unique_identifier::g_register>(_param);
            }

            extern result_t user_store(uint8_t *const _param) { return param_store<user::register_t, IDENTIFIER::USER, user::g_register>(_param); }

            extern result_t visual_store(uint8_t *const _param)
            {
                return param_store<visual::register_t, IDENTIFIER::VISUAL_FEEDBACK, visual::g_register>(_param);
            }

            extern result_t address_load(uint8_t *const _source) { return param_load<address::register_t, IDENTIFIER::ADDRESS, address::g_register>(_source); }

            extern result_t audio_load(uint8_t *const _source) { return param_load<audio::register_t, IDENTIFIER::AUDIO_FEEDBACK, audio::g_register>(_source); }

            extern result_t charger_load(uint8_t *const _source)
            {
                return param_load<charger::register_t, IDENTIFIER::CHARGER_CALIB, charger::g_register>(_source);
            }

            extern result_t features_load(uint8_t *const _source)
            {
                return param_load<features::register_t, IDENTIFIER::FEATURES, features::g_register>(_source);
            }

            extern result_t load_load(uint8_t *const _source) { return param_load<load::register_t, IDENTIFIER::LOAD_CALIB, load::g_register>(_source); }

            extern result_t maintainer_load(uint8_t *const _source)
            {
                return param_load<maintainer::register_t, IDENTIFIER::MAINTAINER, maintainer::g_register>(_source);
            }

            extern result_t name_load(uint8_t *const _source) { return param_load<name::register_t, IDENTIFIER::DEVICE_NAME, name::g_register>(_source); }

            extern result_t position_load(uint8_t *const _source)
            {
                return param_load<position::register_t, IDENTIFIER::POSITION, position::g_register>(_source);
            }

            extern result_t serial_number_load(uint8_t *const _source)
            {
                return param_load<serial_number::register_t, IDENTIFIER::SERIAL_NUMBER, serial_number::g_register>(_source);
            }

            extern result_t unique_identifier_load(uint8_t *const _source)
            {
                return param_load<unique_identifier::register_t, IDENTIFIER::UNIQUE_IDENTIFIER, unique_identifier::g_register>(_source);
            }

            extern result_t user_load(uint8_t *const _source) { return param_load<user::register_t, IDENTIFIER::USER, user::g_register>(_source); }

            extern result_t visual_load(uint8_t *const _source)
            {
                return param_load<visual::register_t, IDENTIFIER::VISUAL_FEEDBACK, visual::g_register>(_source);
            }
        }
    }
}