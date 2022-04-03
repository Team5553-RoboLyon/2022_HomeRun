#include <frc2/command/SubsystemBase.h>

#include "subsystems/Gearbox.h"

class Climber : public frc2::SubsystemBase
{

public:
    Climber(Gearbox *gearbox);
    void Periodic();
    void Stop();
    void MoveRotatingArms(double speed);
    void MoveClimber(double speed);

    void ResetEncoder();
    void Enable();
    void Disable();

    double GetMeasurement();
    void UseOutput(double output, double setpoint);
    void SetSetpoint(double setpoint);
    double GetSetpoint();

private:
    Gearbox *m_gearbox;
    enum state_Climber
    {
        initClimber,
        goTo0Climber,
        enableClimber,
        disableClimber,
    };
    enum state_RotatingArms
    {
        initRotatingArms,
        goTo0RotatingArms,
        enableRotatingArms,
        disableRotatingArms,
    };
    state_Climber m_state_Climber = Climber::state_Climber::initClimber;
    state_RotatingArms m_state_RotatingArms = Climber::state_RotatingArms::initRotatingArms;

    frc::ProfiledPIDController<units::degree> m_pidcontroller{
        CLIMBER_PID_P, CLIMBER_PID_I, CLIMBER_PID_D,
        frc::TrapezoidProfile<units::degree>::Constraints{5_deg / 1_s, 10_deg / (1_s * 1_s)}};
    frc::Encoder m_encoderClimber{CLIMBER_LINEAR_ENCODER_ID_A, CLIMBER_LINEAR_ENCODER_ID_B};
    HallSecurity m_HallSensor{CLIMBER_SENSOR_HALL_ID};

    double m_setPoint = 0.0;

    frc::Encoder m_encoderRotatingArms{CLIMBER_ROTATING_ENCODER_ID_A, CLIMBER_ROTATING_ENCODER_ID_B};
    frc::DigitalInput m_HallSensorRotatingArmRight{CLIMBER_ROTATING_SENSOR_HALL_FORWARD_ID};
    frc::DigitalInput m_HallSensorRotatingArmLeft{CLIMBER_ROTATING_SENSOR_HALL_BACKWARD_ID};
};
