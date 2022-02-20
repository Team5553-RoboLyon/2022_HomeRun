// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/TimedRobot.h>
#include <frc2/command/Command.h>
#include <rev/CANSparkMax.h>
#include <frc/Joystick.h>
#include <frc/DutyCycleEncoder.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/DoubleSolenoid.h>

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
  rev::CANSparkMax m_leftMotor{1, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax m_leftMotorFollower{2, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax m_rightMotor{3, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax m_rightMotorFollower{4, rev::CANSparkMax::MotorType::kBrushless};
  frc::Joystick m_joystick{0};
  frc::DutyCycleEncoder m_encoder{1};
  frc::DoubleSolenoid m_solenoid{frc::PneumaticsModuleType::CTREPCM, 0, 1};
  double time = 0;
};
