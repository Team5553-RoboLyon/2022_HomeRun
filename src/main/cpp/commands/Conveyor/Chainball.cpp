// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Conveyor/Chainball.h"

ChainBallState chainBallState = ChainBallState::Disable;

void ChainballInit(Conveyor *m_pConveyor, Shooter *m_pShooter)
{
    m_pConveyor->m_count = 0;
    m_pConveyor->m_state = Conveyor::state::_INIT;
    m_pShooter->m_countShooter = 0;
}

void ChainballRun(Conveyor *m_pConveyor, Shooter *m_pShooter)
{

    m_pShooter->m_countShooter += 1;
    if (m_pShooter->m_countShooter >= 25)
    {
        switch (m_pConveyor->m_state)
        {
        case Conveyor::state::_INIT:

            if (m_pConveyor->m_count >= 20)
            {
                m_pConveyor->m_state = Conveyor::state::_ENABLE;
                m_pConveyor->m_count = 0;
            }
            else
            {
                m_pConveyor->UnblockFeedingMotor();
                if (m_pConveyor->m_count <= 8)
                {
                    m_pConveyor->UnblockConveyorMotor();
                }
                else
                {
                    m_pConveyor->StopConveyorMotor();
                }
            }
            m_pConveyor->m_count += 1;

            break;
        case Conveyor::state::_ENABLE:
            if (m_pConveyor->m_count >= 10)
            {
                m_pConveyor->m_count = 0;
                m_pConveyor->m_state = Conveyor::state::_INIT;
            }
            else
            {
                m_pConveyor->m_count += 1;
                m_pConveyor->ActiveConveyorMotor();
                m_pConveyor->ActiveFeedingMotor();
            }

            break;

        default:
            break;
        }
    }
}

void ChainballInit2(Conveyor *m_pConveyor, Shooter *m_pShooter)
{
    m_pConveyor->m_count = 0;
    chainBallState = ChainBallState::Disangage;
}

void ChainballRun2(Conveyor *m_pConveyor, Shooter *m_pShooter)

{
    m_pConveyor->m_count += 1;
    switch (chainBallState)
    {
    case ChainBallState::Disangage:          // on fait desscendre les balles
        m_pConveyor->UnblockConveyorMotor(); // -10          -10*0.5=-5
        m_pConveyor->UnblockFeedingMotor();  // -10          -10*0.5=-5
        if (m_pConveyor->m_count >= 4)
        {
            m_pConveyor->m_count = 0;
            chainBallState = ChainBallState::Shoot0;
        }
        break;
    case ChainBallState::Shoot0:           // on prépare le feeder pour feeder les balles
        m_pConveyor->StopConveyorMotor();  // 0               0*0.5=0
        m_pConveyor->ActiveFeedingMotor(); // +10             10*0.9=9
        if (m_pConveyor->m_count >= 5)
        {
            m_pConveyor->m_count = 0;
            chainBallState = ChainBallState::Shoot1;
        }
        break;
    case ChainBallState::Shoot1:            // on envoie les balle
        m_pConveyor->ActiveConveyorMotor(); // +5             5*0.8=4
        m_pConveyor->ActiveFeedingMotor();  // +5             5*0.9=4.5
        if (m_pConveyor->m_count >= 8)
        {
            m_pConveyor->m_count = 0;
            chainBallState = ChainBallState::Shoot2_Pause;
        }
        break;

    case ChainBallState::Shoot2_Pause:     // petite pause entre deux balles
        m_pConveyor->StopConveyorMotor();  // 0              0*0.5=0
        m_pConveyor->ActiveFeedingMotor(); // 5              5*0.9=4.5
        if (m_pConveyor->m_count >= 12)
        {
            m_pConveyor->m_count = 0;
            chainBallState = ChainBallState::Disangage;
        }
        break;
    default:
        break;
    }
}