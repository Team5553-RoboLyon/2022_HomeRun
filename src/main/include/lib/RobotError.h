#pragma once

#include <iostream>
#include <exception>
#include <string>
#include <spdlog/spdlog.h>

namespace RobotError
{
    class RobotError : public std::exception
    {
    public:
        std::string message;
        RobotError(const std::string &msg) : message(msg)
        {
            spdlog::error(message);
        }
        const char *what() const noexcept override { return message.c_str(); }
    };

    class RobotCriticalError : public std::exception
    {
    public:
        std::string message;
        RobotCriticalError(const std::string &msg) : message(msg)
        {
            spdlog::error(message);
        }
        const char *what() const noexcept override { return message.c_str(); }
    };

    class RobotTestError : public std::exception
    {
    public:
        std::string message;
        RobotTestError(const std::string &testName, const std::string &msg) : message(msg)
        {
            spdlog::error("TEST [{}] ERROR : {}", testName, message);
        }
        const char *what() const noexcept override { return message.c_str(); }
    };
}