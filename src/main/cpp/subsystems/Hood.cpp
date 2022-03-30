// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Hood.h"

Hood::Hood()
{
    m_encoderHood.SetDistancePerRotation(-(58 / 4.2));

    Enable();
    SetSetpoint(0.0);

    m_HoodMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    m_HoodMotor.SetInverted(true);
    m_controller.SetIntegratorRange(-5, 5);

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
    double output = m_controller.Calculate(units::degree_t{GetMeasurement()}, units::degree_t{m_setPoint});

    switch (m_state)
    {
    case Hood::state::WaitingEncoder:
        if (m_encoderHood.IsConnected())
        {
            ResetEncoders();
            m_state = Hood::state::Enabled; // TODO attention on saute le mode init la !!!!!
        }
        break;
    case Hood::state::Init:
        if (m_hallSecurity.MagnetDetected())
        {
            m_state = Hood::state::Disabled;
            ResetEncoders();
            SetSetpoint(0.0);
        }
        else
        {
            SetSetpoint(-60.0);
            if (!m_hallSecurity.ShouldIStop(GetMeasurement(), wpi::sgn(output)))
            {
                m_HoodMotor.Set(std::clamp(output, -0.1, 0.1));
            }
            else
            {
                m_HoodMotor.Set(0.0);
            }
        }
        break;

    case Hood::state::Enabled:
        if (m_hallSecurity.ShouldIStop(GetMeasurement(), wpi::sgn(output)))
        {
            m_HoodMotor.Set(output);
        }
        else
        {
            m_HoodMotor.Set(0.0);
        }
        break;
    case Hood::state::Disabled:
        m_HoodMotor.Set(0.0);
        break;
    default:
        break;
    }
    frc::SmartDashboard::PutNumber("outputHood", output);
}
