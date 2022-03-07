// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Hood.h"

#include <frc/livewindow/LiveWindow.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/shuffleboard/Shuffleboard.h>
#include <spdlog/spdlog.h>

Hood::Hood()
    : PIDSubsystem(frc2::PIDController{0.035, 0.008, 0.0004})
{
  m_encoderHood.SetDistancePerRotation(-(58 / 4.2));

  this->Enable();
  this->SetSetpoint(0.0);

  m_HoodMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
  m_HoodMotor.SetInverted(true);
  GetController().SetIntegratorRange(-5, 5);
}

void Hood::ResetEncoders()
{
  while (!m_encoderHood.IsConnected())
  {
  }
  m_encoderHood.Reset();
  m_HoodMotor.GetEncoder().SetPosition(0.0);
}

double Hood::GetMeasurement()
{
  return GetEncoder();
}

void Hood::UseOutput(double output, double setpoint)
{

  m_HoodMotor.Set(std::clamp(output, -0.4, 0.4));
  frc::SmartDashboard::PutNumber("outputHood", output);
}

double Hood::GetEncoder()
{
  return m_encoderHood.GetDistance();
}

void Hood::SetPID(double p, double i, double d)
{
  this->GetController().SetP(p);
  this->GetController().SetI(i);
  this->GetController().SetD(d);
}
