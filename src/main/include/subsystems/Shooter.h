#pragma once

#include <frc2/command/SubsystemBase.h>
#include "frc/motorcontrol/VictorSP.h"
#include "Constants.h"
#include "frc/Timer.h"
#include "frc/XboxController.h"
#include "frc/DoubleSolenoid.h"
#include "frc/Solenoid.h"

using namespace frc;

// Clase para el disparador
class Shooter : public frc2::SubsystemBase
{
public:
	Shooter();

	// Función que ocurre todo el tiempo
	void Periodic() override;

	// Activar el motor
	void SetMotor(float speed);

	// Resetear
	void Reset();

	// Abrir los solenoides
	void Open();

	// Encender luz
	void Light(bool on);

	// Disparar
	void Move();

private:
	// Motor del disparador
	VictorSP motor{mShooter};

	// Control
	XboxController control{0};

	// Solenoide del stopper
	DoubleSolenoid stopper{PneumaticsModuleType::REVPH,pStopperFront, pStopperBack};

	// Luz
	//Solenoid light{5};
};
