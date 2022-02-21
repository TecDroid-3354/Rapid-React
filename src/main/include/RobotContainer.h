/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/Command.h>

#include "subsystems/Drivetrain.h"
#include "subsystems/Auto.h"
#include "subsystems/Shooter.h"
#include "subsystems/Intake.h"
#include "subsystems/Turret.h"

using namespace frc2;
using namespace frc;

/*Clase que contiene los subsistemas del robot y controla funciones generales.*/
class RobotContainer
{
public:
	RobotContainer();

	Command *GetAutonomousCommand();

	/*Mover chasis*/
	void Drive();

	// Resetear robot
	void Reset();

	// Ejecuta el autónomo
	void AutonomousPeriodic();

	// Resetea el autónomo
	void AutonomousInit();

	/*Temporizador*/
	frc::Timer timer;

private:
	// Objeto del chasis
	Drivetrain chasis;

	// Objeto del autónomo que recibe el chasis
	Auto auton{chasis};

	Turret turret;

	Shooter shooter;

	Intake intake;

	XboxController control{0};


	/*Función para configurar las acciones relacionadas a cada botón*/
	void ConfigureButtonBindings();
};
