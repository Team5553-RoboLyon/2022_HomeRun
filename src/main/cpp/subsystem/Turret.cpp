// Copyright(c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystem/Turret.h"
#include <spdlog/spdlog.h>

Turret::Turret()
    : PIDSubsystem(frc2::PIDController(0.04, 0.02, 0.002))
{
    SetSetpoint(0.0);
    GetController().SetIntegratorRange(-5, 5);
    GetController().SetTolerance(0.0, std::numeric_limits<double>::infinity());
    m_encoderTurret.SetDistancePerPulse(45.000 / 1290);
    m_encoderTurret.SetReverseDirection(true);
    ResetEncoder();
    Disable();
}
bool Turret::MagnetDetected() { return !m_SensorHall.Get(); }

void Turret::UseOutput(double output, double setpoint)
{
    switch (Turret::m_state)
    {
    case Turret::TurretState::unknownPosition:
        SetSetpoint(-140);
        if (MagnetDetected())
        {
            m_TurretMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0.0);
            m_state = TurretState::goTo0;
            ResetEncoder();
            Enable();
            SetSetpoint(64);
        }
        else
        {
            m_TurretMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, std::clamp(output, -0.2, 0.2)); // TODO remettre le clamp a 0.6
        }
        break;
    case Turret::TurretState::goTo0:
        if (GetMeasurement() < 66 && GetMeasurement() > 62)
        {
            spdlog::info(GetMeasurement());
            spdlog::info("on passe en ready");
            m_TurretMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0.0);
            ResetEncoder();
            SetSetpoint(0);
            m_state = TurretState::ready;
        }
        else
        {
            m_TurretMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, std::clamp(output, -0.4, 0.4)); // TODO remettre le clamp a 0.6
        }
        break;
    case Turret::TurretState::ready:
        SetSetpoint(frc::SmartDashboard::GetNumber("Setpoint m_turret", 0.0));
        m_TurretMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, std::clamp(output, -0.5, 0.5)); // TODO remettre le clamp a 0.6

        break;

    default:
        break;
    }

    frc::SmartDashboard::PutNumber("outputTurret", output);
    frc::SmartDashboard::PutNumber("out setpoint", setpoint);
}

double Turret::GetMeasurement()
{
    return m_encoderTurret.GetDistance();
}

void Turret::ResetEncoder()
{
    m_encoderTurret.Reset();
}

void Turret::SetPID(double p, double i, double d)
{
    GetController().SetP(p);
    GetController().SetI(i);
    GetController().SetD(d);
}