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
#include <frc/Compressor.h>
#include "subsystem/Hood.h"
#include "subsystem/Turret.h"
#include "subsystem/Shooter.h"
#include "subsystem/ShooterFeedingSystem.h"
#include "Constants.h"
#include <photonlib/PhotonCamera.h>
#include <photonlib/PhotonUtils.h>
#include <iostream>
#include <fstream>

#define MAX_HEIGHT_CLIMBER 56.4
#define IS_CLIMBER_PID true

class Robot : public frc::TimedRobot
{
public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;

private:
  rev::CANSparkMax m_leftMotor{DRIVETRAIN_MOTOR_RIGHT_CAN_ID, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax m_leftMotorFollower{DRIVETRAIN_MOTOR_RIGHT_FOLLOWER_CAN_ID, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax m_rightMotor{DRIVETRAIN_MOTOR_LEFT_CAN_ID, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax m_rightMotorFollower{DRIVETRAIN_MOTOR_LEFT_FOLLOWER_CAN_ID, rev::CANSparkMax::MotorType::kBrushless};
  frc::Joystick m_joystickRight{0};
  frc::Joystick m_joystickLeft{1};
  frc::Compressor m_compressor{frc::PneumaticsModuleType::CTREPCM};
  double time = 0;

  Hood m_hood;
  Turret m_turret;
  Shooter m_shooter;
  ShooterFeedingSystem m_feedingSystem;

  double m_flyingWheelsSpeed = 0.0;
  photonlib::PhotonCamera m_camera{"photonvision"};
};
