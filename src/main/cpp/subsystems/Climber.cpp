// #include "subsystems/Climber.h"

// Climber::Climber(Gearbox *gearbox)
// {
//     m_gearbox = gearbox;
// }

// void Climber::Periodic()
// {
//     double outputClimber = m_pidcontroller.Calculate(units::degree_t{GetMeasurement()}, units::degree_t{m_setPoint});
//     UseOutput(outputClimber, GetSetpoint());
//     spdlog::trace("Drivetrain::Periodic()");
// }
// void Climber::Stop()
// {
//     spdlog::trace("Drivetrain::Stop()");
//     m_gearbox->StopEveryOne(Gearbox::PTOState::Climbing);
// }
// void Climber::MoveRotatingArms(double speed) {}
// void Climber::MoveClimber(double speed) {}

// void Climber::ResetEncoder()
// {
//     spdlog::trace("Drivetrain::ResetEncoderClimber()");
//     m_encoderClimber.Reset();
// }
// void Climber::Enable()
// {
//     m_gearbox->SetPTOState(Gearbox::PTOState::Climbing);
//     m_state_Climber = Climber::state_Climber::enableClimber;
//     m_state_RotatingArms = Climber::state_RotatingArms::enableRotatingArms;
// }
// void Climber::Disable()
// {
//     m_gearbox->SetPTOState(Gearbox::PTOState::Driving);
//     m_state_Climber = Climber::state_Climber::disableClimber;
//     m_state_RotatingArms = Climber::state_RotatingArms::disableRotatingArms;
// }

// double Climber::GetMeasurement()
// {
//     spdlog::trace("Drivetrain::GetMeasurementClimber()");
//     return m_encoderClimber.GetDistance();
// }
// void Climber::UseOutput(double output, double setpoint)
// {

//     spdlog::trace("Drivetrain::UseOutput()");
//     if (m_gearbox->GetPTOState() == Gearbox::PTOState::Climbing)
//     {
//         switch (m_state_Climber)
//         {
//         case Climber::state_Climber::initClimber:
//             if (m_HallSensor.MagnetDetected())
//             {
//                 m_state_Climber = Climber::state_Climber::disableClimber;
//                 ResetEncoder();
//             }
//             else
//             {
//                 if (!m_HallSensor.ShouldIStop(GetMeasurement(), wpi::sgn(output)))
//                 {
//                     m_gearbox->SetRight(output, Gearbox::PTOState::Climbing);
//                 }
//                 else
//                 {
//                     m_gearbox->SetRight(0.0, Gearbox::PTOState::Climbing);
//                 }
//             }
//             break;

//         case Climber::state_Climber::enableClimber:
//             if (m_HallSensor.ShouldIStop(GetMeasurement(), wpi::sgn(output)))
//             {
//                 m_gearbox->SetRight(output, Gearbox::PTOState::Climbing);
//             }
//             else
//             {
//                 m_gearbox->SetRight(0.0, Gearbox::PTOState::Climbing);
//             }
//             break;
//         case Climber::state_Climber::disableClimber:
//             m_gearbox->SetRight(0.0, Gearbox::PTOState::Climbing);
//             break;
//         default:
//             break;
//         }

//         switch (m_state_RotatingArms)
//         {
//         case Climber::state_RotatingArms::initRotatingArms:
//             /* code */
//             break;
//         case Climber::state_RotatingArms::enableRotatingArms:
//             if (m_HallSensor.ShouldIStop(GetMeasurement(), wpi::sgn(0.1)))
//             {
//                 m_gearbox->SetLeft(0.1, Gearbox::PTOState::Climbing);
//             }
//             else
//             {
//                 m_gearbox->SetLeft(0.0, Gearbox::PTOState::Climbing);
//             }
//             break;
//         case Climber::state_RotatingArms::disableRotatingArms:
//             m_gearbox->SetLeft(0.0, Gearbox::PTOState::Climbing);
//             break;
//         default:
//             break;
//         }
//     }
// }
// void Climber::SetSetpoint(double setpoint)
// {
//     spdlog::trace("Drivetrain::SetSetpointClimber(double setpointClimber)");
//     m_setPoint = setpoint;
// }
// double Climber::GetSetpoint()
// {
//     spdlog::trace("Drivetrain::GetSetpointClimber()");
//     return m_setPoint;
// }