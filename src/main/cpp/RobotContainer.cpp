/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "RobotContainer.h"

// Al iniciar el robot, configurar los botones
RobotContainer::RobotContainer()
{
	ConfigureButtonBindings();
}

// Configurar los comandos según el botón
void RobotContainer::ConfigureButtonBindings()
{

	// Al presionar right bumper, preparar el disparador
	//	bPrepare.WhenPressed(new Prepare(&shooter, &intake));
}

// Funciones de manejo del robot
void RobotContainer::Drive()
{
	// Manejar el robot según el control
	chasis.Drive();

	// Mover la torre según el control
	// shooter.Move();
}

void RobotContainer::Reset()
{
	chasis.Reset();
	// shooter.Reset();
	// intake.Reset();
}

void RobotContainer::RunAuto()
{
	// auton.Move(50);
	//auton.Turn(90);
	auton.Run();
}

void RobotContainer::ResetAuto()
{
	auton.Reset();
}