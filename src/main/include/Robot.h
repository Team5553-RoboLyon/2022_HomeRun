// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/livewindow/LiveWindow.h>
#include <frc/TimedRobot.h>
#include <frc/Joystick.h>
#include <spdlog/spdlog.h>

#include "Shooter.h"

#define SPEED_TO_RPM(x) ((x * 600) / 2048)

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
  void TestInit() override;

private:
  frc::Joystick m_Joystick{0};
  Shooter m_Shooter;
};
