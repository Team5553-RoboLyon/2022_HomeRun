// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystem/Hood.h"

Hood::Hood()
{
    m_encoderHood.SetDistancePerPulse(HOOD_ENCODER_CONVERSION_FACTOR);

    SetSetpoint(0.0);

    m_HoodMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    m_HoodMotor.SetInverted(true);
    m_HoodMotor.SetSmartCurrentLimit(HOOD_CURRENT_LIMIT);
    m_controller.SetIntegratorRange(-5, 5);

    m_state = Hood::state::Disabled;

    m_hallSecurity.setInverted(false);
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

void Hood::Periodic()
{
    double output = m_controller.Calculate(GetMeasurement(), m_setPoint);
    m_HoodMotor.Set(output);
}

void Hood::ResetController()
{
    m_controller.Reset();
}

double Hood::GetSetpoint()
{
    return m_controller.GetSetpoint();
}

void Hood::SetPID(double p, double i, double d)
{
    m_controller.SetPID(p, i, d);
}