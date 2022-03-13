// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Hood copy.h"

#include <frc/livewindow/LiveWindow.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/shuffleboard/Shuffleboard.h>
#include <spdlog/spdlog.h>

HoodCopy::HoodCopy()
    : PIDSubsystem(frc2::PIDController{0.02, 0.0032, 0.0008})
{

  Enable();
  SetSetpoint(0.0);

  m_HoodMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
  m_HoodMotor.SetInverted(true);
  GetController().SetIntegratorRange(-5, 5);

  m_encoderhood = new rev::SparkMaxRelativeEncoder{m_HoodMotor.GetEncoder()};

  m_encoderhood->SetPositionConversionFactor((58 / 16.738)); //-(58 / 16.738)
}

void HoodCopy::ResetEncoders()
{
  m_encoderhood->SetPosition(0.0);
}

double HoodCopy::GetMeasurement()
{
  return GetEncoder();
}

void HoodCopy::UseOutput(double output, double setpoint)
{

  m_HoodMotor.Set(std::clamp(output, -0.4, 0.4));
  frc::SmartDashboard::PutNumber("outputHood 2", output);
}

double HoodCopy::GetEncoder()
{

  frc::SmartDashboard::PutNumber("hood encoder 2", m_encoderhood->GetPosition());
  return m_encoderhood->GetPosition();
}

void HoodCopy::SetPID(double p, double i, double d)
{
  this->GetController().SetP(p);
  this->GetController().SetI(i);
  this->GetController().SetD(d);
}
