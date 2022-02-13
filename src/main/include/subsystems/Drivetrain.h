// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.
#pragma once

#include <frc2/command/SubsystemBase.h>
#include <rev/CANSparkMax.h>
#include <ctre/phoenix/motorcontrol/can/TalonFX.h>
#include <spdlog/spdlog.h>
#include "lib/wrappers/CANSparkMaxWrapper.h"

#include "lib/RobotError.h"
#include "Constants.h"

class Drivetrain : public frc2::SubsystemBase
{
public:
  Drivetrain();
  void Periodic() override;
  void Stop();
#if IS_DRIVETRAIN_OMNIBASE
  void Drive(double right, double left, double lateral);
  void GetEncoderValues(double (&encoderValues)[3]);
#else
  void Drive(double right, double left);
  void GetEncoderValues(double (&encoderValues)[2])
#endif

private:
  CANSparkMaxWrapper m_NeoMotorRight{DRIVETRAIN_NEO_MOTOR_RIGHT_ID, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  CANSparkMaxWrapper m_NeoMotorRightFollower{DRIVETRAIN_NEO_MOTOR_RIGHT_FOLLOWER_ID, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  CANSparkMaxWrapper m_NeoMotorLeft{DRIVETRAIN_NEO_MOTOR_LEFT_ID, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  CANSparkMaxWrapper m_NeoMotorLeftFollower{DRIVETRAIN_NEO_MOTOR_LEFT_FOLLOWER_ID, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
#if IS_DRIVETRAIN_OMNIBASE
  ctre::phoenix::motorcontrol::can::TalonFX m_FalconMotor{DRIVETRAIN_FALCON_MOTOR_OMNI_ID};
#endif
};
