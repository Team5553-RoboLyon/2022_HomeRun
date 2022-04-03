// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#define SHUFFLEBOARD_DEBUG true
#define LOG_IN_FILE false

#define CONFIG_FILE_PATH "/home/admin/config.json"

#define ROBOT_LOOP_TIME 0.02

#define SMART_LIMIT_CURRENT_NEO 40
#define SMART_LIMIT_CURRENT_NEO_BASE 45

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
#define INTAKE_SOLENOID_1_ID 5 // 3
#define INTAKE_SOLENOID_2_ID 4 // 2

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
#define HOOD_PID_P 0.01 // 0.035
#define HOOD_PID_I 0    // 0.008
#define HOOD_PID_D 0    // 0.004
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
#define DRIVETRAIN_ENCODER_EXTERN_RIGHT_A_ID 0
#define DRIVETRAIN_ENCODER_EXTERN_RIGHT_B_ID 1
#define DRIVETRAIN_ENCODER_EXTERN_LEFT_A_ID 2
#define DRIVETRAIN_ENCODER_EXTERN_LEFT_B_ID 3
#define CLIMBER_ROTATING_ENCODER_ID_A 6
#define CLIMBER_ROTATING_ENCODER_ID_B 7
#define TURRET_ENCODER_A_ID 8
#define TURRET_ENCODER_B_ID 9
#define CLIMBER_LINEAR_ENCODER_ID_A 10
#define CLIMBER_LINEAR_ENCODER_ID_B 11
#define HOOD_ENCODER_A_ID 12
#define HOOD_ENCODER_B_ID 13

// ######### Digital input IDs #########
#define HOOD_SENSOR_HALL_ID 17
#define TURRET_SENSOR_HALL_ID 14
#define CLIMBER_SENSOR_HALL_ID 18
#define CLIMBER_ROTATING_SENSOR_HALL_FORWARD_ID 15
#define CLIMBER_ROTATING_SENSOR_HALL_BACKWARD_ID 16
