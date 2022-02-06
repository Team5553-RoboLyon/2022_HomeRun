// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.
#include <rev/CANSparkMax.h>
#include <frc/RobotBase.h>
#include <hal/SimDevice.h>

#include "Constants.h"

#pragma once

class CANSparkMaxWrapper : public rev::CANSparkMax
{
public:
  CANSparkMaxWrapper(int deviceId, rev::CANSparkMax::MotorType motorType);
  void Set(double speed);
  double Get();

private:
  bool m_isSimulated;
  hal::SimDouble m_setpoint;
  hal::SimDevice m_simDevice;
};
