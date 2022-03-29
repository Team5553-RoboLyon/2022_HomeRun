// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <frc/smartdashboard/SmartDashboard.h>

#define MAX_HEIGHT_CLIMBER 56.4 // In rotations

void Robot::RobotInit()
{
}

void Robot::RobotPeriodic()
{
    frc2::CommandScheduler::GetInstance().Run();
    frc::SmartDashboard::PutNumber("encodeur Hood", m_Shooter.m_hood.GetMeasurement());
}

void Robot::DisabledInit()
{
}

void Robot::DisabledPeriodic() {}

void Robot::AutonomousInit()
{
}

void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit()
{

    // a mettre dans init de m_hood et m_turret
    // frc::SmartDashboard::PutNumber("Setpoint m_turret", 0.0);
    frc::SmartDashboard::PutNumber("Setpoint m_hood", frc::SmartDashboard::GetNumber("Setpoint m_hood", 0.0));
    frc::SmartDashboard::PutNumber("Shooter speed", 0.0);
}

void Robot::TeleopPeriodic()
{
    double joystick = m_Joystick.GetThrottle();
    frc::SmartDashboard::PutNumber("vitesse shooter", joystick);
    frc::SmartDashboard::PutNumber("encodeur", SPEED_TO_RPM(
                                                   m_Shooter.AppliedSpeed()));

    if (m_Joystick.GetRawButton(1))
    {
        m_Shooter.SetSpeed(frc::SmartDashboard::GetNumber("Shooter speed", 0.0));
    }
    else
    {
        m_Shooter.SetSpeed(0.0);
    }
    m_Shooter.m_hood.SetSetpoint(std::clamp(frc::SmartDashboard::GetNumber("Setpoint m_hood", 0.0), 1.0, 57.0));
}

void Robot::TestInit()
{
    frc::LiveWindow::SetEnabled(false);
    spdlog::info("testinit");
    // m_hood.Enable();
}

void Robot::TestPeriodic()
{
    spdlog::info("TestPeriodic");
}

#ifndef RUNNING_FRC_TESTS

int main()
{
    return frc::StartRobot<Robot>();
}

#endif
