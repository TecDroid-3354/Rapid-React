/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Drivetrain.h"
#include <frc/smartdashboard/smartdashboard.h>
#include "Constants.h"

using namespace frc;
using namespace std;
using namespace nt;

Drivetrain::Drivetrain()
{
	encoderFrontRight.SetPositionConversionFactor(kDistancePerRotation);
	encoderFrontLeft.SetPositionConversionFactor(kDistancePerRotation);
	encoderBackRight.SetPositionConversionFactor(kDistancePerRotation);
	encoderBackLeft.SetPositionConversionFactor(kDistancePerRotation);
}

void Drivetrain::Periodic()
{

	// ------------------------- Publicar potencia utilizada por cada motor ----------------------
	SmartDashboard::PutNumber("FrontRight Motor", frontRight.Get());
	SmartDashboard::PutNumber("FrontLeft Motor", frontLeft.Get());
	SmartDashboard::PutNumber("BackLeft Motor", backLeft.Get());
	SmartDashboard::PutNumber("BackRight Motor", backRight.Get());

	// ------------------------- Publicar distancia recorrida por cada encoder ----------------------
	SmartDashboard::PutNumber("Front Right Encoder", encoderFrontRight.GetPosition());
	SmartDashboard::PutNumber("Front Left Encoder", encoderFrontLeft.GetPosition());
	SmartDashboard::PutNumber("Back Right Encoder", encoderBackRight.GetPosition());
	SmartDashboard::PutNumber("Back Left Encoder", encoderBackLeft.GetPosition());

	// Publicar distancia promedio de todos los encoders
	SmartDashboard::PutNumber("Encoder Average", GetEncoderAverage());

	SmartDashboard::PutNumber("Gyro", ReadGyro());

}

// Manejar el robot según el control
void Drivetrain::Drive()
{
	// El eje X determina el giro
	float x = control.GetRawAxis(cLeftAxisX);

	// El eje Y determina el avance
	float y = control.GetRawAxis(cLeftAxisY);

	// Utilizar los ejes para moverse, agregar o quitar signos negativos para cambiar de dirección
	chasis.ArcadeDrive(x, y);
}

// Manejar el robot según valores específicos
void Drivetrain::Drive(float x, float y)
{

	chasis.ArcadeDrive(x, y);
}

// Activar seguridad del chasis
void Drivetrain::SetSafetyEnabled(bool state)
{
	chasis.SetSafetyEnabled(state);
}

void Drivetrain::Reset()
{
	// ------------------------------ Resetear valores de los motores -------------------------

	ResetGyro();
	ResetEncoders();
}

void Drivetrain::ResetGyro(){
	gyro.Reset();
}

void Drivetrain::ResetEncoders(){
	encoderFrontLeft.SetPosition(0);
	encoderBackLeft.SetPosition(0);
	encoderFrontRight.SetPosition(0);
	encoderBackRight.SetPosition(0);
}
// Promedio de los encoders
float Drivetrain::GetEncoderAverage()
{
	// Los valores de los encoders derecho están negativos porque apuntan al lado contrario
	return (encoderFrontLeft.GetPosition() + encoderBackLeft.GetPosition() - (encoderBackRight.GetPosition() + encoderFrontRight.GetPosition()) )/4;
}

// Leer el giroscopio
float Drivetrain::ReadGyro()
{

	// Se le agrega .value() porque GetAngle() no regresa un número sino una variable tipo angle, .value() obtiene el valor numérico
	return gyro.GetAngle().value();
}