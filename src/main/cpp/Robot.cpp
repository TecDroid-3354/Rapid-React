/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2019 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"
#include "subsystems/Drivetrain.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/CommandScheduler.h>
#include <frc/Joystick.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <RobotContainer.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/TimedRobot.h>
#include <frc/motorcontrol/PWMSparkMax.h>
#include <rev/CANSparkMax.h>

using namespace frc;
using namespace rev;

// Inicializar el robot
void Robot::RobotInit()
{

	// Obtener cámara 1
	cs::UsbCamera cam = frc::CameraServer::GetInstance()->StartAutomaticCapture(0);

	// Asignar resolución
	cam.SetResolution(640, 480);

	// Asignar FPS
	cam.SetFPS(40);

	// Obtener cámara 2
	cs::UsbCamera cam2 = frc::CameraServer::GetInstance()->StartAutomaticCapture(1);

	// Asignar resolución
	cam2.SetResolution(640, 480);

	// Asignar FPS
	cam2.SetFPS(40);

	
	// Restaurar a parámetros de fábrica para que siempre empiecen "desde cero"
	m_container.Reset();
}

// Periódicamente obtener el siguiente comando
void Robot::RobotPeriodic()
{

	frc2::CommandScheduler::GetInstance().Run();
}

void Robot::DisabledInit()
{
}

// Resetear el robot cuando se desactiva
void Robot::DisabledPeriodic()
{

}

// Inicializar autónomo
void Robot::AutonomousInit()
{

	// Resetear el paso
	step = 0;

}

// Función del autónomo
void Robot::AutonomousPeriodic()
{
}

// Inicializar teleoperado
void Robot::TeleopInit()
{


}

// Teleoperado
void Robot::TeleopPeriodic()
{


	// Manejar robot
	m_container.Drive();
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