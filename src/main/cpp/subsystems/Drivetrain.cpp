// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Drivetrain.h"

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

/**
 * @brief Sets the speed of the left, right and lateral motors for OMNI_BASE
 * @warning  Does not work if the robot is not TANK_BASE
 *
 * @param right Right wheels pourcentage
 * @param left Left wheels pourcentage
 * @param lateral Lateral pourcentage
 */
void Drivetrain::Drive(double right, double left, double lateral)
{

    if (!IS_DRIVETRAIN_OMNIBASE)
    {
        throw std::runtime_error("Drivetrain::Drive(double right, double left, double lateral) : Cannot use this function for TANK_BASE");
    }
    m_NeoMotorLeft.Set(left);
    m_NeoMotorRight.Set(right);
    m_FalconMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, lateral);
}

/**
 * @brief Sets the speed of the left and right motors for TANK_BASE
 * @warning  Does not work if the robot is OMNI_BASE
 *
 * @param right Right wheels pourcentage
 * @param left Left wheels pourcentage
 */
void Drivetrain::Drive(double right, double left)
{

    if (IS_DRIVETRAIN_OMNIBASE)
    {
        throw std::runtime_error("Drivetrain::Drive(double right, double left) : Cannot use this function for OMNI_BASE");
    }
    m_NeoMotorLeft.Set(left);
    m_NeoMotorRight.Set(right);
}