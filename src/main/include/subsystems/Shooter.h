#pragma once

#include <frc2/command/SubsystemBase.h>
#include <rev/CANSparkMax.h>
#include "Constants.h"
#include "frc/Timer.h"
#include "frc/XboxController.h"
#include "frc/DoubleSolenoid.h"
#include "frc/Solenoid.h"

using namespace frc;
using namespace rev;

// Clase para el disparador
class Shooter : public frc2::SubsystemBase
{
public:
	Shooter();

	// Función que ocurre todo el tiempo
	void Periodic() override;

	// Activar el motor
	void SetMotor(float speed);

private:
	// Motor del disparador
	CANSparkMax motor{shooterDeviceID, CANSparkMax::MotorType::kBrushed};

	// Control
	XboxController control{0};


};
