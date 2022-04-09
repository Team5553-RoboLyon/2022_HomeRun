// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/TimedRobot.h>
#include <frc2/command/Command.h>
#include <iostream>
#include <iomanip>

#include "RobotContainer.h"
#include "Constants.h"
#include "lib/JsonConfig.h"

#include <spdlog/spdlog.h>
#include "spdlog/fmt/ostr.h" // must be included
#include "spdlog/sinks/stdout_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
#include <frc/DutyCycleEncoder.h>
#include <frc/DigitalInput.h>
#include <frc2/command/CommandScheduler.h>

#include <ostream>

#include "lib/N/NErrorHandling.h"
#include "lib/NL/MotionControl/Characterization/NLCharacterizationTable.h"
#include "lib/NL/MotionControl/NLDriveTrainSpecs.h"
#include "lib/NL/MotionControl/NLRobotPose.h"
#include "lib/NL/MotionControl/NLRamseteFollower.h"
#include "lib/NL/MotionControl/Trajectory/NLTrajectoryPack.h"

class Robot : public frc::TimedRobot
{
public:
  enum STATE
  {
    PATH_ERROR = 0, ///< L'initialisation du path following a rencontr� un probl�me ( erreur au chargement tr�s probablement ). Le Robot ne peut-�tre en �tat PATH_FOLLOWING.
    PATH_FOLLOWING, ///< Le robot est en �tat de suivit de chemin.
    PATH_END        ///< La Vitesse  est en d�passement.
  };

  void RobotInit();
  void RobotPeriodic();
  void DisabledInit();
  void DisabledPeriodic();
  void AutonomousInit();
  void AutonomousPeriodic();
  void TeleopInit();
  void TeleopPeriodic();
  void TestInit();
  void TestPeriodic();

private:
  // Have it null by default so that if testing teleop it
  // doesn't have undefined behavior and potentially crash.
  frc2::Command *m_autonomousCommand = nullptr;

  RobotContainer m_container;
  STATE m_state;

  NLMOTOR_CHARACTERIZATION m_CrtzL1;
  NLMOTOR_CHARACTERIZATION m_CrtzL2;
  NLMOTOR_CHARACTERIZATION m_CrtzR1;
  NLMOTOR_CHARACTERIZATION m_CrtzR2;

  NLDRIVETRAINSPECS m_DriveTrainSpecs;

  Nu32 m_flags;
  Nf32 m_dsLeftWheel;
  Nf32 m_dsRightWheel;

  NLROBOTPOSE m_estimatedPose;
  NLRAMSETEFOLLOWER m_ramsete;
  NLTRAJECTORY_PACK m_TrajectoryStatePack;
  NLTRAJECTORY_STATE m_currrentState;
};
