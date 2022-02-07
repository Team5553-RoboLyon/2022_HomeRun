#pragma once
#include "subsystems/Conveyor.h"

Conveyor::Conveyor()
{
    m_ConveyorMotor.SetInverted(true);
}

void Conveyor::ActiveMotor() { m_ConveyorMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, CONVEYOR_MOTOR_SPEED); }

void Conveyor::UnblockMotor() { m_ConveyorMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, -CONVEYOR_MOTOR_SPEED); }

void Conveyor::StopMotor() { m_ConveyorMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0.0); }