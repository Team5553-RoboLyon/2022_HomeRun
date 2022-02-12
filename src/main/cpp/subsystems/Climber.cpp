#pragma once

#include "subsystems/Climber.h"

Climber::Climber() { m_NeoMotor.RestoreFactoryDefaults(); }

void Climber::ActiveMotor(double speed) { m_NeoMotor.Set(speed); }
