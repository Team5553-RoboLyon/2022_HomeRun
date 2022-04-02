// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#define SHUFFLEBOARD_DEBUG true
#define LOG_IN_FILE false

#define CONFIG_FILE_PATH "/home/admin/config.json"

#define ROBOT_LOOP_TIME 0.02

// ######### SUBSYSTEM ACTIVATION #########

#define DRIVETRAIN true
#define CLIMBER true
#define INTAKE true
#define CONVEYOR true
#define FEEDER true
#define SHOOTER true
#define GEARBOX true
#define HOOD true

// ######### CAN IDs #########

// Drivetrain

#define DRIVETRAIN_NEO_MOTOR_RIGHT_ID 1
#define DRIVETRAIN_NEO_MOTOR_RIGHT_FOLLOWER_ID 2
#define DRIVETRAIN_NEO_MOTOR_LEFT_ID 3
#define DRIVETRAIN_NEO_MOTOR_LEFT_FOLLOWER_ID 4

// Turret
#define TURRET_MOTOR_ID 9

// Intake
#define INTAKE_MOTOR_ID 6
#define INTAKE_SOLENOID_1_ID 3 // 3
#define INTAKE_SOLENOID_2_ID 2 // 2

// Hood
#define HOOD_MOTOR_ID 10

// Shooter
#define SHOOTER_FALCON_MOTOR_ID 11
#define SHOOTER_FALCON_MOTOR_FOLLOWER_ID 12

// Conveyor
#define FEEDER_MOTOR_ID 8
#define CONVEYOR_MOTOR_ID 7

// ######### Joystick IDs #########

#define DRIVER_JOYSTICK_RIGHT_ID 0
#define DRIVER_JOYSTICK_LEFT_ID 1

// ######### speed #########

// Intake
#define INTAKE_MOTOR_SPEED 0.7

// Feeder
#define FEEDER_MOTOR_SPEED 0.9

// Conveyor
#define CONVEYOR_MOTOR_SPEED 0.65

// Climber PID
#define CLIMBER_PID_P 0.1
#define CLIMBER_PID_I 0.0
#define CLIMBER_PID_D 0.0
#define CLIMBER_ENCODER_CONVERSION_FACTOR 1 / 56.4

// Hood PID
#define HOOD_PID_P 0.035
#define HOOD_PID_I 0.008
#define HOOD_PID_D 0.0004
#define HOOD_ENCODER_CONVERSION_FACTOR -(58 / 4.2)
#define HOOD_PID_TOLERANCE 0
#define HOOD_PID_INTEGRATOR_RANGE 5
#define HOOD_INIT_MAX_SPEED 0.1
#define HOOD_MAX_SPEED 0.3

#define DRIVETRAIN_TEST_SPEED 0.1
#define DRIVETRAIN_TEST_DURATION 0.5

#define DRIVETRAIN_SOLENOID_ID_FORWARD 0
#define DRIVETRAIN_SOLENOID_ID_REVERSE 1

// ######### Encoder IDs #########
#define HOOD_ENCODER_ID 0

// ######### Digital input IDs #########
#define HOOD_SENSOR_HALL_ID 8

// ######### Camera #########

#define TARGET_HEIGHT 2.58
#define CAMERA_HEIGHT 0.772
#define CAMERA_PITCH 0.6457718