#include <hal/HAL.h>
#include <spdlog/spdlog.h>
#include "spdlog/fmt/ostr.h" // must be included
#include "spdlog/sinks/stdout_sinks.h"

#include "gtest/gtest.h"
#include <frc/RobotBase.h>

int main(int argc, char **argv)
{
    auto logger = spdlog::stdout_logger_mt("LOGGER");
    spdlog::set_default_logger(logger);

    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%n] [%^%l%$] %v");
    spdlog::set_level(spdlog::level::trace);
    SPDLOG_TRACE("TESTS INITIALISATION");

    HAL_Initialize(500, 0);
    ::testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}