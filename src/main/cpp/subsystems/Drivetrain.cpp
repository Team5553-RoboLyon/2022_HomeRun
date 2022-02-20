// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Drivetrain.h"

Drivetrain::Drivetrain()
{
    spdlog::trace("Drivetrain()");
    m_NeoMotorRight.RestoreFactoryDefaults();
    m_NeoMotorRightFollower.RestoreFactoryDefaults();
    m_NeoMotorLeft.RestoreFactoryDefaults();
    m_NeoMotorLeftFollower.RestoreFactoryDefaults();

    m_NeoMotorLeft.SetOpenLoopRampRate(0.7);
    m_NeoMotorRight.SetOpenLoopRampRate(0.7);
    m_NeoMotorLeftFollower.SetOpenLoopRampRate(0.7);
    m_NeoMotorRightFollower.SetOpenLoopRampRate(0.7);

    m_NeoMotorLeft.EnableVoltageCompensation(10);
    m_NeoMotorRight.EnableVoltageCompensation(10);
    m_NeoMotorLeftFollower.EnableVoltageCompensation(10);
    m_NeoMotorRightFollower.EnableVoltageCompensation(10);

    m_NeoMotorRightFollower.Follow(m_NeoMotorRight);
    m_NeoMotorLeftFollower.Follow(m_NeoMotorLeft);

    m_NeoMotorLeft.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    m_NeoMotorLeftFollower.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    m_NeoMotorRight.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    m_NeoMotorRightFollower.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);

    m_NeoMotorLeft.SetInverted(true);
    m_NeoMotorLeftFollower.SetInverted(true);
    m_NeoMotorRight.SetInverted(false);
    m_NeoMotorRightFollower.SetInverted(false);

    m_NeoMotorLeft.GetEncoder().SetPosition(0);
    m_NeoMotorLeftFollower.GetEncoder().SetPosition(0);
    m_NeoMotorRight.GetEncoder().SetPosition(0);
    m_NeoMotorRightFollower.GetEncoder().SetPosition(0);

#if IS_DRIVETRAIN_OMNIBASE
    m_FalconMotor.ConfigFactoryDefault();
    m_FalconMotor.SetNeutralMode(ctre::phoenix::motorcontrol::Brake);
    m_FalconMotor.SetInverted(false);
    m_FalconMotor.GetSensorCollection().SetIntegratedSensorPosition(0.0);
    m_FalconMotor.ConfigOpenloopRamp(0.7);
    m_FalconMotor.EnableVoltageCompensation(true);
    m_FalconMotor.ConfigVoltageCompSaturation(10);
#endif
    m_solenoidClimber.Set(frc::DoubleSolenoid::Value::kForward);
    m_solenoidRotatingArms.Set(frc::DoubleSolenoid::Value::kForward);
}

void Drivetrain::Periodic()
{
    spdlog::trace("Drivetrain::Periodic()");
}

void Drivetrain::Stop()
{
    spdlog::trace("Drivetrain::Stop()");
    m_NeoMotorLeft.StopMotor();
    m_NeoMotorRight.StopMotor();

#if IS_DRIVETRAIN_OMNIBASE
    m_FalconMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0);
#endif
}

#if IS_DRIVETRAIN_OMNIBASE
/**
 * @brief Sets the speed of the left, right and lateral motors for OMNI_BASE
 * @warning  Does not work if the robot is TANK_BASE
 *
 * @param right Right wheels pourcentage
 * @param left Left wheels pourcentage
 * @param lateral Lateral pourcentage
 */
void Drivetrain::Drive(double right, double left, double lateral)
{
    spdlog::trace("Drive({}, {}, {})", right, left, lateral);

    if (!IS_DRIVETRAIN_OMNIBASE)
    {
        throw RobotError::RobotCriticalError("Drivetrain::Drive(double right, double left, double lateral) : Cannot use this function for TANK_BASE");
    }
    m_NeoMotorLeft.Set(left);
    m_NeoMotorRight.Set(right);
    m_FalconMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, lateral);
}

/**
 * @brief Gets the encoder values of the left, right and lateral motors for OMNI_BASE
 * @warning  Does not work if the robot is TANK_BASE
 *
 * @param encoderValues Array of 3 doubles where the encoder values will be stored
 */
void Drivetrain::GetEncoderValues(double (&encoderValues)[3])
{
    spdlog::trace("Drivetrain::GetEncoderValues()");
    encoderValues[0] = m_NeoMotorLeft.GetEncoder().GetPosition();
    encoderValues[1] = m_NeoMotorRight.GetEncoder().GetPosition();
    encoderValues[2] = m_FalconMotor.GetSensorCollection().GetIntegratedSensorPosition();
}

double Drivetrain::GetFalconSimulatedOutput()
{
    spdlog::trace("Drivetrain::GetFalconSimulatedOutput()");
    return m_FalconMotor.GetSimCollection().GetMotorOutputLeadVoltage();
}
#else
/**
 * @brief Sets the speed of the left and right motors for TANK_BASE
 * @warning  Does not work if the robot is OMNI_BASE
 *
 * @param right Right wheels pourcentage
 * @param left Left wheels pourcentage
 */
void Drivetrain::Drive(double right, double left)
{
    spdlog::trace("Drive({}, {})", right, left);

    if (IS_DRIVETRAIN_OMNIBASE)
    {
        throw RobotError::RobotCriticalError("Drivetrain::Drive(double right, double left) : Cannot use this function for OMNI_BASE");
    }
    m_NeoMotorLeft.Set(left);
    m_NeoMotorRight.Set(right);
}

/**
 * @brief Gets the encoder values of the left and right motors for TANK_BASE
 * @warning  Does not work if the robot is OMNI_BASE
 *
 * @param encoderValues Array of 2 doubles where the encoder values will be stored
 */
void Drivetrain::GetEncoderValues(double (&encoderValues)[2])
{
    spdlog::trace("Drivetrain::GetEncoderValues()");
    encoderValues[0] = m_NeoMotorLeft.GetEncoder().GetPosition();
    encoderValues[1] = m_NeoMotorRight.GetEncoder().GetPosition();
}
#endif