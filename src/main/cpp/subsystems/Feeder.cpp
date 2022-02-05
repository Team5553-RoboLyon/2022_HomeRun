#include "subsystems/Feeder.h"

Feeder::Feeder()
{
    m_FeederMotor.SetInverted(true);
    m_FeederMotorFollower.SetInverted(false);
}

void Feeder::ActiveMotor() { m_FeederMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, FEEDER_MOTOR_SPEED); }

void Feeder::UnblockMotor() { m_FeederMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, -FEEDER_MOTOR_SPEED); }

void Feeder::StopMotor() { m_FeederMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0.0); }