/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2019 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/TimedRobot.h>
#include <frc2/command/Command.h>
#include <frc/motorcontrol/VictorSP.h>
#include "RobotContainer.h"
#include "cameraserver/CameraServer.h"

#include "frc/ADIS16448_IMU.h"
using namespace cs;

/*
	Clase que controla las etapas del robot
*/
class Robot : public frc::TimedRobot
{
public:
	void RobotInit() override;
	void RobotPeriodic() override;
	void DisabledInit() override;
	void DisabledPeriodic() override;
	void AutonomousInit() override;
	void AutonomousPeriodic() override;
	void TeleopInit() override;
	void TeleopPeriodic() override;
	void TestInit();
	void TestPeriodic() override;

private:
	/*Objeto del contenedor del robot*/
	RobotContainer robot;
};
