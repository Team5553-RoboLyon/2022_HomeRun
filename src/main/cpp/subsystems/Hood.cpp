// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Hood.h"

#include <frc/livewindow/LiveWindow.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/shuffleboard/Shuffleboard.h>
#include <spdlog/spdlog.h>

Hood::Hood()
{
    m_encoderHood.SetDistancePerRotation(-(58 / 4.2));

    Enable();
    SetSetpoint(0.0);

    m_HoodMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    m_HoodMotor.SetInverted(true);
    // m_pidcontroller.SetIntegratorRange(-HOOD_PID_INTEGRATOR_RANGE, HOOD_PID_INTEGRATOR_RANGE);
    // m_pidcontroller.SetTolerance(HOOD_PID_TOLERANCE);
    m_hallSecurity.setInverted(true); // TODO verifier ca mais je pense que c'est vrai
    ResetEncoders();

#if SHUFFLEBOARD_DEBUG
    // m_entry_HoodPosition = frc::Shuffleboard::GetTab("Hood DEBUG").Add("Hood Position", GetMeasurement()).GetEntry();
    // m_entry_HoodSetpoint = frc::Shuffleboard::GetTab("Hood DEBUG").Add("Hood Setpoint", GetSetpoint()).GetEntry();
    // m_entry_HoodError = frc::Shuffleboard::GetTab("Hood DEBUG").Add("Hood Error", m_pidcontroller.GetPositionError()).GetEntry();
    // m_entry_HoodOutput = frc::Shuffleboard::GetTab("Hood DEBUG").Add("Hood Output", 0.0).GetEntry();
    // m_entry_HoodState = frc::Shuffleboard::GetTab("Hood DEBUG").Add("Hood State", StateToString(m_state)).GetEntry();
#endif
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

double Hood::GetSetpoint()
{
    return m_setPoint;
}

void Hood::ResetEncoders()
{
    m_encoderHood.Reset();
    m_HoodMotor.GetEncoder().SetPosition(0.0);
}

double Hood::GetMeasurement()
{
    return m_encoderHood.GetDistance();
}

void Hood::UseOutput(double output, double setpoint)
{
    switch (m_state)
    {
    case Hood::state::WaitingEncoder:
        if (m_encoderHood.IsConnected())
        {
            ResetEncoders();
            m_state = Hood::state::Init;
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

void Hood::Periodic()
{
    double output = m_pidcontroller.Calculate(units::degree_t{GetMeasurement()}, units::degree_t{m_setPoint});
    UseOutput(output, GetSetpoint());

#if SHUFFLEBOARD_DEBUG
    // m_entry_HoodPosition.SetDouble(GetMeasurement());
    // m_entry_HoodSetpoint.SetDouble(GetSetpoint());
    // m_entry_HoodError.SetDouble(m_pidcontroller.GetPositionError());
    // m_entry_HoodOutput.SetDouble(output);
    // m_entry_HoodState.SetString(StateToString(m_state));
#endif
}

// Convert state number to name

std::string Hood::StateToString(int state)
{
    switch (state)
    {
    case 0:
        return "Init";
    case 1:
        return "haut_Direction";
    case 2:
        return "bas_Direction";
    case 3:
        return "bh_Direction";
    case 4:
        return "StopSecure";
    default:
        return "Unknown";
    }
}