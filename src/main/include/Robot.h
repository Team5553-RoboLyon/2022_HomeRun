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
#include <ctre/phoenix/motorcontrol/can/VictorSPX.h>

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
  ctre::phoenix::motorcontrol::can::VictorSPX m_feederMotor{6};
  rev::CANSparkMax m_conveyorMotor{7, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  ctre::phoenix::motorcontrol::can::VictorSPX m_intakeMotor{8};
  ctre::phoenix::motorcontrol::can::TalonFX m_ShooterMotor{9};
  ctre::phoenix::motorcontrol::can::TalonFX m_ShooterMotorFollower{10};
  frc::Joystick m_joystickRight{0};
  frc::Joystick m_joystickLeft{1};
  frc::DoubleSolenoid m_solenoidIntake{frc::PneumaticsModuleType::CTREPCM, 3, 2};
  frc::Compressor m_compressor{frc::PneumaticsModuleType::CTREPCM};
};
