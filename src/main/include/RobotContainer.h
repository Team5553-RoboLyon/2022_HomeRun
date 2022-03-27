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
#include "subsystems/Gearbox.h"
#include "subsystems/Climber.h"
#include "subsystems/Drivetrain.h"
#include "subsystems/Intake.h"
#include "subsystems/Conveyor.h"
#include "subsystems/Shooter.h"
#include "subsystems/Hood.h"
#include "commands/drivetrain/Drive.h"
#include "commands/Intake/ChangeIntakePosition.h"
#include "commands/Intake/ActiveIntakeMotor.h"
#include "commands/Intake/UnblockIntakeMotor.h"
#include "commands/Conveyor/ActiveConveyorMotor.h"
#include "commands/Conveyor/UnblockConveyorMotor.h"
#include "commands/Conveyor/ActiveFeederMotor.h"
#include "commands/Conveyor/UnblockFeederMotor.h"
#include "commands/Shoot/ActiveShooter.h"
#include "commands/Shoot/TurnHood.h"
#include "commands/Shoot/TurnHoodBas.h"
#include "lib/JsonConfig.h"

#include "commands/tests/DrivetrainDirectionTest.h"
#include <frc2/command/InstantCommand.h>

class RobotContainer
{
public:
  RobotContainer();
  // void StartTests();

private:
  void ConfigureButtonBindings();

  Drivetrain m_Drivetrain;
  Intake m_Intake;
  Conveyor m_Conveyor;
  Shooter m_Shooter;
  Hood m_Hood;

  frc::Joystick m_DriverRightJoystick{DRIVER_JOYSTICK_RIGHT_ID};
  frc::Joystick m_DriverLeftJoystick{DRIVER_JOYSTICK_LEFT_ID};

  frc2::JoystickButton m_ThrottleLeft{&m_DriverLeftJoystick, 1};
  // frc2::Trigger m_ThrottleLeft{[this]
  //                              { return m_DriverRightJoystick.GetThrottle(); }};
};
