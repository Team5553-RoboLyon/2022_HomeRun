// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/TimedRobot.h>
#include <frc2/command/Command.h>
#include <rev/CANSparkMax.h>
#include <frc/XboxController.h>
#include <units/voltage.h>

class Robot : public frc::TimedRobot
{
public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;

private:
  rev::CANSparkMax m_moteur{1, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax m_moteurFollower{2, rev::CANSparkMax::MotorType::kBrushless};

  frc::XboxController m_driverController{0};

  units::volt_t speed;
  double value;
};
