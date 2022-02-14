#pragma once

#include "subsystems/Drivetrain.h"
#include "Constants.h"
#include <frc2/command/PIDSubsystem.h>
#include <vector>

using namespace frc;
using namespace std;

/*Clase para controlar el autónomo*/
class Auto : public frc2::SubsystemBase
{
public:

	// Vector que contiene referencias a todas las funciones que se ejecutarán durante el periodo autónomo
	// std::

	// El autónomo se construye a partir de los subsistemas que va a controlar
	explicit Auto(Drivetrain &);

	// Función que ocurre todo el tiempo
	void Periodic() override;

	// Resetear sensores
	void Reset();

	// Mover el chasis la distancia seleccionada
	bool Move(float, float);

	bool MoveTo(vector<float>, float);

	// Girar el chasis hasta el ángulo seleccionado
	bool Turn(float, float);

	// Quedar a una distancia específica del objetivo
	void AdjustDistance(float);

	void DeterminePosition();

	void Run();

	void Init();

private:
	// Chasis
	Drivetrain &chasis;

	PIDController movePID{kMoveP,kMoveI,kMoveD};

	PIDController turnPID{kTurnP,kTurnI,kTurnD};

	PIDController limelightPID{kLimeP, kLimeI, kLimeD};

	vector<vector<float>> setpoints = {{-100,100},{100,100}};
	
	unsigned int autoStep = 0;

	// Temporizador
	frc::Timer timer;

	double horizontalAngle, verticalAngle, targetArea, targetSkew;

	float frontToTarget = 0;
	bool gotLimelightDistance = false;

	float positionTheta = 0, positionR = 0;

	bool moveToTurning = true;

	double maxSpeed = 0.5;
};
