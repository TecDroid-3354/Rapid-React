/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/Command.h>

#include "subsystems/Drivetrain.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include "frc/XboxController.h"
#include "frc2/command/button/Button.h"
#include "frc/Timer.h"
#include <rev/CANSparkMax.h>
#include "subsystems/Auto.h"
#include "subsystems/Intake.h"
#include "subsystems/Shooter.h"

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
	void RunAuto();

	// Resetea el autónomo
	void ResetAuto();

	/*Temporizador*/
	frc::Timer timer;

private:
	// Objeto del chasis
	Drivetrain chasis;

	// Objeto del autónomo que recibe el chasis
	Auto auton{chasis};

	/*Objeto de disparador*/
	// Shooter shooter;

	/*Objeto de torre*/
	// Intake intake;

	/*Botón para preparar el disparador*/
	Button bPrepare{[&]
					{ return control.GetRawButton(cRightBumper); }};

	/*Función para configurar las acciones relacionadas a cada botón*/
	void ConfigureButtonBindings();
};
