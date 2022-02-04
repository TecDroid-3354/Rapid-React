#pragma once

#include "subsystems/Drivetrain.h"
#include <frc/smartdashboard/smartdashboard.h>
#include <math.h>
#include "Constants.h"
#include <iostream>
#include <string.h>

using namespace frc;
using namespace std;


/*Clase para controlar el autónomo*/
class Auto : public frc2::SubsystemBase
{
public:
	/*
	   El autónomo recibe los objetos del chasis, la torre y el disparador para poderlos controlar
	*/
	explicit Auto(Drivetrain&);

	// Función que ocurre todo el tiempo
	void Periodic() override;

	// Resetear
	void Reset();

	// Mover el chasis
	void Move(float);

	void Turn(float);

	void AdjustDistance(float);

	void Align();

private:
	// Cámara pixy
	//PixySource source;

	// Chasis
	Drivetrain &chasis;

	double kMoveP = 0.1, kMoveI = 0, kMoveD = 0;

	double kTurnP = 0.1, kTurnI = 0, kTurnD = 0.023;

	float frontToTarget = 0;
	bool gotLimelightDistance = false;


	PIDController movePIDController{kMoveP,kMoveI,kMoveD};

	PIDController turnPIDController{kTurnP,kTurnI,kTurnD};

	// Temporizador
	frc::Timer timer;

	double horizontalAngle, verticalAngle, targetArea, targetSkew;
};
