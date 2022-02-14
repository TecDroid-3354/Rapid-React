/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2019 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/CommandScheduler.h>

using namespace frc;


// Inicializar el robot
void Robot::RobotInit()
{

	
	// Obtener cámara 1
	// cs::UsbCamera cam = frc::CameraServer::GetInstance()->StartAutomaticCapture(0);

	// Asignar resolución
	// cam.SetResolution(640, 480);

	// Asignar FPS
	// cam.SetFPS(40);

	// Obtener cámara 2
	// cs::UsbCamera cam2 = frc::CameraServer::GetInstance()->StartAutomaticCapture(1);

	// Asignar resolución
	// cam2.SetResolution(640, 480);

	// Asignar FPS
	// cam2.SetFPS(40);

	// Restaurar a parámetros de fábrica para que siempre empiecen "desde cero"
	robot.Reset();
}

// Periódicamente obtener el siguiente comando
void Robot::RobotPeriodic()
{
	frc2::CommandScheduler::GetInstance().Run();
}

void Robot::DisabledInit()
{
	robot.Reset();
}

// Resetear el robot cuando se desactiva
void Robot::DisabledPeriodic()
{
}

// Inicializar autónomo
void Robot::AutonomousInit()
{

	// Resetear el paso
	robot.AutonomousInit();
}

// Función del autónomo
void Robot::AutonomousPeriodic()
{
	robot.AutonomousPeriodic();
}

// Inicializar teleoperado
void Robot::TeleopInit()
{
	robot.Reset();
}

// Teleoperado
void Robot::TeleopPeriodic()
{

	// Manejar robot
	robot.Drive();
}

void Robot::TestInit()
{
}
void Robot::TestPeriodic()
{
}

#ifndef RUNNING_FRC_TESTS
int main()
{
	return frc::StartRobot<Robot>();
}
#endif