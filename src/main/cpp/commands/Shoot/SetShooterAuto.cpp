// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Shoot/SetShooterAuto.h"

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/stable/docs/software/commandbased/convenience-features.html
SetShooterAuto::SetShooterAuto(Conveyor *pconveyor, Shooter *shooter, Hood *hood, Turret *turret, Camera *camera)
{
  m_pConveyor = pconveyor;
  m_shooter = shooter;
  m_hood = hood;
  m_turret = turret;
  m_camera = camera;

  AddRequirements(m_shooter);
  AddRequirements(m_hood);
  AddRequirements(m_turret);
  AddRequirements(m_camera);
  AddRequirements(m_pConveyor);
}
void SetShooterAuto::End(bool interrupted)
{
  m_camera->DisableLED();
  m_shooter->SetSpeed(0.0);
  m_turret->Enable();
  m_turret->SetSetpoint(0.0);
  m_hood->SetSetpoint(0.0);
  m_pConveyor->StopAllMotors();
}
void SetShooterAuto::Initialize()
{
  m_camera->EnableLED();
  m_shooter->m_countShooter = 0.0;
  ChainballInit2(m_pConveyor, m_shooter);
}

void SetShooterAuto::Execute()
{

  if (m_camera->HasTarget())
  {
    m_shooter->m_countShooter += 1;
    double pitch = m_horizontalMedian.Calculate(m_camera->GetPitch());
    int *index = getNearestElementId(std::clamp(pitch, shooterDataTable[0][0], shooterDataTable[SHOOTER_TABLE_SIZE - 1][0]));

    double t = (pitch - shooterDataTable[*index][0]) / (shooterDataTable[*(index + 1)][0] - shooterDataTable[*index][0]);
    // std::cout << "t : " << t << std::endl;
    // std::cout << "pitch : " << LERP(shooterDataTable[*index][0], shooterDataTable[*(index + 1)][0], t) << std::endl;
    // std::cout << "angle calculated : " << LERP(shooterDataTable[*index][1], shooterDataTable[*(index + 1)][1], t) << std::endl;
    // std::cout << "speed calculated : " << LERP(shooterDataTable[*index][2], shooterDataTable[*(index + 1)][2], t) << std::endl;
    m_hood->SetSetpoint(LERP(shooterDataTable[*index][1], shooterDataTable[*(index + 1)][1], t));
    m_shooter->SetSpeed(LERP(shooterDataTable[*index][2], shooterDataTable[*(index + 1)][2], t));
    m_turret->SetSetpoint(m_turret->GetMeasurement() + (m_camera->GetHorizontalError() * 0.5));
    if (m_camera->HasTarget() && (std::abs(m_turret->GetError()) < 2 && std::abs(m_hood->GetError()) < 2 && m_shooter->m_countShooter >= 10))
    {
      ChainballRun2(m_pConveyor, m_shooter);
    }
  }
}
bool SetShooterAuto::IsFinished()
{
  // if (frc::DriverStation::IsAutonomous())
  // {
  //   return (m_shooter->m_countShooter > AUTO_SHOOTING_BALL_TIME);
  // }
  // else
  // {
  return false;
  // }
}

int *SetShooterAuto::getNearestElementId(double target)
{
  // fonction de recherche dichotomique de l"élément le plus proche
  static int r[2];
  int n = sizeof(shooterDataTable) / sizeof(shooterDataTable[0]);
  if (target <= shooterDataTable[0][0])
  {
    r[0] = 0;
    r[1] = 1;
    return r;
  }
  if (target >= shooterDataTable[n - 1][0])
  {
    r[0] = n - 2;
    r[1] = n - 1;
    return r;
  }
  int left = 0, right = n, mid = 0;
  while (left < right)
  {
    mid = (left + right) / 2;
    if (shooterDataTable[mid][0] == target)
    {
      r[0] = mid;
      r[1] = mid + 1;
      return r;
    }
    if (target < shooterDataTable[mid][0])
    {
      if (mid > 0 && target > shooterDataTable[mid - 1][0])
      {
        r[0] = mid - 1;
        r[1] = mid;
        return r;
      }
      right = mid;
    }
    else
    {
      if (mid < n - 1 && target < shooterDataTable[mid + 1][0])
      {
        r[0] = mid;
        r[1] = mid + 1;
        return r;
      }
      left = mid + 1;
    }
  }
  r[0] = mid;
  r[1] = mid + 1;
  return r;
}