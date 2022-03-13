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
    m_pidController.SetSetpoint(0.0);

    m_HoodMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    m_HoodMotor.SetInverted(true);
    m_pidController.SetIntegratorRange(-HOOD_PID_INTEGRATOR_RANGE, HOOD_PID_INTEGRATOR_RANGE);
    m_pidController.SetTolerance(HOOD_PID_TOLERANCE);

    ResetEncoders();

#if SHUFFLEBOARD_DEBUG
    m_entry_HoodPosition = frc::Shuffleboard::GetTab("Hood DEBUG").Add("Hood Position", GetEncoderDistance()).GetEntry();
    m_entry_HoodSetpoint = frc::Shuffleboard::GetTab("Hood DEBUG").Add("Hood Setpoint", m_pidController.GetSetpoint()).GetEntry();
    m_entry_HoodError = frc::Shuffleboard::GetTab("Hood DEBUG").Add("Hood Error", m_pidController.GetPositionError()).GetEntry();
    m_entry_HoodOutput = frc::Shuffleboard::GetTab("Hood DEBUG").Add("Hood Output", 0.0).GetEntry();
    m_entry_HoodState = frc::Shuffleboard::GetTab("Hood DEBUG").Add("Hood State", StateToString(m_state)).GetEntry();
#endif
}

bool Hood::MagnetDetected() { return !m_SensorHall.Get(); }

void Hood::ResetEncoders()
{
    m_encoderHood.Reset();
    m_HoodMotor.GetEncoder().SetPosition(0.0);
}

void Hood::UseOutput(double output, double setpoint)
{
    m_Position = GetEncoderDistance();
    m_DeltaPosition = m_Position - m_PositionBefore;
    if (m_DeltaPosition > -0.3 && m_DeltaPosition < 0.3)
        m_DeltaPosition = 0;
    m_PositionBefore = m_Position;
    switch (m_state)
    {
    case Hood::state::Init:
        m_Position = m_PositionBefore = GetEncoderDistance();
        if (MagnetDetected())
        {
            m_state = Hood::state::haut_Direction;
            ResetEncoders();
            SetSetpoint(0.0);
        }
        else
        {
            SetSetpoint(-60.0);
            m_HoodMotor.Set(std::clamp(output, -HOOD_INIT_MAX_SPEED, HOOD_INIT_MAX_SPEED));
        }
        break;
    case Hood::state::bas_Direction:
        if (output < 0) // si le pid renvoie <0 mettre moteur vitesse normal
        {
            // SetSetpoint((frc::SmartDashboard::GetNumber("Setpoint m_hood", 0.0)));
            m_HoodMotor.Set(std::clamp(output, -HOOD_MAX_SPEED, HOOD_MAX_SPEED));
        }
        else
        { // sinon mettre le hood a 0.0
            m_HoodMotor.Set(0.0);
        }
        if (!MagnetDetected())
        {                                        // si on ne détecte plus
            m_state = Hood::state::bh_Direction; // mettre state à bh_direction
        }
        break;

    case Hood::state::haut_Direction:
        if (output > 0) // si le pid renvoie >0 mettre moteur vitesse normal
        {
            // SetSetpoint((frc::SmartDashboard::GetNumber("Setpoint m_hood", 0.0)));
            m_HoodMotor.Set(std::clamp(output, -HOOD_MAX_SPEED, HOOD_MAX_SPEED));
        }
        else
        { // sinon mettre vitesse à 0
            m_HoodMotor.Set(0.0);
        }
        if (!MagnetDetected())
        {                                        // si on ne détecte plus
            m_state = Hood::state::bh_Direction; // mettre state à bh_direction
        }

        break;

    case Hood::state::bh_Direction:
        if (MagnetDetected())
        { // si on détecte un aimant
            if (m_DeltaPosition < 0)
            { // si on va en bas
                if (output > 0)
                { // si joystick renvoie >0 mettre moteur vitesse normal
                    // SetSetpoint((frc::SmartDashboard::GetNumber("Setpoint m_hood", 0.0)));
                    m_HoodMotor.Set(std::clamp(output, -HOOD_MAX_SPEED, HOOD_MAX_SPEED));
                }
                else
                { // sinon mettre le poid du Hood
                    m_HoodMotor.Set(0.0);
                    // est ce que le hood a une barre qui le maintien (mettre a O ?)
                }
                m_state = Hood::state::haut_Direction; // mettre state à haut
            }
            else
            { // sinon si on vas en haut
                if (output < 0)
                { // si joystick renvoie <0 mettre moteur vitesse normal
                    // SetSetpoint((frc::SmartDashboard::GetNumber("Setpoint m_hood", 0.0)));
                    m_HoodMotor.Set(0.0);
                }
                else
                { // sinon mettre le poid du Hood
                    m_HoodMotor.Set(std::clamp(output, -HOOD_MAX_SPEED, HOOD_MAX_SPEED));
                }
                m_state = Hood::state::bas_Direction; // mettre state à bas
            }
        }
        else
        { // sinon pas d'aimant mettre vitesse normal
            // SetSetpoint((frc::SmartDashboard::GetNumber("Setpoint m_hood", 0.0)));
            m_HoodMotor.Set(std::clamp(output, -HOOD_MAX_SPEED, HOOD_MAX_SPEED));
        }

        break;

    default:
        break;
    }
}

double Hood::GetEncoderDistance()
{
    return m_encoderHood.GetDistance();
}

void Hood::Periodic()
{
    double output = m_pidController.Calculate(GetEncoderDistance());
    UseOutput(output, m_pidController.GetSetpoint());

#if SHUFFLEBOARD_DEBUG
    m_entry_HoodPosition.SetDouble(GetEncoderDistance());
    m_entry_HoodSetpoint.SetDouble(m_pidController.GetSetpoint());
    m_entry_HoodError.SetDouble(m_pidController.GetPositionError());
    m_entry_HoodOutput.SetDouble(output);
    m_entry_HoodState.SetString(StateToString(m_state));
#endif
}

void Hood::SetSetpoint(double setpoint)
{
    m_pidController.SetSetpoint(setpoint);
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