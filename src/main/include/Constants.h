#define SHOOTER_VOLTAGE_COMPENSATION 11.0

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

#define INTAKE_SOLENOID_ID_FORWARD 0
#define INTAKE_SOLENOID_ID_REVERSE 1

#define HOOD_ENCODER_ID_A 12
#define HOOD_ENCODER_ID_B 13
#define TURRET_ENCODER_ID_A 8
#define TURRET_ENCODER_ID_B 9

#define INTAKE_MOTOR_SPEED 0.7
#define CONVEYOR_MOTOR_SPEED 0.7
#define FEEDER_MOTOR_SPEED 0.9

// Hood PID
#define HOOD_PID_P 0.02  // 0.035
#define HOOD_PID_I 0.008 // 0.008
#define HOOD_PID_D 0.0   // 0.004
#define HOOD_ENCODER_CONVERSION_FACTOR 58.0 / 8604.0
#define HOOD_PID_TOLERANCE 0
#define HOOD_PID_INTEGRATOR_RANGE 5
#define HOOD_INIT_MAX_SPEED 0.1
#define HOOD_MAX_SPEED 0.3

// ######### Digital input IDs #########
#define HOOD_SENSOR_HALL_ID 17
#define TURRET_SENSOR_HALL_ID 14
#define CLIMBER_SENSOR_HALL_ID 18
#define CLIMBER_ROTATING_SENSOR_HALL_FORWARD_ID 15
#define CLIMBER_ROTATING_SENSOR_HALL_BACKWARD_ID 16

// Hood
#define HOOD_MOTOR_ID 10

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

#define USE_CAMERA_TO_MOVE_TURRET false