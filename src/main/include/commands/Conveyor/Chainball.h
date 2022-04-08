// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once
#include "subsystems/Conveyor.h"
#include "subsystems/Shooter.h"
#include <spdlog/spdlog.h>

void ChainballInit(Conveyor *m_pConveyor, Shooter *m_pShooter);
void ChainballRun(Conveyor *m_pConveyor, Shooter *m_pShooter);

void ChainballInit2(Conveyor *m_pConveyor, Shooter *m_pShooter);
void ChainballRun2(Conveyor *m_pConveyor, Shooter *m_pShooter);

enum ChainBallState
{
    Disable,
    Disabled,
    Disangage,
    Shoot0,
    Shoot1,
    Shoot2_Pause,
    Shoot3
};
