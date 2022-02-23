// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/TimedRobot.h>
#include <frc2/command/Command.h>
#include <frc/Joystick.h>
#include <frc/DutyCycleEncoder.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <ctre/phoenix/motorcontrol/can/VictorSPX.h >
#include <frc/DutyCycleEncoder.h>

#define ROTATION (190 / 18) * 30
class Robot : public frc::TimedRobot
{
public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;

private:
  frc::Joystick m_joystick{0};
  ctre::phoenix::motorcontrol::can::VictorSPX m_TurretMotor{1};
  frc::DutyCycleEncoder m_TurretEncoder{9};
};
