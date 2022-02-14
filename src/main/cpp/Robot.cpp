// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/CommandScheduler.h>

#include <ostream>

void Robot::RobotInit()
{
  auto logger = spdlog::stdout_logger_mt("LOGGER");
  spdlog::set_default_logger(logger);

  spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%n] [%^%l%$] %v");
  spdlog::set_level(spdlog::level::debug);

  // JsonConfig::LoadConfig(CONFIG_FILE_PATH);
  spdlog::trace("RobotInit()");

  spdlog::debug("OMNIBASE : {}", IS_DRIVETRAIN_OMNIBASE);
  planetaryencoder.Reset();
}

void Robot::RobotPeriodic()
{
  spdlog::trace("RobotPeriodic()");
  frc2::CommandScheduler::GetInstance().Run();
}

void Robot::DisabledInit()
{
  spdlog::trace("DisabledInit()");
}

void Robot::DisabledPeriodic()
{
  spdlog::trace("DisabledPeriodic()");
}

void Robot::AutonomousInit()
{
  spdlog::trace("AutonomousInit()");
}

void Robot::AutonomousPeriodic()
{
  spdlog::trace("AutonomousPeriodic()");
}

void Robot::TeleopInit()
{
  spdlog::trace("TeleopInit()");
}

void Robot::TeleopPeriodic()
{
  spdlog::trace("TeleopPeriodic()");
}

void Robot::TestInit()
{
  spdlog::trace("TestInit()");
  m_container.StartTests();
}

void Robot::TestPeriodic()
{
  spdlog::trace("TestPeriodic()");
}

#ifndef RUNNING_FRC_TESTS
int main()
{
  return frc::StartRobot<Robot>();
}
#endif
