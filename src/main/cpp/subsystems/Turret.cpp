// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Turret.h"

Turret::Turret()
{
    m_pidController.SetSetpoint(0.0);
    m_pidController.SetIntegratorRange(-5, 5);
    m_pidController.SetTolerance(0.0, std::numeric_limits<double>::infinity());
    m_encoderTurret.SetDistancePerPulse(45.000 / 1290);
    m_encoderTurret.SetReverseDirection(true);
    ResetEncoder();
}
bool Turret::MagnetDetected() { return !m_SensorHall.Get(); }

void Turret::UseOutput(double output, double setpoint)
{
    m_TPosition = GetEncoderDistance();
    m_TDeltaPosition = m_TPosition - m_TPositionBefore;
    m_TPositionBefore = m_TPosition;
    switch (Turret::m_State)
    {
    case Turret::State::unknownPosition:
        SetSetpoint(-140);
        if (MagnetDetected())
        {
            m_TurretMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0.0);
            m_State = State::goTo0;
            ResetEncoder();
            SetSetpoint(64);
        }
        else
        {
            m_TurretMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, std::clamp(output, -0.2, 0.2)); // TODO remettre le clamp a 0.6
        }
        break;
    case Turret::State::goTo0:
        if (GetEncoderDistance() < 66 && GetEncoderDistance() > 62)
        {
            spdlog::info(GetEncoderDistance());
            spdlog::info("on passe en ready");
            m_TurretMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0.0);
            ResetEncoder();
            SetSetpoint(0);
            m_State = State::ready;
        }
        else
        {
            m_TurretMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, std::clamp(output, -0.4, 0.4)); // TODO remettre le clamp a 0.6
        }
        break;
    case Turret::State::ready:
        m_TPosition = m_TPositionBefore = GetEncoderDistance();
        m_TDeltaPosition = 0.0;
        // si on détecte un aimant à l'init on stoppe tout
        if (MagnetDetected())
        {
            m_State = StopSecure;
        }
        else
        {
            m_State = dg_Direction;
        }

        break;
    case Turret::State::d_Direction:
        // std::cout << "Turret::State::d_Direction:" << std::endl;
        if (m_TSpeedConsigne < 0)
        {
            m_TurretMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, std::clamp(output, -0.6, 0.6)); // TODO remettre le clamp a 0.6
        }
        else
        {
            m_TurretMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput,
                              (0.0)); // m_State = Turret::State::Stop;
        }
        if (!MagnetDetected())
        {
            m_State = Turret::State::dg_Direction;
        }
        break;

    case Turret::State::g_Direction:
        // std::cout << "Turret::State::g_Direction:" << std::endl;
        if (m_TSpeedConsigne > 0)
        {
            m_TurretMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, std::clamp(output, -0.6, 0.6)); // TODO remettre le clamp a 0.6
        }
        else
        {
            m_TurretMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput,
                              (0.0)); // m_State = Turret::State::Stop;
        }
        if (!MagnetDetected())
        {
            m_State = Turret::State::dg_Direction;
        }
        break;

    case Turret::State::dg_Direction:
        // std::cout << "Turret::State::dg_Direction:" << std::endl;
        if (MagnetDetected()) // si on détecte un aimant
        {
            if (m_TDeltaPosition < 0) // on est a droite
            {
                if (m_TSpeedConsigne > 0)
                {
                    m_TurretMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, std::clamp(output, -0.6, 0.6)); // TODO remettre le clamp a 0.6
                }
                else
                {
                    m_TurretMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput,
                                      (0.0)); // m_State = Turret::State::Stop;
                }
                m_State = Turret::State::g_Direction; // on va à gauche;
            }
            else if (m_TDeltaPosition > 0) // on est a gauche
            {
                if (m_TSpeedConsigne < 0)
                {
                    m_TurretMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, std::clamp(output, -0.6, 0.6)); // TODO remettre le clamp a 0.6
                }
                else
                {
                    m_TurretMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput,
                                      (0.0)); // m_State = Turret::State::Stop;
                }
                m_State = Turret::State::d_Direction; // on va à droite;
            }
        }
        else // si on ne détecte pas d'aimant
        {
            m_TurretMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, std::clamp(output, -0.6, 0.6)); // TODO remettre le clamp a 0.6
        }

        break;

    case Turret::State::StopSecure:
        m_TurretMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, (0.0));
        break;

    default:
        break;
    }

    double Turret::GetEncoderDistance()
    {
        return m_encoderTurret.GetDistance();
    }

    void Turret::ResetEncoder()
    {
        m_encoderTurret.Reset();
    }
