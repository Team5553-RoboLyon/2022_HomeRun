// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "lib/JsonConfig.h"

JsonConfig::JsonConfig() = default;

wpi::json JsonConfig::Config = nullptr;

void JsonConfig::LoadConfig(const std::string fileName)
{
    // Verify that the file exists
    std::ifstream file(fileName);
    if (!file.good())
    {
        std::cout << "File " << fileName << " does not exist" << std::endl;
        return;
    }
    std::string fullFile = "";
    file.open(fileName, std::ios::in); //open a file to perform read operation using file object
    if (file.is_open())
    { //checking whether the file is open
        std::string tp;
        while (getline(file, tp))
        { //read data from file object and put it into string.
            fullFile = fullFile + tp;
            // std::cout << tp << "\n"; //print the data of the string
        }
        file.close(); //close the file object.
    }
    JsonConfig::Config = wpi::json::parse(fullFile);
}

void JsonConfig::UnloadConfig()
{
    JsonConfig::Config = nullptr;
}

wpi::json JsonConfig::GetConfig()
{
    return JsonConfig::Config;
}

bool JsonConfig::isConfigLoaded()
{
    return JsonConfig::Config != nullptr;
}
