// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/Command.h>
#include <frc/Joystick.h>
#include <frc2/command/button/Trigger.h>
#include <frc2/command/button/JoystickButton.h>
#include <frc/DriverStation.h>
#include "lib/RobotError.h"

#include "Constants.h"

#if GEARBOX
#include "subsystems/Gearbox.h"
#endif

#if CLIMBER
#include "subsystems/Climber.h"
#endif

#if DRIVETRAIN
#include "subsystems/Drivetrain.h"
#include "commands/drivetrain/Drive.h"
#include "commands/tests/DrivetrainDirectionTest.h"
#endif

#if INTAKE
#include "subsystems/Intake.h"
#include "commands/Intake/ChangeIntakePosition.h"
#include "commands/Intake/ActiveIntakeMotor.h"
#include "commands/Intake/UnblockIntakeMotor.h"

#endif

#if CONVEYOR
#include "subsystems/Conveyor.h"
#include "commands/Conveyor/ActiveConveyorMotor.h"
#include "commands/Conveyor/UnblockConveyorMotor.h"
#include "commands/Conveyor/ActiveFeederMotor.h"
#include "commands/Conveyor/UnblockFeederMotor.h"
#include "commands/Conveyor/ActiveConveyorFeederMotor.h"
#endif

#if SHOOTER
#include "subsystems/Shooter.h"
#include "commands/Shoot/ActiveShooter.h"
#include "commands/Shoot/SetShooterAuto.h"
#endif

#if HOOD
#include "subsystems/Hood.h"
#endif

#include "lib/JsonConfig.h"

#include <frc2/command/InstantCommand.h>
#include <frc2/command/ParallelCommandGroup.h>
#include <cameraserver/CameraServer.h>
#include <frc/Compressor.h>

class RobotContainer
{
public:
  RobotContainer();
  // void StartTests();

#if GEARBOX
  void GetDrivetrainEncoderValues(double (&encoderValues)[2]);
  void SetMotorVoltagesWhenAutonomous(units::voltage::volt_t l1, units::voltage::volt_t l2, units::voltage::volt_t r1, units::voltage::volt_t r2);
  void SetPTOWhenAutonomous(Gearbox::PTOState ptoState);
#endif

  void InitTeleopPeriod();

private:
  void ConfigureButtonBindings();

#if GEARBOX
  Gearbox m_Gearbox;
#endif
#if CLIMBER
  Climber m_Climber{&m_Gearbox};
#endif
#if DRIVETRAIN
  Drivetrain m_Drivetrain{&m_Gearbox};
#endif
#if INTAKE
  Intake m_Intake;
#endif
#if CONVEYOR
  Conveyor m_Conveyor;
#endif
#if SHOOTER
  Shooter m_Shooter;
#endif

#if HOOD
  Hood m_Hood;
#endif
  cs::UsbCamera m_Camera;

  frc::Joystick m_DriverRightJoystick{DRIVER_JOYSTICK_RIGHT_ID};
  frc::Joystick m_DriverLeftJoystick{DRIVER_JOYSTICK_LEFT_ID};

  frc2::JoystickButton m_ThrottleLeft{&m_DriverLeftJoystick, 1};
  // frc2::Trigger m_ThrottleLeft{[this]
  //                              { return m_DriverRightJoystick.GetThrottle(); }};

  frc::Compressor m_Compressor{frc::PneumaticsModuleType::CTREPCM};
};
