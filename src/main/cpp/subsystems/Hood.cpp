// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Hood.h"

Hood::Hood()
{
    m_encoderHood.SetDistancePerPulse(-(58 / 4.2));

    Enable();
    SetSetpoint(0.0);

    m_HoodMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    m_HoodMotor.SetInverted(true);
    m_HoodMotor.SetSmartCurrentLimit(20);
    m_controller.SetIntegratorRange(-5, 5);
    frc::SmartDashboard::PutNumber("hood setpoint", m_setPoint);

    m_state = Hood::state::Disabled;

    m_hallSecurity.setInverted(true); // TODO verifier ca mais je pense que c'est vrai
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
    m_setPoint = setpoint;
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
    frc::SmartDashboard::PutNumber("outputHood", output);
    frc::SmartDashboard::PutNumber("encodeur hood", GetMeasurement());
    SetSetpoint(frc::SmartDashboard::GetNumber("hood setpoint", m_setPoint));
    switch (m_state)
    {
    case Hood::state::Enabled:
        m_HoodMotor.Set(output);
        break;
    case Hood::state::Disabled:
        m_HoodMotor.Set(0.0);
        break;
    default:
        break;
    }
}
