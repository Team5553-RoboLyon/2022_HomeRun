// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <frc/smartdashboard/SmartDashboard.h>

#define MAX_HEIGHT_CLIMBER 56.4 // In rotations

void Robot::RobotInit()
{
  m_speedShooter = 0.0;
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want to run during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic()
{
  if (m_file.is_open())
  {
    // Get timestamp as an integer
    m_file << frc::Timer::GetFPGATimestamp().value() << ";";
    m_file << m_PDP.GetVoltage() << ";";
    for (int i = 0; i < 16; i++)
    {
      m_file << m_PDP.GetCurrent(i) << ";";
    }
    m_file << m_ShooterMotorLeft.GetSensorCollection().GetIntegratedSensorAbsolutePosition() << ";";
    m_file << m_ShooterMotorRight.GetSensorCollection().GetIntegratedSensorAbsolutePosition() << ";";
    m_file << m_ShooterMotorLeft.GetBusVoltage() << ";";
    m_file << m_ShooterMotorRight.GetBusVoltage() << ";";
    m_file << m_ShooterMotorLeft.GetStatorCurrent() << ";";
    m_file << m_ShooterMotorRight.GetStatorCurrent() << ";";
    m_file << m_ShooterMotorLeft.GetTemperature() << ";";
    m_file << m_ShooterMotorRight.GetTemperature() << ";";
    m_file << m_ShooterMotorLeft.GetMotorOutputPercent() << ";";
    m_file << m_ShooterMotorRight.GetMotorOutputPercent() << ";\n";
    m_file.flush();
  }
}

/**
 * This function is called once each time the robot enters Disabled mode. You
 * can use it to reset any subsystem information you want to clear when the
 * robot is disabled.
 */
void Robot::DisabledInit()
{
  if (m_file.is_open())
    m_file.close();
}

void Robot::DisabledPeriodic() {}

/**
 * This autonomous runs the autonomous command selected by your {@link
 * RobotContainer} class.
 */
void Robot::AutonomousInit()
{
}

void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit()
{
  m_ShooterMotorLeft.ConfigFactoryDefault();
  m_ShooterMotorRight.ConfigFactoryDefault();

  m_ShooterMotorLeft.SetInverted(true);
  m_ShooterMotorRight.SetInverted(false);

  // Get time from the computer to use for logging file name
  time_t rawtime;
  struct tm *timeinfo;
  char buffer[80];
  time(&rawtime);
  timeinfo = localtime(&rawtime);
  strftime(buffer, 80, "%Y-%m-%d-%H-%M-%S", timeinfo);
  m_file.open("/home/lvuser/logfile-" + std::string(buffer) + ".csv", std::ios::out);
  m_file << "Time;Voltage;";
  m_file << "Current Channel 1;Current Channel 2;Current Channel 3;";
  m_file << "Current Channel 4;Current Channel 5;Current Channel 6;";
  m_file << "Current Channel 7;Current Channel 8;Current Channel 9;";
  m_file << "Current Channel 10;Current Channel 11;Current Channel 12;";
  m_file << "Current Channel 13;Current Channel 14;Current Channel 15;";
  m_file << "Current Channel 16;Shooter Motor Left Encoder;Shooter Motor Right Encoder;";
  m_file << "Shooter Motor Left Speed;Shooter Motor Right Speed;";
  m_file << "Shooter Motor Left Voltage;Shooter Motor Right Voltage;";
  m_file << "Shooter Motor Left Current;Shooter Motor Right Current;";
  m_file << "Shooter Motor Left Temperature;Shooter Motor Right Temperature;";
  m_file << "Shooter Motor Left Setpoint;Shooter Motor Right Setpoint;\n";
}

/**
 * This function is called periodically during operator control.
 */
void Robot::TeleopPeriodic()
{
  double joystick = m_Joystick.GetThrottle();
  double speedHood = m_Joystick.GetY() * 0.2;
  frc::SmartDashboard::PutNumber("vitesse shooter", joystick);
  frc::SmartDashboard::PutNumber("vitesse hood", speedHood);
  frc::SmartDashboard::PutNumber("encodeur 1", SPEED_TO_RPM(m_ShooterMotorRight.GetSensorCollection().GetIntegratedSensorVelocity()));
  frc::SmartDashboard::PutNumber("encodeur 2", SPEED_TO_RPM(-m_ShooterMotorLeft.GetSensorCollection().GetIntegratedSensorVelocity()));
  // frc::SmartDashboard::PutNumber("encodeur mini NEO",ALEXANDRE tu peux mettre ici le getencoder du mini neo stp);

  if (m_Joystick.GetRawButton(1))
  {
    m_ShooterMotorRight.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, joystick);
    m_ShooterMotorLeft.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, joystick);
  }
  else
  {
    m_ShooterMotorRight.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0.0);
    m_ShooterMotorLeft.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0.0);
  }

  m_HoodMotor.Set(speedHood);
}

/**
 * This function is called periodically during test mode.
 */
void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main()
{
  return frc::StartRobot<Robot>();
}
#endif
