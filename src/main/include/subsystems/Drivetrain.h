// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.
#pragma once

#include <frc2/command/SubsystemBase.h>
#include <rev/CANSparkMax.h>
#include <ctre/phoenix/motorcontrol/can/TalonFX.h>
#include <spdlog/spdlog.h>
#include "lib/wrappers/CANSparkMaxWrapper.h"
#include <frc/DoubleSolenoid.h>

#include "lib/RobotError.h"
#include "Constants.h"

class Drivetrain : public frc2::SubsystemBase
{
public:
  enum class PTOState
  {
    Climbing,
    Driving,
    None
  };

  Drivetrain();
  void Periodic() override;
  void Stop();
  void Drive(double right, double left, double lateral, PTOState ptoConfigurationRequired);
  void GetEncoderValues(double (&encoderValues)[3]);
  double GetFalconSimulatedOutput();
  std::string PTOStateIndexToString(PTOState ptoConfiguration);
  PTOState GetPTOState();

private:
  CANSparkMaxWrapper m_NeoMotorRight{DRIVETRAIN_NEO_MOTOR_RIGHT_ID, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  CANSparkMaxWrapper m_NeoMotorRightFollower{DRIVETRAIN_NEO_MOTOR_RIGHT_FOLLOWER_ID, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  CANSparkMaxWrapper m_NeoMotorLeft{DRIVETRAIN_NEO_MOTOR_LEFT_ID, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  CANSparkMaxWrapper m_NeoMotorLeftFollower{DRIVETRAIN_NEO_MOTOR_LEFT_FOLLOWER_ID, rev::CANSparkMaxLowLevel::MotorType::kBrushless};

  ctre::phoenix::motorcontrol::can::TalonFX m_FalconMotor{DRIVETRAIN_FALCON_MOTOR_OMNI_ID};

  frc::DoubleSolenoid m_solenoidRotatingArms{frc::PneumaticsModuleType::CTREPCM, DRIVETRAIN_SOLENOID_ROTATINGARM_ID_FORWARD, DRIVETRAIN_SOLENOID_ROTATINGARM_ID_REVERSE};
  frc::DoubleSolenoid m_solenoidClimber{frc::PneumaticsModuleType::CTREPCM, DRIVETRAIN_SOLENOID_CLIMBER_ID_FORWARD, DRIVETRAIN_SOLENOID_CLIMBER_ID_REVERSE};
  PTOState m_ptoState = PTOState::None;
};
