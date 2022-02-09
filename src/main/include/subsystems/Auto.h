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
	//std::

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

	// Alinear con el objetivo
	bool Align(float);

	void DeterminePosition();

	void Run();

private:
	// Chasis
	Drivetrain &chasis;

	const double kMoveP = 0.1, kMoveI = 0, kMoveD = 0;

	const double kTurnP = 0.1, kTurnI = 0, kTurnD = 0.01;

	const double kLimeP = 0.1, kLimeI = 0, kLimeD = 0.001;

	PIDController movePID{kMoveP,kMoveI,kMoveD};

	PIDController turnPID{kTurnP,kTurnI,kTurnD};

	PIDController limelightPID{kLimeP, kLimeI, kLimeD};

	vector<vector<float>> setpoints = {{50,50}};
	
	int autoStep = 0;

	// Temporizador
	frc::Timer timer;

	double horizontalAngle, verticalAngle, targetArea, targetSkew;

	float frontToTarget = 0;
	bool gotLimelightDistance = false;

	float positionTheta = 0, positionR = 0;

	bool moveToTurning = true;

	double maxSpeed = 0.5;
};
