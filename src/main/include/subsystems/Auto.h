#pragma once

#include "subsystems/Drivetrain.h"
#include <frc/smartdashboard/smartdashboard.h>
#include <math.h>
#include "Constants.h"
#include <iostream>
#include <string.h>
#include "subsystems/PIDSubsystems/LimelightPID.h"
#include "subsystems/PIDSubsystems/TurnPID.h"
#include "subsystems/PIDSubsystems/MovePID.h"

using namespace frc;
using namespace std;

/*Clase para controlar el autónomo*/
class Auto : public frc2::SubsystemBase
{
public:
	// El autónomo se construye a partir de los subsistemas que va a controlar
	explicit Auto(Drivetrain &);

	// Función que ocurre todo el tiempo
	void Periodic() override;

	// Resetear sensores
	void Reset();

	// Mover el chasis la distancia seleccionada
	void Move(float);

	// Girar el chasis hasta el ángulo seleccionado
	void Turn(float);

	// Quedar a una distancia específica del objetivo
	void AdjustDistance(float);

	// Alinear con el objetivo
	void Align();

private:
	// Chasis
	Drivetrain &chasis;

	// Controlador para alinearse al objetivo por medio de la Limelight
	LimelightPID limelightPID{chasis, kP, kI, kD};

	// Controlador para recorrer distancias específicas
	MovePID movePID{chasis, kP, kI, kD};

	// Controlador para girar un ángulo específico
	TurnPID turnPID{chasis, kP, kI, kD};

	/* Temporizador
	frc::Timer timer;

	double horizontalAngle, verticalAngle, targetArea, targetSkew;

	float frontToTarget = 0;
	bool gotLimelightDistance = false;*/
};
