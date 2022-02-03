/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Drivetrain.h"
#include <frc/smartdashboard/smartdashboard.h>
#include <math.h>
#include "Constants.h"
#include <iostream>
#include <string.h>

using namespace frc;
using namespace std;
using namespace nt;

Drivetrain::Drivetrain()
{

}

// Periódicamente determina si se está picando el botón de cambiar modo de escalada
void Drivetrain::Periodic()
{

	SmartDashboard::PutNumber("FrontRight Motor", frontRight.Get());
	SmartDashboard::PutNumber("FrontLeft Motor", frontLeft.Get());
	SmartDashboard::PutNumber("BackLeft Motor", backLeft.Get());
	SmartDashboard::PutNumber("BackRight Motor", backRight.Get());

	SmartDashboard::PutNumber("Front Right Encoder", encoderFrontRight.GetPosition()*kDistancePerRotation);
	SmartDashboard::PutNumber("Front Left Encoder", encoderFrontLeft.GetPosition()*kDistancePerRotation);
	SmartDashboard::PutNumber("Back Right Encoder", encoderBackRight.GetPosition()*kDistancePerRotation);
	SmartDashboard::PutNumber("Back Left Encoder", encoderBackLeft.GetPosition()*kDistancePerRotation);

	SmartDashboard::PutNumber("Encoder Average",GetEncoderAverage());

	// Si se pica el botón, se cambia de modo, pero solamente hasta que el botón se suelta
	// Esto se hace para evitar que se cambie mil veces cada segundo
	if (flag && control.GetRawButton(cStart))
	{
		climbMode = !climbMode;
		flag = false;
	}
	else if (!control.GetRawButton(cStart))
	{
		flag = true;
	}




}

// Manejar el robot según el control
void Drivetrain::Drive()
{
// cambié x y y
	// El eje X determina el giro
	float x = control.GetRawAxis(cLeftAxisX);

	// El eje Y determina el avance
	float y = control.GetRawAxis(cLeftAxisY);

	// Utilizar los ejes para moverse, agregar o quitar signos negativos para cambiar de dirección
	//cambié negativo
	chasis.ArcadeDrive(x, y);	
}

// Manejar el robot según valores específicos
void Drivetrain::Drive(float x, float y)
{
	
	chasis.ArcadeDrive(x,y);
}

// Activar seguridad del chasis
void Drivetrain::SetSafetyEnabled(bool state)
{
	chasis.SetSafetyEnabled(state);
}


void Drivetrain::Reset(){
	frontRight.RestoreFactoryDefaults();
	backRight.RestoreFactoryDefaults();
	frontLeft.RestoreFactoryDefaults();
	backRight.RestoreFactoryDefaults();

	encoderFrontLeft.SetPosition(0);
	encoderBackLeft.SetPosition(0);
	encoderFrontRight.SetPosition(0);
	encoderBackRight.SetPosition(0);

	gyro.Reset();
}

float Drivetrain::GetEncoderAverage(){
	return ((encoderFrontLeft.GetPosition()+encoderBackLeft.GetPosition())-(encoderBackRight.GetPosition()+encoderFrontRight.GetPosition()))*kDistancePerRotation/4;
}

float Drivetrain::ReadGyro(){
	return gyro.GetAngle().value();
}