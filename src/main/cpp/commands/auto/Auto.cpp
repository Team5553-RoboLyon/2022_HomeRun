// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/auto/Auto.h"

/*      TODOLIST
        - ON REGARDE SI LE GYRO IL MARCHE !!!!
        - check le temps de shoot
        - check la vitesse pour ce retourner
        - check le temps pour avancer sur la balle
        -check le temps pour reculer au niveau de la balle (UN POIL COURT)
        - checker le -90 ou 90 degré


        - check vitesse shoot pid turret

        ps: check les valeur dans le shuffleboard pour le shooter si jamais

*/

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/stable/docs/software/commandbased/convenience-features.html
Auto::Auto(Drivetrain *drivetrain, Shooter *shooter, Turret *turret,
           Hood *hood, Conveyor *conveyor, Intake *intake, Camera *camera,
           Gearbox *gearbox, frc::AnalogGyro *gyro)
{
    AddCommands(CompleteInit(camera, hood, gearbox, drivetrain, turret, intake),
                AutoMoovBackward(drivetrain),
                SetShooterAuto(conveyor, shooter, hood, turret, camera),
                AutoTurn(drivetrain, gyro, -90.0),
                frc2::InstantCommand(
                    [intake]
                    { intake->Open(); },
                    {intake}),
                frc2::ParallelRaceGroup(
                    AutoMoovToBall(drivetrain),
                    ActiveIntakeMotor(intake),
                    IntakeConveyorMode(conveyor)),
                frc2::InstantCommand(
                    [intake]
                    { intake->Close(); },
                    {intake}),
                AutoTurn(drivetrain, gyro, 0.0),
                // AutoBackToShoot(drivetrain, gyro),
                SetShooterAuto(conveyor, shooter, hood, turret, camera));
}
