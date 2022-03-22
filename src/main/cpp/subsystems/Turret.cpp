// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Turret.h"

Turret::Turret()
{
    SetSetpoint(0.0);
    m_pidController.SetIntegratorRange(-5, 5);
    m_pidController.SetTolerance(0.0, std::numeric_limits<double>::infinity());
    m_encoderTurret.SetDistancePerPulse(45.000 / 1290);
    m_encoderTurret.SetReverseDirection(true);
    ResetEncoder();
}

void Turret::Enable()
{
    m_State = Turret::State::enable;
}

void Turret::Disable()
{
    m_State = Turret::State::disable;
}

void Turret::SetSetpoint(double setpoint)
{
    m_setPoint = setpoint;
}

double Turret::GetSetpoint()
{
    return m_setPoint;
}

void Turret::UseOutput(double output, double setpoint)
{
    switch (Turret::m_State)
    {
    case Turret::State::unknownPosition:
        m_pidController.SetSetpoint(-140);
        if (m_SensorHall.MagnetDetected())
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
        if (GetMeasurement() < 66 && GetMeasurement() > 62)
        {
            spdlog::info(GetMeasurement());
            spdlog::info("on passe en ready");
            m_TurretMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0.0);
            ResetEncoder();
            SetSetpoint(0);
            m_State = State::enable;
        }
        else
        {
            m_TurretMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, std::clamp(output, -0.4, 0.4)); // TODO remettre le clamp a 0.6
        }
        break;
    case Turret::State::enable:
        if (m_SensorHall.ShouldIStop(GetMeasurement(), wpi::sgn(output)))
        {
            m_TurretMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, std::clamp(output, -0.4, 0.4)); // TODO remettre le clamp a 0.6
        }
        else
        {
            m_TurretMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0.0);
        }
        break;
    case Turret::State::disable:
        m_TurretMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0.0);
        break;

    default:
        break;
    }
}

void Turret::Periodic()
{
    double output = m_pidController.Calculate(GetMeasurement());
    UseOutput(output, GetSetpoint());
}
double Turret::GetMeasurement()
{
    return m_encoderTurret.GetDistance();
}

void Turret::ResetEncoder()
{
    m_encoderTurret.Reset();
}
