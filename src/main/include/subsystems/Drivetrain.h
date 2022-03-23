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
#include <frc/Encoder.h>
#include "lib/HallSecurity.h"
#include <frc/DigitalInput.h>

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
  static std::string PTOStateIndexToString(PTOState ptoConfiguration);
  PTOState GetPTOState();
  void SetPTOState(PTOState ptoConfiguration);
  double GetMeasurement();
  void ResetEncoderClimber();
  void EnableClimber();
  void DisableClimber();
  void EnableRotatingArms();
  void DisableRotatingArms();

private:
  CANSparkMaxWrapper m_NeoMotorRight{DRIVETRAIN_NEO_MOTOR_RIGHT_ID, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  CANSparkMaxWrapper m_NeoMotorRightFollower{DRIVETRAIN_NEO_MOTOR_RIGHT_FOLLOWER_ID, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  CANSparkMaxWrapper m_NeoMotorLeft{DRIVETRAIN_NEO_MOTOR_LEFT_ID, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  CANSparkMaxWrapper m_NeoMotorLeftFollower{DRIVETRAIN_NEO_MOTOR_LEFT_FOLLOWER_ID, rev::CANSparkMaxLowLevel::MotorType::kBrushless};

  ctre::phoenix::motorcontrol::can::TalonFX m_FalconMotor{DRIVETRAIN_FALCON_MOTOR_OMNI_ID};

  frc::DoubleSolenoid m_solenoid{frc::PneumaticsModuleType::CTREPCM, DRIVETRAIN_SOLENOID_ID_FORWARD, DRIVETRAIN_SOLENOID_ID_REVERSE};
  PTOState m_ptoState = PTOState::None;

  enum state_Climber
  {
    init,
    goTo0,
    enable,
    disable,
  };

  enum state_RotatingArms
  {
    initRotate,
    goTo0Rotate,
    enableRotate,
    disableRotate,
  };
  state_Climber m_state_Climber = Drivetrain::state_Climber::init;
  state_RotatingArms m_state_RotatingArms = Drivetrain::state_RotatingArms::initRotate;

  frc::Encoder m_encoderClimber{10, 11};
  HallSecurity m_HallSensorClimber{4};

  frc::Encoder m_encoderRotatingArms{11, 12};
  frc::DigitalInput m_HallSensorRotatingArmRight{1};
  frc::DigitalInput m_HallSensorRotatingArmLeft{2};
};
