// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Hood.h"

Hood::Hood() : PIDSubsystem(frc2::PIDController(HOOD_PID_P, HOOD_PID_I, HOOD_PID_D))
{
    m_HoodMotor.ConfigFactoryDefault();
    m_HoodMotor.SetInverted(false);
    m_HoodMotor.SetNeutralMode(ctre::phoenix::motorcontrol::NeutralMode::Brake);
    GetController().SetTolerance(HOOD_PID_TOLERANCE);
}

double Hood::GetMeasurement()
{
    return 0;
}

void Hood::UseOutput(double output, double setpoint)
{
    m_HoodMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, output);
}

bool Hood::AtSetpoint()
{
    return GetController().AtSetpoint();
}
