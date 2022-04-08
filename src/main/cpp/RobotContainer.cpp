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
                                       &m_Drivetrain));

  m_Climber.SetDefaultCommand(Climb(
      [=]
      { return m_DriverLeftJoystick.GetY(); },
      [=]
      { return m_DriverRightJoystick.GetY(); },
      &m_Climber));

  m_CameraPilote = frc::CameraServer::StartAutomaticCapture();
  m_CameraPilote.SetResolution(320, 240);
  m_CameraPilote.SetFPS(12);

  m_Compressor.EnableDigital();

  m_Camera.DisableLED();

  m_Drivetrain.Enable();
}

/**
 * @brief Gets the encoder values of the left and right external encoders
 *
 * @param encoderValues Array of 2 doubles where the encoder values will be stored
 */
void RobotContainer::GetDrivetrainEncoderValues(double (&encoderValues)[2])
{
  m_Gearbox.GetEncoderValues(encoderValues);
}

frc2::Command *RobotContainer::GetAutonomousCommand()
{
  return &m_autonomousGroupCommand;
}
void RobotContainer::InitTeleopPeriod()
{
  CompleteInit(&m_Camera, &m_Hood, &m_Gearbox, &m_Drivetrain).Schedule();
}

void RobotContainer::ConfigureButtonBindings()
{
  frc2::CommandScheduler::GetInstance().ClearButtons();
  spdlog::debug("RobotContainer::ConfigureButtonBindings()");

#if GEARBOX && CLIMBER
  frc2::JoystickButton m_buttonChangeModeBase = frc2::JoystickButton(&m_DriverRightJoystick, 2);
  m_buttonChangeModeBase.WhenActive(SwitchGearboxMode((m_gearbox, m_drivetrain, m_climber, m_intake, m_turret, m_hood, m_conveyor, m_shooter));

#endif

#if INTAKE
  frc2::JoystickButton m_buttonIntakeChangePosition = frc2::JoystickButton(&m_DriverLeftJoystick, 2);
  m_buttonIntakeChangePosition.WhileActiveOnce(ChangeIntakePosition(&m_Intake));

  frc2::JoystickButton m_buttonIntakeUnblockMotor = frc2::JoystickButton(&m_DriverLeftJoystick, 11);
  m_buttonIntakeUnblockMotor.WhileActiveContinous(frc2::ParallelCommandGroup(UnblockIntakeMotor(&m_Intake), UnblockConveyorMotor(&m_Conveyor), UnblockShooter(&m_Shooter)));
#endif

#if INTAKE && CONVEYOR
  frc2::JoystickButton m_buttonIntakeConvoyerActiveMotor = frc2::JoystickButton(&m_DriverLeftJoystick, 1);
  m_buttonIntakeConvoyerActiveMotor.WhileActiveContinous(frc2::ParallelCommandGroup(ActiveIntakeMotor(&m_Intake), ActiveConveyorMotor(&m_Conveyor)));
#endif

  frc2::JoystickButton m_buttonCompressor = frc2::JoystickButton(&m_DriverLeftJoystick, 6);
  m_buttonCompressor.WhenActive(frc2::InstantCommand([this]
  {
    if (m_Compressor.Enabled())
    {
      m_Compressor.Disable();
    }
    else
    {
      m_Compressor.EnableDigital();
    } 
  }));

#if SHOOTER && TURRET
  frc2::JoystickButton m_buttonAutoShoot = frc2::JoystickButton(&m_DriverRightJoystick, 1);
  m_buttonAutoShoot.WhenHeld(SetShooterAuto(&m_Conveyor, &m_Shooter, &m_Hood, &m_Turret, &m_Camera));

  frc2::JoystickButton m_buttonShootNear = frc2::JoystickButton(&m_DriverRightJoystick, 4);
  m_buttonShootNear.WhenHeld(NearShoot(&m_Conveyor, &m_Shooter, &m_Hood, &m_Turret));
#endif

  frc2::JoystickButton m_buttonRemonteIntake = frc2::JoystickButton(&m_DriverLeftJoystick, 8);
  m_buttonRemonteIntake.WhenActive(frc2::InstantCommand([this]
                                                        {
    m_Intake.Close(); }));
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
