// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

void Robot::RobotInit()
{

#if LOG_IN_FILE
  std::vector<spdlog::sink_ptr> sinks;
  sinks.push_back(std::make_shared<spdlog::sinks::stdout_sink_st>());
  // Get timestamp
  auto now = std::chrono::system_clock::now();
  auto in_time_t = std::chrono::system_clock::to_time_t(now);
  std::stringstream ss;
  ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d_%H-%M-%S");
  std::string time_stamp = ss.str();
  std::string log_file_name = "/home/lvuser/logs/" + time_stamp + ".log";

  sinks.push_back(std::make_shared<spdlog::sinks::basic_file_sink_st>(log_file_name));
  std::shared_ptr<spdlog::logger> logger = std::make_shared<spdlog::logger>("LOGGER", begin(sinks), end(sinks));
#else
  std::shared_ptr<spdlog::logger> logger = spdlog::stdout_logger_mt("LOGGER");
#endif
  spdlog::set_default_logger(logger);

  spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%n] [%^%l%$] %v");
  spdlog::set_level(spdlog::level::err);

  // JsonConfig::LoadConfig(CONFIG_FILE_PATH);
  spdlog::trace("RobotInit()");

  NErrorIf(!m_pVirtualRobot, NERROR_NULL_POINTER); // A virtual Robot has to be defined !!!
  // a reprendre :

  // NLCHARACTERIZATION_TABLE characterization_table(4);
  // characterization_table.load("characterization_MultiVarLinearRegression.txt");
  // characterization_table.get(&m_CrtzL1, "L1", NFALSE);
  // characterization_table.get(&m_CrtzL2, "L2", NFALSE);
  // characterization_table.get(&m_CrtzR1, "R1", NFALSE);
  // characterization_table.get(&m_CrtzR2, "R2", NFALSE);

  // // Read TrajectoryFollowing external data:
  // // En mode simulation ces donn�es sont 'lues' ( copi�es en fait ) depuis le path workbench courant.
  // // En mode "r�el" elles sont effectivement pr�sentes sous forme de fichiers charg�s � l'initialisation.
  // Nu32 read_error_count = 0;

  // FILE *file;

  // read_error_count += m_DriveTrainSpecs.read(file) ? 0 : 1;
  // read_error_count += m_ramsete.read(file) ? 0 : 1;
  // read_error_count += m_TrajectoryStatePack.read(file) ? 0 : 1;
  // read_error_count += m_TrajectoryStatePack.m_keyStatesArray.Size ? 0 : 1;

  // m_currrentState.null();
  // // read_error_count += m_TrajectoryStateSPack.read(pwb) ? 0:1;
  // // m_currrentSState.null();

  // if (read_error_count)
  //   m_state = Robot::STATE::PATH_ERROR;
  // else
  //   m_state = Robot::STATE::PATH_FOLLOWING;

  // m_dsLeftWheel = 0.0f;
  // m_dsRightWheel = 0.0f;
  // m_estimatedPose.reset();
}

void Robot::RobotPeriodic()
{
  spdlog::trace("RobotPeriodic()");
  frc2::CommandScheduler::GetInstance().Run();
}

void Robot::DisabledInit()
{
  spdlog::trace("DisabledInit()");
}

void Robot::DisabledPeriodic()
{
  spdlog::trace("DisabledPeriodic()");
}

void Robot::AutonomousInit()
{
  spdlog::trace("AutonomousInit()");
  m_container.GetAutonomousCommand()->Schedule();
}

