#pragma once

#include <frc2/command/SubsystemBase.h>
#include <rev/CANSparkMax.h>
#include "Constants.h"
#include "frc/XboxController.h"
#include <frc/Encoder.h>
#include <frc2/command/PIDSubsystem.h>
#include <networktables/NetworkTable.h>
#include <frc/Servo.h>

using namespace frc;
using namespace frc2;
using namespace rev;

// Clase para el disparador
class Shooter : public SubsystemBase
{
public:
	Shooter();

	// Función que ocurre todo el tiempo
	void Periodic() override;

	bool ReachRPM(float rpm);

	void Shoot();

	void Feed();

	void SetServos(float length);

	double CalculateRPM();

	double CalculateDistance(float);

	void ResetServos();

	void ResetMotors();

	void ResetEncoder();

	void Reset();

private:
	// Motor del disparador
	CANSparkMax mShooter{shooterDeviceID, CANSparkMax::MotorType::kBrushed};

	CANSparkMax mFeeder{feederDeviceID, CANSparkMax::MotorType::kBrushed};

	Encoder encoder{pEncoderShooterA, pEncoderShooterB, false};

	PIDController speedPID{kShooterP, kShooterI, kShooterD};

	Servo mServoRight{pServoRight};

	Servo mServoLeft{pServoLeft};

	// Control
	XboxController control{0};

	std::shared_ptr<nt::NetworkTable> limelight;
};
