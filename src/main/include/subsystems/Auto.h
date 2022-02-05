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
	// El autónomo se construye a partir de los subsistemas que va a controlar
	explicit Auto(Drivetrain &);

	// Función que ocurre todo el tiempo
	void Periodic() override;

	// Resetear sensores
	void Reset();

	// Mover el chasis la distancia seleccionada
	bool Move(float);

	// Girar el chasis hasta el ángulo seleccionado
	bool Turn(float);

	// Quedar a una distancia específica del objetivo
	void AdjustDistance(float);

	// Alinear con el objetivo
	bool Align(float);

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

	vector<double> setpoints = {100, 90, 50, 90, 100, 90, 0, 50};

	vector<char> movements ={'m', 't', 'm', 't', 'm', 't', 'a', 'm'};

	
	int autoStep = 0;

	// Temporizador
	frc::Timer timer;

	double horizontalAngle, verticalAngle, targetArea, targetSkew;

	float frontToTarget = 0;
	bool gotLimelightDistance = false;
};
