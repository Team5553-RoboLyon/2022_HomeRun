// ############ IDs ###############
// motors
#define SHOOTER_MOTOR_LEFT_CAN_ID 12
#define SHOOTER_MOTOR_RIGHT_CAN_ID 11
#define HOOD_MOTOR_CAN_ID 10
#define TURRET_MOTOR_CAN_ID 9
#define CONVEYOR_MOTOR_CAN_ID 7
#define FEEDER_MOTOR_CAN_ID 8
#define INTAKE_MOTOR_CAN_ID 6
#define DRIVETRAIN_MOTOR_RIGHT_CAN_ID 1
#define DRIVETRAIN_MOTOR_RIGHT_FOLLOWER_CAN_ID 2
#define DRIVETRAIN_MOTOR_LEFT_CAN_ID 3
#define DRIVETRAIN_MOTOR_LEFT_FOLLOWER_CAN_ID 4
// solenoids
#define INTAKE_SOLENOID_ID_FORWARD 0
#define INTAKE_SOLENOID_ID_REVERSE 1
#define DRIVETRAIN_SOLENOID_ID_FORWARD 7
#define DRIVETRAIN_SOLENOID_ID_REVERSE 6
// encoders
#define HOOD_ENCODER_ID_A 12
#define HOOD_ENCODER_ID_B 13
#define TURRET_ENCODER_ID_A 8
#define TURRET_ENCODER_ID_B 9
#define DRIVETRAIN_ENCODER_EXTERN_RIGHT_A_ID 0
#define DRIVETRAIN_ENCODER_EXTERN_RIGHT_B_ID 1
#define DRIVETRAIN_ENCODER_EXTERN_LEFT_A_ID 2
#define DRIVETRAIN_ENCODER_EXTERN_LEFT_B_ID 3
#define CLIMBER_ROTATING_ENCODER_ID_A 6
#define CLIMBER_ROTATING_ENCODER_ID_B 7
#define CLIMBER_LINEAR_ENCODER_ID_A 10
#define CLIMBER_LINEAR_ENCODER_ID_B 11

// ############ Speeds ###############
// unblock speeds
#define CONVEYOR_UNBLOCK_SPEED -0.5
#define FEEDER_UNBLOCK_SPEED -0.5
#define INTAKE_UNBLOCK_SPEED -0.5
#define SHOOTER_UNBLOCK_SPEED -0.5
// motor normal speeds
#define INTAKE_MOTOR_SPEED 0.7
#define FEEDER_MOTOR_SPEED 0.9
#define CONVEYOR_MOTOR_SPEED 0.8
// autonomous
#define DRIVETRAIN_AUTONOMOUS_SPEED -0.3

// ############ smart current limit ###############
#define DRIVETRAIN_CURRENT_LIMIT 45
#define HOOD_CURRENT_LIMIT 20
#define CONVEYOR_CURRENT_LIMIT 40

// ########### ramp ###############
#define CONVEYOR_RAMP_RATE 0.2
#define FEEDER_RAMP_RATE 0.2
#define INTAKE_RAMP_RATE 0.5
#define DRIVETRAIN_RAMPRATE 0.6

// ########### voltage compensation ###############

#define SHOOTER_VOLTAGE_COMPENSATION 11.0
#define CONVEYOR_VOLTAGE_COMPENSATION 10
#define FEEDER_VOLTAGE_COMPENSATION 10
#define INTAKE_VOLTAGE_COMPENSATION 10

// ########### PID ###############
// turret
#define TURRET_PID_P 0.04
#define TURRET_PID_I 0.02
#define TURRET_PID_D 0.002
// hood
#define HOOD_PID_P 0.02
#define HOOD_PID_I 0.008
#define HOOD_PID_D 0.0
#define HOOD_PID_INTEGRATOR_RANGE 5
// climber
#define CLIMBER_PID_P 0.1
#define CLIMBER_PID_I 0.0
#define CLIMBER_PID_D 0.0

// ########### LES TRUCS D'ALEXANDRER LE FUHRER ###############
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
#define TURRET true
#define CAMERA true
#define GEARBOX true
#define HOOD true

// ######### Joystick IDs #########
#define DRIVER_JOYSTICK_RIGHT_ID 0
#define DRIVER_JOYSTICK_LEFT_ID 1

// ########### conversion factors ###############
#define CLIMBER_ENCODER_CONVERSION_FACTOR 1 / 56.4
#define HOOD_ENCODER_CONVERSION_FACTOR 58.0 / 8604.0

// ########### TESTS ###############
#define DRIVETRAIN_TEST_SPEED 0.1
#define DRIVETRAIN_TEST_DURATION 0.5