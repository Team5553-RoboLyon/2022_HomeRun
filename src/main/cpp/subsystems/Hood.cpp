// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Hood.h"

Hood::Hood()
{
    m_encoderHood.SetDistancePerPulse(HOOD_ENCODER_CONVERSION_FACTOR);

    Enable();
    SetSetpoint(0.0);

    m_HoodMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    m_HoodMotor.SetInverted(true);
    m_HoodMotor.SetSmartCurrentLimit(HOOD_CURRENT_LIMIT);
    m_controller.SetIntegratorRange(-HOOD_PID_INTEGRATOR_RANGE, HOOD_PID_INTEGRATOR_RANGE);
    frc::SmartDashboard::PutNumber("hood setpoint", m_setPoint);
}

void Hood::Enable()
{
    m_state = Hood::state::Enabled;
}

void Hood::Disable()
{
    m_state = Hood::state::Disabled;
}

void Hood::SetSetpoint(double setpoint)
{
    m_setPoint = std::clamp(setpoint, 2.0, 56.0);
}

void Hood::ResetEncoders()
{
    m_encoderHood.Reset();
}

double Hood::GetMeasurement()
{
    return m_encoderHood.GetDistance();
}

void Hood::ResetPID()
{
    m_controller.Reset();
}

void Hood::Periodic()
{
    switch (m_state)
    {
    case Hood::state::Enabled:
    {
        double output = m_controller.Calculate(GetMeasurement(), m_setPoint);
        frc::SmartDashboard::PutNumber("outputHood", output);
        frc::SmartDashboard::PutNumber("encodeur hood", GetMeasurement());
        m_HoodMotor.Set(output);
        break;
    }
    case Hood::state::Disabled:
    {
        m_HoodMotor.Set(0.0);
        break;
    }
    default:
    {
        break;
    }
    }
}
