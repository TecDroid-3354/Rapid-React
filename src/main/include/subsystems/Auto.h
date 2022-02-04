#pragma once

#include "subsystems/Drivetrain.h"
#include "Constants.h"
#include <frc2/command/PIDSubsystem.h>
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

	double kMoveP = 0.1, kMoveI = 0, kMoveD = 0;

	double kTurnP = 0.1, kTurnI = 0, kTurnD = 0.023;

	double kLimeP = 0.1, kLimeI = 0, kLimeD = 0.01;

	PIDController movePID{kMoveP,kMoveI,kMoveD};

	PIDController turnPID{kTurnP,kTurnI,kTurnD};

	PIDController limelightPID{kLimeP, kLimeI, kLimeD};

	// Temporizador
	frc::Timer timer;

	double horizontalAngle, verticalAngle, targetArea, targetSkew;

	float frontToTarget = 0;
	bool gotLimelightDistance = false;
};
