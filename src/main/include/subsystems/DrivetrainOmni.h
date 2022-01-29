// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <rev/CANSparkMax.h>
#include <ctre/phoenix/motorcontrol/can/TalonFX.h>

#include "Constants.h"

class Drivetrain : public frc2::SubsystemBase
{
public:
  Drivetrain();
  void Periodic() override;
  void Drive(double right, double left, double lateral);

private:
  rev::CANSparkMax m_NeoMotorRight{DRIVETRAIN_NEO_MOTOR_RIGHT_ID, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  rev::CANSparkMax m_NeoMotorRightFollower{DRIVETRAIN_NEO_MOTOR_RIGHT_FOLLOWER_ID, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  rev::CANSparkMax m_NeoMotorLeft{DRIVETRAIN_NEO_MOTOR_LEFT_ID, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  rev::CANSparkMax m_NeoMotorLeftFollower{DRIVETRAIN_NEO_MOTOR_LEFT_FOLLOWER_ID, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  ctre::phoenix::motorcontrol::can::TalonFX m_FalconMotor{DRIVETRAIN_FALCON_MOTOR_ID};
};
