// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/Command.h>
#include <frc/Joystick.h>
#include <frc2/command/button/Trigger.h>
#include <frc2/command/button/JoystickButton.h>
#include <frc2/command/InstantCommand.h>
#include <frc/DriverStation.h>
#include "lib/RobotError.h"

#include "commands/auto/Auto.h"

#include "Constants.h"

#if GEARBOX
#include "subsystems/Gearbox.h"
#endif

#if CLIMBER
#include "subsystems/Climber.h"
#include "commands/Climber/Climb.h"
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
#include "commands/Conveyor/IntakeConveyorMode.h"
#include "commands/Conveyor/UnblockConveyorMotor.h"
#include "commands/Conveyor/ActiveFeederMotor.h"
#endif

#if SHOOTER
#include "subsystems/Shooter.h"
#include "commands/Shoot/ActiveShooter.h"
#include "commands/Shoot/UnblockShooter.h"
#endif

#if TURRET
#include "subsystems/Turret.h"
#endif

#if HOOD
#include "subsystems/Hood.h"
#endif

#if CAMERA
#include "subsystems/Camera.h"
#endif

#if SHOOTER && TURRET
#include "commands/Shoot/SetShooterAuto.h"
#include "commands/Shoot/NearShoot.h"
#endif

#include "lib/JsonConfig.h"

#include <frc2/command/InstantCommand.h>
#include <frc2/command/ParallelCommandGroup.h>
#include <frc2/command/SequentialCommandGroup.h>
#include <frc/AnalogGyro.h>
#include <cameraserver/CameraServer.h>
#include <frc/Compressor.h>
#include "commands/global/CompleteInit.h"
#include "commands/gearbox/SwitchGearboxMode.h"

class RobotContainer
{
public:
  RobotContainer();

  frc2::Command *GetAutonomousCommand();
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
#if TURRET
  Turret m_Turret;
#endif
#if HOOD
  Hood m_Hood;
#endif

  cs::UsbCamera m_CameraPilote;
  Camera m_Camera;

  frc::Joystick m_DriverRightJoystick{DRIVER_JOYSTICK_RIGHT_ID};
  frc::Joystick m_DriverLeftJoystick{DRIVER_JOYSTICK_LEFT_ID};

  frc2::JoystickButton m_ThrottleLeft{&m_DriverLeftJoystick, 1};

  frc::Compressor m_Compressor{frc::PneumaticsModuleType::CTREPCM};

  frc::AnalogGyro m_gyro{0};
  frc2::SequentialCommandGroup m_autonomousGroupCommand = Auto();
};
