// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/CommandScheduler.h>

#include <ostream>

void Robot::RobotInit()
{
  std::vector<spdlog::sink_ptr> sinks;
  sinks.push_back(std::make_shared<spdlog::sinks::stdout_sink_st>());

  // Get timestamp
  auto now = std::chrono::system_clock::now();
  auto in_time_t = std::chrono::system_clock::to_time_t(now);
  std::stringstream ss;
  ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d_%H-%M-%S");
  std::string time_stamp = ss.str();
  std::string log_file_name = "/home/lvuser/logs/" + time_stamp + ".log";

  sinks.push_back(std::make_shared<spdlog::sinks::basic_file_sink_st>(log_file_name));
  auto combined_logger = std::make_shared<spdlog::logger>("LOGGER", begin(sinks), end(sinks));

  spdlog::set_default_logger(combined_logger);

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
