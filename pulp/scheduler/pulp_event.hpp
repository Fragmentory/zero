/**
 * \file pulp_event.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "engine_defines.hpp"
#include "event_bus.hpp"
#include "soc_variant.hpp"

namespace pulp::event
{
    struct Perform : public pulp::event::Type<Perform>
    {
        static const int32_t HEARTBEAT_COUNTER = core::soc::Variant::DEFAULT_HEARTBEAT_COUNTER;
    };
    struct Heartbeat : public pulp::event::Type<Heartbeat>
    {
    };

    enum class ERROR : uint8_t
    {
        INTERFACE_MISSED = 0x00,
        INTERFACE_COMMUNICATION = 0x01,
        REGISTRY_BROKEN = 0x10,
        HARDWARE_BROKEN = 0x20,
        HOST_DEVICE_COMMUNICATION = 0x30,
        HOST_DEVICE_CRITICAL_TIMEOUT = 0x31,
        TEMPERATURE_CONTROL = 0x42,
        UPDATE_COMMUNICATION = 0x50,
        UPDATE_VERSION = 0x51,
        INPUT_UNDER_VOLTAGE = 0x82,
        OUTPUT_CURRENT_LIMIT_TRIGGERED = 0x83,
        PARAMETER_CHECK_FAILED = 0x85,

        UNDEFINED = 0xff,
    };

    struct Alert : public pulp::event::Type<Alert>
    {
        Alert(const ERROR _error_code) :
            error_code(_error_code)
        {
        }
        ERROR error_code{ERROR::UNDEFINED};
    };

    struct Connect : public pulp::event::Type<Connect>
    {
    };

    struct Disconnect : public pulp::event::Type<Disconnect>
    {
    };

    struct Done : public pulp::event::Type<Done>
    {
    };

    struct Init : public pulp::event::Type<Init>
    {
    };

    struct ApplicationStop : public pulp::event::Type<ApplicationStop>
    {
    };

    struct Resume : public pulp::event::Type<Resume>
    {
    };

    namespace update
    {
        enum class FUNCTION
        {
            START = 0x10,
            STATUS = 0x17,
            UNDEFINED = 0xff
        };
        enum class RESULT
        {
            SUCCESS = 0x00,
            FAILURE = 0x01,
            DATA_BROKEN = 0x0A,
            UNAVAILABLE = 0x03,
            RUNNING = 0x0b,
            WRONG_REVISION = 0x08,
            WRONG_STATE = 0x09,
            UNDEFINED = 0xff
        };
        enum class STATUS
        {
            START = 0x10,
            INTERNAL = 0x17,
            DONE = 0x14,
            UNDEFINED = 0xff
        };
    }
    struct UpdateReq : public pulp::event::Type<UpdateReq>
    {
        UpdateReq(const update::FUNCTION _function) :
            function(_function)
        {
        }
        update::FUNCTION function{update::FUNCTION::UNDEFINED};
    };
    struct UpdateInd : public pulp::event::Type<UpdateReq>
    {
        UpdateInd(const update::RESULT _result, const update::FUNCTION _function, const update::STATUS _status) :
            result(_result),
            function(_function),
            status(_status)
        {
        }
        update::RESULT result{update::RESULT::UNDEFINED};
        update::FUNCTION function{update::FUNCTION::UNDEFINED};
        update::STATUS status{update::STATUS::UNDEFINED};
    };

    namespace error
    {
        enum class FAILURE
        {
            CHARGE_CONTROLLER_MISSED = 0x00,
            CHARGE_CONTROLLER_COMMUNICATION = 0x01,
            LOAD_CONTROLLER_MISSED = 0x02,
            LOAD_CONTROLLER_COMMUNICATION = 0x03,
            REGISTRY_BROKEN = 0x10,
            HARDWARE_BROKEN = 0x20,
            HOST_DEVICE_COMMUNICATION = 0x30,
            HOST_DEVICE_CRITICAL_TIMEOUT = 0x31,
            TEMPERATURE_LOAD = 0x40,
            TEMPERATURE_CONNECTOR = 0x41,
            TEMPERATURE_CONTROL = 0x42,
            UPDATE_COMMUNICATION = 0x50,
            UPDATE_VERSION = 0x51,
            LOAD_CHARGER_STATE_OFF = 0xA0,
            LOAD_CHARGER_STATE_ON = 0xA1,
            LOAD_CONNECTOR_STATE_OFF = 0xA2,
            LOAD_CONNECTOR_STATE_ON = 0xA3,
            LOAD_CURRENT_NON_ZERO = 0xB0,
            LOAD_CURRENT_ZERO = 0xB1,
            LOAD_LOAD_VOLTAGE_NON_ZERO = 0xB2,
            LOAD_LOAD_VOLTAGE_ZERO = 0xB3,
            LOAD_RELAIS_VOLTAGE_NON_ZERO = 0xB4,
            LOAD_RELAIS_VOLTAGE_ZERO = 0xB5,
            LOAD_TEMPERATURE_RANGE_COLD = 0xC0,
            LOAD_TEMPERATURE_RANGE_COLD_OR_WARM = 0xC1,
            LOAD_TEMPERATURE_RANGE_WARM_OR_HOT = 0xC2,
            LOAD_TEMPERATURE_VALUE = 0xC3,
            UNDEFINED = 0xff,
        };
    }
    struct ErrorInd : public pulp::event::Type<ErrorInd>
    {
        ErrorInd(const error::FAILURE _failure) :
            failure(_failure)
        {
        }
        error::FAILURE failure{error::FAILURE::UNDEFINED};
    };

    struct Service : public pulp::event::Type<Service>
    {
    };

    struct Start : public pulp::event::Type<Start>
    {
    };

    struct Stop : public pulp::event::Type<Stop>
    {
    };

    struct Shutdown : public pulp::event::Type<Shutdown>
    {
    };

    struct Enable : public pulp::event::Type<Enable>
    {
    };

    struct Disable : public pulp::event::Type<Disable>
    {
    };

    struct DeviceCleanup : public pulp::event::Type<DeviceCleanup>
    {
    };

    struct Suspend : public pulp::event::Type<Suspend>
    {
        Suspend(const bool _wake_up) :
            wake_up(_wake_up)
        {
        }

        bool wake_up{false};
    };

    struct ApplicationStart : public pulp::event::Type<ApplicationStart>
    {
    };
}
