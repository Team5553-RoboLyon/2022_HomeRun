// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystem/ShooterFeedingSystem.h"

ShooterFeedingSystem::ShooterFeedingSystem()
{
    m_ConveyorMotor.SetSmartCurrentLimit(CONVEYOR_CURRENT_LIMIT);

    m_ConveyorMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);

    m_FeederMotor.SetInverted(true);
    m_IntakeMotor.SetInverted(false);
    m_ConveyorMotor.SetInverted(false);

    m_ConveyorMotor.SetClosedLoopRampRate(CONVEYOR_RAMP_RATE);
    m_FeederMotor.ConfigClosedloopRamp(FEEDER_RAMP_RATE);
    m_IntakeMotor.ConfigClosedloopRamp(INTAKE_RAMP_RATE);

    m_ConveyorMotor.EnableVoltageCompensation(CONVEYOR_VOLTAGE_COMPENSATION);
    m_IntakeMotor.EnableVoltageCompensation(true);
    m_FeederMotor.EnableVoltageCompensation(true);

    m_FeederMotor.ConfigVoltageCompSaturation(FEEDER_VOLTAGE_COMPENSATION);
    m_IntakeMotor.ConfigVoltageCompSaturation(INTAKE_VOLTAGE_COMPENSATION);
}

// This method will be called once per scheduler run
void ShooterFeedingSystem::Periodic() {}

void ShooterFeedingSystem::ActivateConveyor()
{
    m_ConveyorMotor.Set(CONVEYOR_MOTOR_SPEED);
}

void ShooterFeedingSystem::ActivateFeeder()
{
    m_FeederMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, FEEDER_MOTOR_SPEED);
}

void ShooterFeedingSystem::ActivateIntake()
{
    m_IntakeMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, INTAKE_MOTOR_SPEED);
}

void ShooterFeedingSystem::StopIntake()
{
    m_IntakeMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0.0);
}

void ShooterFeedingSystem::StopConveyor()
{
    m_ConveyorMotor.Set(0.0);
}

void ShooterFeedingSystem::StopFeeder()
{
    m_FeederMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0.0);
}

void ShooterFeedingSystem::UnblockConveyor()
{
    m_ConveyorMotor.Set(CONVEYOR_UNBLOCK_SPEED);
}

void ShooterFeedingSystem::UnblockFeeder()
{
    m_FeederMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, CONVEYOR_UNBLOCK_SPEED);
}

frc::DoubleSolenoid::Value ShooterFeedingSystem::GetIntakeState()
{
    return m_Solenoid.Get();
}

void ShooterFeedingSystem::SetIntakeState(frc::DoubleSolenoid::Value state)
{
    m_Solenoid.Set(state);
}