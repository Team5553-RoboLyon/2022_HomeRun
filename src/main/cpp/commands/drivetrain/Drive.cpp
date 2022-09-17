// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/drivetrain/Drive.h"

#include "lib/Utils.h"

#define TRACKWIDTH 0.61f
#define HALF_TRACKWIDTH (TRACKWIDTH / 2.0f)

#define AMAX 5.1 // Acceleration Max  au PIF .. à définir aux encodeurs
#define VMAX 3.4 // vitesse Max  théorique (3,395472 sur JVN-DT) .. à vérifier aux encodeurs
#define WMAX                     \
  (((2.0 * VMAX) / TRACKWIDTH) / \
   1.7) // vitesse angulaire Max theorique	.. à modifier avec Garice

#define NABS(a) (((a) < 0) ? -(a) : (a))     // VALEUR ABSOLUE
#define NMAX(a, b) (((a) > (b)) ? (a) : (b)) // Max
#define NMIN(a, b) (((a) < (b)) ? (a) : (b)) // Min

Drive::Drive(std::function<double()> forward, std::function<double()> turn, Drivetrain *pdrivetrain)
    : m_Forward(forward), m_Turn(turn), m_pDrivetrain(pdrivetrain)
{
  AddRequirements(m_pDrivetrain);
}

void Drive::Initialize()
{
  // if (m_pDrivetrain->GetPTOState() != Drivetrain::PTOState::Driving)
  // {
  //   this->Cancel();
  // }
}

void Drive::Execute()
{
  if (m_pDrivetrain->GetEnabled())
  {
    // if (m_pDrivetrain->GetPosition())
    // {
    double forward = utils::Deadband(m_Forward());
    double turn = utils::Deadband(m_Turn());
    forward *= 1.0;
    turn *= 0.7;

    /*
    double c = 0.35 * (turn * 5.0 * (std::abs(turn) + 1) / (std::abs(forward) + 1));
    if (turn < 0.0) {
      m_pDrivetrain->Drive(forward * ((c + 1) / (1 - c)), forward);
    } else {
      m_pDrivetrain->Drive(forward, forward * ((1 - c) / (c + 1)));
    }*/

    double v = forward * VMAX;
    double w = turn * WMAX;

    // w = m_pDrivetrain->CalculateTurn(forward, w);

    double left_wheel = v + (w * HALF_TRACKWIDTH);
    double right_wheel = v - (w * HALF_TRACKWIDTH);

    double k;
    k = 1.0 / (NMAX(VMAX, NMAX(NABS(left_wheel), NABS(right_wheel))));
    left_wheel *= k;
    right_wheel *= k;

    m_pDrivetrain->Drive(right_wheel, left_wheel);
    // }
    // else
    // {
    //   double forward = utils::Deadband(m_Forward());
    //   double turn = utils::Deadband(m_Turn());
    //   m_pDrivetrain->Drive(forward, turn, 0.0, Drivetrain::PTOState::Driving);
    // }
  }
}

void Drive::End(bool interrupted) {}

bool Drive::IsFinished()
{
  return false;
}
