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
#include <ctre/phoenix/motorcontrol/can/TalonFX.h>

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
  rev::CANSparkMax m_leftMotor{1, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax m_leftMotorFollower{2, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax m_rightMotor{7, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax m_rightMotorFollower{6, rev::CANSparkMax::MotorType::kBrushless};
  ctre::phoenix::motorcontrol::can::TalonFX m_OmniMotor{5};
  frc::Joystick m_joystickRight{0};
  frc::Joystick m_joystickLeft{1};
  frc::DutyCycleEncoder m_encoderRotatingArms{0};
  frc::DutyCycleEncoder m_encoderClimber{1};
  frc::DoubleSolenoid m_solenoidRotatingArms{frc::PneumaticsModuleType::CTREPCM, 1, 0};
  frc::DoubleSolenoid m_solenoidIntake{frc::PneumaticsModuleType::CTREPCM, 3, 2};
  frc::Compressor m_compressor{frc::PneumaticsModuleType::CTREPCM};
  double time = 0;

  double m_speedPID;
  double m_speedCoef;
  double m_setpoint;
  double m_lastError;
  double m_error;
  double m_integrative;
  double m_derivative;
  double kP = 0.1;
  double kI = 0.0001;
  double kD = 0.001;
};
