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

	//Resetear robot
	void Reset();

	void Test();

	void RunAuto();

	void ResetAuto();

	/*Temporizador*/
	frc::Timer timer;

private:
	// The robot's subsystems and commands are defined here...


	// Objeto de control
	XboxController control{0};

	/*Objeto de chasis*/
	Drivetrain chasis;

	/*Objeto de disparador*/
	//Shooter shooter;

	/*Objeto de torre*/
	//Intake intake;

	Auto auton{chasis};

	/*Botón para preparar el disparador*/
	Button bPrepare{[&]
					{ return control.GetRawButton(cRightBumper); }};

	/*Función para configurar las acciones relacionadas a cada botón*/
	void ConfigureButtonBindings();
};
