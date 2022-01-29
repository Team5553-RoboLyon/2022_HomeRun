// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <wpi/json.h>

class JsonConfig
{
public:
  JsonConfig();
  static void LoadConfig(const std::string fileName);
  static bool isConfigLoaded();
  static void UnloadConfig();
  static wpi::json GetJson();

private:
  static wpi::json Config;
};
