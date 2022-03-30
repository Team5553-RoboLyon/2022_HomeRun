// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Shoot/SetShooterAuto.h"

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/stable/docs/software/commandbased/convenience-features.html
SetShooterAuto::SetShooterAuto(Shooter *shooter)
{
  AddRequirements(shooter);
  AddRequirements(&shooter->m_hood);

  m_shooter = shooter;
}

void SetShooterAuto::Initialize()
{
  double distance = 1.4f;
  int index = getNearestElementId(distance);
  std::cout << "nearest : " << index << std::endl;
  if (shooterDataTable[index][0] <= distance)
  {
    double t = (distance - shooterDataTable[index][0]) / (shooterDataTable[index + 1][0] - shooterDataTable[index][0]);
    std::cout << "t : " << t << std::endl;
    std::cout << "distance calculated : " << LERP(shooterDataTable[index][0], shooterDataTable[index + 1][0], t) << std::endl;
    std::cout << "angle calculated : " << LERP(shooterDataTable[index][1], shooterDataTable[index + 1][1], t) << std::endl;
    std::cout << "speed calculated : " << LERP(shooterDataTable[index][2], shooterDataTable[index + 1][2], t) << std::endl;
    m_shooter->m_hood.SetSetpoint(LERP(shooterDataTable[index][1], shooterDataTable[index + 1][1], t));
    m_shooter->SetSpeed(LERP(shooterDataTable[index][2], shooterDataTable[index + 1][2], t));
  }
  else
  {
    double t = (distance - shooterDataTable[index - 1][0]) / (shooterDataTable[index][0] - shooterDataTable[index][0]);
    std::cout << "t : " << t << std::endl;
    std::cout << "distance calculated : " << LERP(shooterDataTable[index - 1][0], shooterDataTable[index][0], t) << std::endl;
    std::cout << "angle calculated : " << LERP(shooterDataTable[index - 1][1], shooterDataTable[index][1], t) << std::endl;
    std::cout << "speed calculated : " << LERP(shooterDataTable[index - 1][2], shooterDataTable[index][2], t) << std::endl;
    m_shooter->m_hood.SetSetpoint(LERP(shooterDataTable[index - 1][1], shooterDataTable[index][1], t));
    m_shooter->SetSpeed(LERP(shooterDataTable[index - 1][2], shooterDataTable[index][2], t));
  }
}

int SetShooterAuto::getNearest(int x, int y, double target)
{
  if (target - shooterDataTable[x][0] >= shooterDataTable[y][0] - target)
    return y;
  else
    return x;
}
int SetShooterAuto::getNearestElementId(double target)
{
  // fonction de recherche dichotomique de l"élément le plus proche
  int n = sizeof(shooterDataTable) / sizeof(shooterDataTable[0]);
  if (target <= shooterDataTable[0][0])
    return 0;
  if (target >= shooterDataTable[n - 1][0])
    return n - 1;
  int left = 0, right = n, mid = 0;
  while (left < right)
  {
    mid = (left + right) / 2;
    if (shooterDataTable[mid][0] == target)
      return mid;
    if (target < shooterDataTable[mid][0])
    {
      if (mid > 0 && target > shooterDataTable[mid - 1][0])
        return getNearest(mid - 1, mid, target);
      right = mid;
    }
    else
    {
      if (mid < n - 1 && target < shooterDataTable[mid + 1][0])
        return getNearest(shooterDataTable[mid][0], shooterDataTable[mid + 1][0], target);
      left = mid + 1;
    }
  }
  return mid;
}
