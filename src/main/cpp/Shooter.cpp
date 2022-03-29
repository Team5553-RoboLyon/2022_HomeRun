// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Shooter.h"

Shooter::Shooter()
{
    m_MotorLeft.ConfigFactoryDefault();
    m_MotorRight.ConfigFactoryDefault();

    m_MotorLeft.SetInverted(true);
    m_MotorRight.SetInverted(false);

    m_MotorLeft.ConfigVoltageCompSaturation(11);
    m_MotorRight.ConfigVoltageCompSaturation(11);
}

void Shooter::SetSpeed(double speed)
{
    m_MotorLeft.Set(ctre::phoenix::motorcontrol::ControlMode::MotionProfile, speed); // TODO check les motionProfile controle
}

double Shooter::AppliedSpeed()
{
    return m_MotorLeft.GetSelectedSensorVelocity();
}

void Shooter::Periodic() {}
