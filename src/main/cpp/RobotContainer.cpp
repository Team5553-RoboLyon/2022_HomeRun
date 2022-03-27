// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

RobotContainer::RobotContainer()
{
  spdlog::trace("RobotContainer::RobotContainer()");
  // Initialize all of your commands and subsystems here

  // Configure the button bindings
  ConfigureButtonBindings();
  // frc::Joystick *joystick1 = (JsonConfig::GetConfig()["invertJoysticks"].get<bool>() ? &m_DriverRightJoystick : &m_DriverLeftJoystick);
  // frc::Joystick *joystick2 = (JsonConfig::GetConfig()["invertJoysticks"].get<bool>() ? &m_DriverLeftJoystick : &m_DriverRightJoystick);
  m_Drivetrain.SetDefaultCommand(Drive([=]
                                       { return -m_DriverLeftJoystick.GetY(); },
                                       [=]
                                       { return m_DriverRightJoystick.GetZ(); },
                                       [=]
                                       { return m_DriverRightJoystick.GetX(); },
                                       &m_Drivetrain));

  // m_Climber.SetDefaultCommand(ClimberActiveMotor(&m_Climber, [=]
  //                                                { return m_DriverRightJoystick.GetX(); }));
}

void RobotContainer::ConfigureButtonBindings()
{
  frc2::CommandScheduler::GetInstance().ClearButtons();
  spdlog::debug("RobotContainer::ConfigureButtonBindings()");

  frc2::JoystickButton m_buttonChangeModeBase = frc2::JoystickButton(&m_DriverRightJoystick, 3);
  frc2::JoystickButton m_buttonIntakeChangePosition = frc2::JoystickButton(&m_DriverLeftJoystick, 3);

  frc2::JoystickButton m_buttonIntakeActiveMotor = frc2::JoystickButton(&m_DriverLeftJoystick, 2);
  frc2::JoystickButton m_buttonConveyorActiveMotor = frc2::JoystickButton(&m_DriverRightJoystick, 1);
  frc2::JoystickButton m_buttonFeederActiveMotor = frc2::JoystickButton(&m_DriverRightJoystick, 2);

  frc2::JoystickButton m_buttonConveyorUnblockMotor = frc2::JoystickButton(&m_DriverRightJoystick, 11);
  frc2::JoystickButton m_buttonFeederUnblockMotor = frc2::JoystickButton(&m_DriverRightJoystick, 12);
  frc2::JoystickButton m_buttonIntakeUnblockMotor = frc2::JoystickButton(&m_DriverLeftJoystick, 11);

  frc2::JoystickButton m_buttonShooterActiveMotor = frc2::JoystickButton(&m_DriverLeftJoystick, 1);

  frc2::JoystickButton m_buttonHoodUpMotor = frc2::JoystickButton(&m_DriverLeftJoystick, 8);
  frc2::JoystickButton m_buttonHoodLowMotor = frc2::JoystickButton(&m_DriverLeftJoystick, 9);

  // frc2::JoystickButton m_buttonIntakeOpen = frc2::JoystickButton(&m_DriverRightJoystick, 1);
  m_buttonChangeModeBase.WhenActive(frc2::InstantCommand([this]
                                                         { m_Drivetrain.ChangeDrivePosition(); }));

  m_buttonIntakeChangePosition.WhileActiveOnce(ChangeIntakePosition(&m_Intake));

  m_buttonIntakeActiveMotor.WhileActiveContinous(ActiveIntakeMotor(&m_Intake));
  m_buttonFeederActiveMotor.WhileActiveContinous(ActiveFeederMotor(&m_Conveyor));
  m_buttonConveyorActiveMotor.WhileActiveContinous(ActiveConveyorMotor(&m_Conveyor));

  m_buttonConveyorUnblockMotor.WhileActiveContinous(UnblockConveyorMotor(&m_Conveyor));
  m_buttonFeederUnblockMotor.WhileActiveContinous(UnblockFeederMotor(&m_Conveyor));
  m_buttonIntakeUnblockMotor.WhileActiveContinous(UnblockIntakeMotor(&m_Intake));

  m_buttonShooterActiveMotor.WhileActiveContinous(ActiveShooter(&m_Shooter));

  m_buttonHoodUpMotor.WhileActiveContinous(TurnHood(&m_Hood));
  m_buttonHoodLowMotor.WhileActiveContinous(TurnHoodBas(&m_Hood));
}

// void RobotContainer::StartTests()
// {
//   if (!frc::DriverStation::IsTest())
//     throw RobotError::RobotCriticalError("RobotContainer::StartTests() called when not in test mode");

//   spdlog::trace("RobotContainer::StartTests()");

//   try
//   {
//     DrivetrainDirectionTest command(&m_Drivetrain);
//     frc2::CommandScheduler::GetInstance().Schedule(&command);
//   }
//   catch (std::exception &e)
//   {
//     spdlog::error("DrivetrainTests failed: {}", e.what());
//   }
// }
