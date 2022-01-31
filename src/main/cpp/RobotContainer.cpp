/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "RobotContainer.h"
#include "frc2/command/button/JoystickButton.h"
#include "frc/smartdashboard/SmartDashboard.h"

// Al iniciar el robot, configurar los botones
RobotContainer::RobotContainer()
{
	ConfigureButtonBindings();
}

// Configurar los comandos según el botón
void RobotContainer::ConfigureButtonBindings()
{


}

// Funciones de manejo del robot
void RobotContainer::Drive()
{
	// Manejar el robot según el control
	chasis.Drive();
}

void RobotContainer::Test()
{
}

void RobotContainer::Reset(){
	chasis.Reset();
	chasis.ResetAuto();
}

void RobotContainer::RunAuto(){
	chasis.RunAuto();
}