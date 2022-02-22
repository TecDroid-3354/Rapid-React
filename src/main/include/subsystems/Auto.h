#pragma once

#include "Constants.h"
#include "subsystems/Drivetrain.h"
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

	bool MoveTo(std::vector<float>, float);

	// Girar el chasis hasta el ángulo seleccionado
	bool Turn(float, float);

	// Quedar a una distancia específica del objetivo
	void AdjustDistance(float);

	//void DeterminePosition();

	void Run();

	void Init();

	float GetAbsoluteAngle(float, float);

private:
	// Chasis
	Drivetrain &chasis;

	PIDController movePID{kMoveP, kMoveI, kMoveD};

	PIDController turnPID{kTurnP, kTurnI, kTurnD};

	PIDController limelightPID{kLimeP, kLimeI, kLimeD};

	std::vector<std::vector<float>> setpoints = {{50, 50}, {0, 50}, {50,0},{0,0}};

	unsigned int autoStep = 0;

	// Temporizador
	frc::Timer timer;

	double horizontalAngle, verticalAngle, targetArea, targetSkew;

	float frontToTarget = 0;

	bool gotLimelightDistance = false;

	bool isTurning = true;

	double maxSpeed = 0.5;

	double currentX, currentY, currentAngle = 0;
};
