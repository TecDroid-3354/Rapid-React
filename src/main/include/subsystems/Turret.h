#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/motorcontrol/VictorSP.h>
#include "Constants.h"
#include "frc/XboxController.h"
#include <frc/Encoder.h>
#include <frc2/command/PIDSubsystem.h>
#include <networktables/NetworkTable.h>
#include <frc/Encoder.h>

using namespace frc;
using namespace frc2;

// Clase para el disparador
class Turret : public SubsystemBase
{
public:
	Turret();

	// Función que ocurre todo el tiempo
	void Periodic() override;

	bool Align();

	void Move();

	bool SetAngle(float);

	void Reset();

private:
	VictorSP motor{pTurret};

	Encoder encoder{pEncoderTurretA, pEncoderTurretB};

	PIDController anglePID{kTurretEncoderP, kTurretEncoderI, kTurretEncoderD};

	PIDController alignPID{kTurretAlignP, kTurretAlignI, kTurretAlignD};

	// Control
	XboxController control{0};

	std::shared_ptr<nt::NetworkTable> limelight;
};
