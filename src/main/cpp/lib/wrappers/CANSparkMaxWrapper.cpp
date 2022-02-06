// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "lib/wrappers/CANSparkMaxWrapper.h"

CANSparkMaxWrapper::CANSparkMaxWrapper(int deviceId, rev::CANSparkMax::MotorType motorType)
    : CANSparkMax(deviceId, motorType)
{
    m_isSimulated = frc::RobotBase::IsSimulation();
    if (m_isSimulated)
    {
        m_simDevice = hal::SimDevice(("WRAPPER::SPARK MAX [" + std::to_string(INTAKE_MOTOR_ID) + "]").c_str());
        m_setpoint = m_simDevice.CreateDouble("Setpoint", 2, 0.0);
    }
}

void CANSparkMaxWrapper::Set(double speed)
{
    if (m_isSimulated)
    {
        m_setpoint.Set(speed);
    }
    else
    {
        rev::CANSparkMax::Set(speed);
    }
}

double CANSparkMaxWrapper::Get()
{
    if (m_isSimulated)
    {
        return m_setpoint.Get();
    }
    else
    {
        return rev::CANSparkMax::Get();
    }
}