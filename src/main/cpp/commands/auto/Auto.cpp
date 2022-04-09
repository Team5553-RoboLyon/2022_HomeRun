// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/auto/Auto.h"

/*      TODOLIST
        - check le temps de shoot
        - check la vitesse pour ce retourner
        - check le temps pour avancer sur la balle

*/

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/stable/docs/software/commandbased/convenience-features.html
Auto::Auto(Drivetrain *drivetrain, Shooter *shooter, Turret *turret,
           Hood *hood, Conveyor *conveyor, Intake *intake, Camera *camera,
           Gearbox *gearbox, frc::AnalogGyro *gyro)
{
  AddCommands(CompleteInit(camera, hood, gearbox, drivetrain, turret),
              AutoMoovBackward(drivetrain),
              SetShooterAuto(conveyor, shooter, hood, turret, camera),
              frc2::InstantCommand(
                  [intake]
                  { intake->Open(); },
                  {intake}),
              frc2::ParallelRaceGroup(
                  AutoMoovToBall(gearbox, gyro),
                  ActiveIntakeMotor(intake)),
              frc2::InstantCommand(
                  [intake]
                  { intake->Close(); },
                  {intake}),
              AutoBackToShoot(drivetrain, gyro),
              SetShooterAuto(conveyor, shooter, hood, turret, camera));
}
