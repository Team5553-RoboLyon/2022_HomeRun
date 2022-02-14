// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/TimedRobot.h>
#include <frc2/command/Command.h>
#include <rev/CANSparkMax.h>
#include <frc/Joystick.h>
#include <rev/SparkMaxRelativeEncoder.h>
#include <ctre/phoenix/motorcontrol/can/VictorSPX.h>
#include <spdlog/spdlog.h>

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
  rev::CANSparkMax m_ConveyorMotor{8, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  ctre::phoenix::motorcontrol::can::VictorSPX m_FeederMotorRight{1};
  ctre::phoenix::motorcontrol::can::VictorSPX m_FeederMotorLeft{2};
  frc::Joystick m_JoystickRight{0};
  frc::Joystick m_JoystickLeft{1};
  double m_speedFeeder;
  double m_speedConveyor;
};
