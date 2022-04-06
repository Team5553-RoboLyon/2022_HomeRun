// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <rev/CANSparkMax.h>
#include "Constants.h"
#include <ctre/phoenix/motorcontrol/can/VictorSPX.h>
#include <frc/DoubleSolenoid.h>

class ShooterFeedingSystem : public frc2::SubsystemBase
{
public:
  ShooterFeedingSystem();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;
  void ActivateConveyor();
  void ActivateFeeder();
  void ActivateIntake();
  void StopIntake();
  void StopConveyor();
  void StopFeeder();
  void UnblockConveyor();
  void UnblockFeeder();
  void SetIntakeState(frc::DoubleSolenoid::Value state);
  frc::DoubleSolenoid::Value GetIntakeState();

private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  rev::CANSparkMax m_ConveyorMotor{CONVEYOR_MOTOR_CAN_ID, rev::CANSparkMax::MotorType::kBrushless};
  ctre::phoenix::motorcontrol::can::VictorSPX m_FeederMotor{FEEDER_MOTOR_CAN_ID};
  ctre::phoenix::motorcontrol::can::VictorSPX m_IntakeMotor{INTAKE_MOTOR_CAN_ID};

  frc::DoubleSolenoid m_Solenoid{frc::PneumaticsModuleType::CTREPCM, INTAKE_SOLENOID_ID_FORWARD, INTAKE_SOLENOID_ID_REVERSE};
};