void Robot::AutonomousPeriodic()
{

  // Nf32 dt = ROBOT_LOOP_TIME;
  // spdlog::trace("AutonomousPeriodic()");
  // Nf32 l, r, dl, dr;
  // NLRAMSETEOUTPUT output;

  // switch (m_state)
  // {
  // case Robot::STATE::PATH_ERROR:
  // {
  //   break;
  // }
  // case Robot::STATE::PATH_FOLLOWING:
  // {
  //   // *****************************************************    'THE' METHOD(e)
  //   // A) Feed back:
  //   // avec les encodeurs on estime la position du robot:
  //   //			l = distance parcourue par la roue gauche depuis le dernier reset encodeur.
  //   //			r = distance parcourue par la roue droite depuis le dernier reset encodeur.
  //   //
  //   //			dl et dr = distances parcourues par les roues gauche et droite depuis le dernier call.
  //   //			(note dl/dt = vitesse roue gauche et dr/dt = vitesse roue droite  )
  //   //

  //   double encoderValues[2];

  //   m_container.GetDrivetrainEncoderValues(encoderValues);

  //   l = (encoderValues[0] / 8192.0f) * NF32_2PI * m_DriveTrainSpecs.m_wheelRadius;
  //   r = (encoderValues[1] / 8192.0f) * NF32_2PI * m_DriveTrainSpecs.m_wheelRadius;
  //   dl = l - m_dsLeftWheel;
  //   dr = r - m_dsRightWheel;
  //   m_dsLeftWheel = l;
  //   m_dsRightWheel = r;
  //   // forward:
  //   m_estimatedPose.odometryUpdate(&m_DriveTrainSpecs, dl, dr, (m_gyro.GetAngle() * NF64_2PI / 360.0));

  //   // backward:
  //   // m_estimatedPose.odometryUpdate(&m_DriveTrainSpecs, -dr, -dl, m_gyro.get());

  //   // B) Feed forward : State ( full )
  //   m_currrentState.m_kin.m_t += dt;
  //   m_TrajectoryStatePack.getState(&m_currrentState, m_currrentState.m_kin.m_t);

  //   // C) Ramsete:
  //   m_ramsete.update(&output, &m_DriveTrainSpecs, &m_currrentState, &m_estimatedPose);

  //   // forward:
  //   Nf32 l1 = m_CrtzL1.getVoltage(output.m_leftVelocity, output.m_leftAcceleration);
  //   Nf32 l2 = m_CrtzL2.getVoltage(output.m_leftVelocity, output.m_leftAcceleration);
  //   Nf32 r1 = m_CrtzR1.getVoltage(output.m_rightVelocity, output.m_rightAcceleration);
  //   Nf32 r2 = m_CrtzR2.getVoltage(output.m_rightVelocity, output.m_rightAcceleration);

  //   m_container.SetMotorVoltagesWhenAutonomous(units::volt_t{l1}, units::volt_t{l2}, units::volt_t{r1}, units::volt_t{r2});

  //   /*
  //   // backward:
  //   m_moteurR1.SetVoltage(m_CrtzL1.getVoltage(-output.m_leftVelocity, -output.m_leftAcceleration));
  //   m_moteurR2.SetVoltage(m_CrtzL2.getVoltage(-output.m_leftVelocity, -output.m_leftAcceleration));

  //   m_moteurL1.SetVoltage(m_CrtzR1.getVoltage(-output.m_rightVelocity,-output.m_rightAcceleration));
  //   m_moteurL2.SetVoltage(m_CrtzR2.getVoltage(-output.m_rightVelocity,-output.m_rightAcceleration));
  //   */
  //   break;
  // }
  // case Robot::STATE::PATH_END:
  // {
  //   break;
  // }
  // default:
  // {
  //   NErrorIf(1, NERROR_UNAUTHORIZED_CASE);
  //   break;
  // }
  // }
}

void Robot::TeleopInit()
{
  spdlog::trace("TeleopInit()");
  m_container.InitTeleopPeriod();
}

void Robot::TeleopPeriodic()
{
  spdlog::trace("TeleopPeriodic()");
}

void Robot::TestInit()
{
  spdlog::trace("TestInit()");
  // m_container.StartTests();
}

void Robot::TestPeriodic()
{
  spdlog::trace("TestPeriodic()");
}

#ifndef RUNNING_FRC_TESTS
int main()
{
  return frc::StartRobot<Robot>();
}
#endif
