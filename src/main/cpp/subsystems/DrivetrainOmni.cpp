// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/DrivetrainOmni.h"

Drivetrain::Drivetrain()
{
    m_NeoMotorRight.RestoreFactoryDefaults();
    m_NeoMotorRightFollower.RestoreFactoryDefaults();
    m_NeoMotorLeft.RestoreFactoryDefaults();
    m_NeoMotorLeftFollower.RestoreFactoryDefaults();
    m_FalconMotor.ConfigFactoryDefault();

    m_NeoMotorRightFollower.Follow(m_NeoMotorRight);
    m_NeoMotorLeftFollower.Follow(m_NeoMotorLeft);

    m_NeoMotorLeft.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    m_NeoMotorLeftFollower.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    m_NeoMotorRight.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    m_NeoMotorRightFollower.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    m_FalconMotor.SetNeutralMode(ctre::phoenix::motorcontrol::Brake);

    m_NeoMotorLeft.SetInverted(true);
    m_NeoMotorLeftFollower.SetInverted(true);
    m_NeoMotorRight.SetInverted(false);
    m_NeoMotorRightFollower.SetInverted(false);
    m_FalconMotor.SetInverted(false);
}

void Drivetrain::Periodic() {}

void Drivetrain::Drive(double right, double left, double lateral)
{
    m_NeoMotorLeft.Set(left);
    m_NeoMotorRight.Set(right);
    m_FalconMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, lateral);
}