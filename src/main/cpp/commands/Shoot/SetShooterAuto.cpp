// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Shoot/SetShooterAuto.h"

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/stable/docs/software/commandbased/convenience-features.html
SetShooterAuto::SetShooterAuto(Shooter *shooter, Hood *hood)
    : m_shooter(shooter), m_hood(hood)
{
  AddRequirements(m_shooter);
  AddRequirements(m_hood);
}

void SetShooterAuto::Initialize()
{
  double distance = nt::NetworkTableInstance::GetDefault().GetTable("")->GetEntry("").GetDouble(0.0);
  int *index = getNearestElementId(distance);
  std::cout << "nearest : " << *(index) << " " << *(index + 1) << std::endl;

  double t = (distance - shooterDataTable[*(index)][0]) / (shooterDataTable[*(index + 1)][0] - shooterDataTable[*(index)][0]);
  std::cout << "t : " << t << std::endl;
  std::cout << "distance calculated : " << LERP(shooterDataTable[*(index)][0], shooterDataTable[*(index + 1)][0], t) << std::endl;
  std::cout << "angle calculated : " << LERP(shooterDataTable[*(index)][1], shooterDataTable[*(index + 1)][1], t) << std::endl;
  std::cout << "speed calculated : " << LERP(shooterDataTable[*(index)][2], shooterDataTable[*(index + 1)][2], t) << std::endl;
  m_hood->SetSetpoint(LERP(shooterDataTable[*(index)][1], shooterDataTable[*(index + 1)][1], t));
  m_shooter->SetVelocity(LERP(shooterDataTable[*(index)][2], shooterDataTable[*(index + 1)][2], t));
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
    r[0] = n - 1;
    r[1] = n;
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