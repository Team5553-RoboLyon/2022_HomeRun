// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystem/ShooterFeedingSystem.h"

ShooterFeedingSystem::ShooterFeedingSystem(){
    m_ConveyorMotor.SetSmartCurrentLimit(CONVEYOR_CURRENT_LIMIT);

    m_ConveyorMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
};

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

frc::DoubleSolenoid::Value ShooterFeedingSystem::GetIntakeState()
{
    return m_Solenoid.Get();
}

void ShooterFeedingSystem::SetIntakeState(frc::DoubleSolenoid::Value state)
{
    m_Solenoid.Set(state);
}