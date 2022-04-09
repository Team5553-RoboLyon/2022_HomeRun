// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Shooter.h"

Shooter::Shooter()
{
    m_MotorLeft.ConfigFactoryDefault();
    m_MotorRight.ConfigFactoryDefault();

    m_MotorLeft.SetInverted(false);
    m_MotorRight.SetInverted(true);

    m_MotorRight.Follow(m_MotorLeft);

    m_MotorLeft.ConfigVoltageCompSaturation(11);
    m_MotorRight.ConfigVoltageCompSaturation(11);

    m_MotorLeft.EnableVoltageCompensation(true);
    m_MotorRight.EnableVoltageCompensation(true);

    frc::Shuffleboard::GetTab("dev").Add("shooter coef", 1.0);
}

void Shooter::SetSpeed(double speed)
{
    m_MotorLeft.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, std::clamp(speed, 0.0, 1.0) * frc::Shuffleboard::GetTab("dev").Add("shooter coef", 1.0).GetEntry().GetDouble(1.0)); // TODO ATTENTION A ENLEVER LE COEF
}
void Shooter::Reverse()
{
    m_MotorLeft.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, SHOOTER_UNBLOCK_SPEED);
}

double Shooter::AppliedSpeed()
{
    return m_MotorLeft.GetSelectedSensorVelocity();
}

void Shooter::Periodic() {}
