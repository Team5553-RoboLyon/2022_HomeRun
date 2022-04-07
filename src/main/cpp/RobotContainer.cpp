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

  if (m_Gearbox.GetPTOState() == Gearbox::PTOState::Driving)
    m_Drivetrain.SetDefaultCommand(Drive([=]
                                         { return -m_DriverLeftJoystick.GetY(); },
                                         [=]
                                         { return m_DriverRightJoystick.GetZ(); },
                                         &m_Drivetrain));

  m_CameraPilote = frc::CameraServer::StartAutomaticCapture();
  m_CameraPilote.SetResolution(320, 240);
  m_CameraPilote.SetFPS(12);
  m_Compressor.Disable();

  // m_Climber.SetDefaultCommand(ClimberActiveMotor(&m_Climber, [=]
  //                                                { return m_DriverRightJoystick.GetX(); }));
}

#if GEARBOX
/**
 * @brief Gets the encoder values of the left and right external encoders
 *
 * @param encoderValues Array of 2 doubles where the encoder values will be stored
 */
void RobotContainer::GetDrivetrainEncoderValues(double (&encoderValues)[2])
{
  m_Gearbox.GetEncoderValues(encoderValues);
}

void RobotContainer::SetMotorVoltagesWhenAutonomous(units::voltage::volt_t l1, units::voltage::volt_t l2, units::voltage::volt_t r1, units::voltage::volt_t r2)
{
  if (!frc::DriverStation::IsAutonomous())
  {
    spdlog::critical("RobotContainer::SetMotorVoltagesWhenAutonomous() Robot is not in Autonomous mode !!!!");
    return;
  }
  else
  {
    m_Gearbox.SetVoltageEveryone(l1, l2, r1, r2, Gearbox::PTOState::Driving);
  }
}

void RobotContainer::SetPTOWhenAutonomous(Gearbox::PTOState ptoState)
{
  if (!frc::DriverStation::IsAutonomous())
  {
    spdlog::critical("RobotContainer::SetPTOWhenAutonomous() Robot is not in Autonomous mode !!!!");
    return;
  }
  else
  {
    m_Gearbox.SetPTOState(ptoState);
  }
}

void RobotContainer::InitTeleopPeriod()
{
#if HOOD
  m_Hood.ResetPID();
#endif

#if GEARBOX
  m_Gearbox.InitTeleopPeriod();
#endif
}
#endif

void RobotContainer::ConfigureButtonBindings()
{
  frc2::CommandScheduler::GetInstance().ClearButtons();
  spdlog::debug("RobotContainer::ConfigureButtonBindings()");

#if GEARBOX && CLIMBER
  frc2::JoystickButton m_buttonChangeModeBase = frc2::JoystickButton(&m_DriverRightJoystick, 3);
  m_buttonChangeModeBase.WhenActive(frc2::InstantCommand([this]
                                                         { 
                                                           if (m_Gearbox.GetPTOState() == Gearbox::PTOState::Driving){
                                                            m_Gearbox.SetPTOState(Gearbox::PTOState::Climbing);
                                                            m_Drivetrain.SetDefaultCommand(frc2::InstantCommand());
                                                            m_Climber.SetDefaultCommand(Climb(
                                                              Climb([=]
                                                                { return -m_DriverLeftJoystick.GetY(); },
                                                                [=]
                                                                { return m_DriverRightJoystick.GetZ(); },
                                                                &m_Climber
                                                            )));

                                                           } else{
                                                             m_Gearbox.SetPTOState(Gearbox::PTOState::Driving);
                                                            m_Drivetrain.SetDefaultCommand(Drive([=]
                                                                { return -m_DriverLeftJoystick.GetY(); },
                                                                [=]
                                                                { return m_DriverRightJoystick.GetZ(); },
                                                                &m_Drivetrain));
                                                                m_Climber.SetDefaultCommand(frc2::InstantCommand());

                                                           } }));

#endif

#if INTAKE
  frc2::JoystickButton m_buttonIntakeChangePosition = frc2::JoystickButton(&m_DriverRightJoystick, 2);
  m_buttonIntakeChangePosition.WhileActiveOnce(ChangeIntakePosition(&m_Intake));

  frc2::JoystickButton m_buttonIntakeActiveMotor = frc2::JoystickButton(&m_DriverRightJoystick, 1);
  m_buttonIntakeActiveMotor.WhileActiveContinous(ActiveIntakeMotor(&m_Intake));

  frc2::JoystickButton m_buttonIntakeUnblockMotor = frc2::JoystickButton(&m_DriverLeftJoystick, 11);
  m_buttonIntakeUnblockMotor.WhileActiveContinous(UnblockIntakeMotor(&m_Intake));
#endif

#if CONVEYOR
  frc2::JoystickButton m_buttonConveyorFeederActiveMotor = frc2::JoystickButton(&m_DriverLeftJoystick, 1);
  m_buttonConveyorFeederActiveMotor.WhileActiveContinous(ActiveConveyorFeederMotor(&m_Conveyor, &m_Shooter));

  // frc2::JoystickButton m_buttonFeederActiveMotor = frc2::JoystickButton(&m_DriverLeftJoystick, 3);
  // m_buttonFeederActiveMotor.WhileActiveContinous(ActiveFeederMotor(&m_Conveyor));

  frc2::JoystickButton m_buttonConveyorUnblockMotor = frc2::JoystickButton(&m_DriverRightJoystick, 11);
  m_buttonConveyorUnblockMotor.WhileActiveContinous(UnblockConveyorMotor(&m_Conveyor));

  frc2::JoystickButton m_buttonFeederUnblockMotor = frc2::JoystickButton(&m_DriverRightJoystick, 12);
  m_buttonFeederUnblockMotor.WhileActiveContinous(UnblockFeederMotor(&m_Conveyor));
#endif

#if INTAKE && CONVEYOR
  frc2::JoystickButton m_buttonIntakeConvoyerActiveMotor = frc2::JoystickButton(&m_DriverLeftJoystick, 2);
  m_buttonIntakeConvoyerActiveMotor.WhileActiveContinous(frc2::ParallelCommandGroup(ActiveIntakeMotor(&m_Intake), ActiveConveyorMotor(&m_Conveyor)));
#endif

  frc2::JoystickButton m_buttonCompressor = frc2::JoystickButton(&m_DriverRightJoystick, 10);
  m_buttonCompressor.WhenActive(frc2::InstantCommand([this]
                                                     {if (m_Compressor.Enabled()){
                                                           m_Compressor.Disable();
                                                         }else{
                                                           m_Compressor.EnableDigital();
                                                         } }));

  // frc2::JoystickButton m_buttonChangeModeHood = frc2::JoystickButton(&m_DriverLeftJoystick, 3);
  // m_buttonChangeModeHood.WhenActive(frc2::InstantCommand([this]
  //                                                        { if (m_Hood.m_state==m_Hood.Hood::state::Disabled)
  //                                                        {
  //                                                          m_Hood.Enable();
  //                                                        }
  //                                                        else
  //                                                        {
  //                                                          m_Hood.Disable();
  //                                                        } }));

#if SHOOTER && TURRET
  frc2::JoystickButton m_buttonAutoShoot = frc2::JoystickButton(&m_DriverLeftJoystick, 3);
  m_buttonAutoShoot.WhenHeld(SetShooterAuto(&m_Shooter, &m_Hood, &m_Turret, &m_Camera));

#endif
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
