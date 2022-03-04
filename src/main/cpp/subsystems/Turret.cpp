#include "subsystems/Turret.h"

#include "Constants.h"
#include "frc/smartdashboard/Smartdashboard.h"
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableInstance.h"
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTableValue.h"
#include "wpi/span.h"

using namespace frc;
using namespace std;

Turret::Turret()
{
	anglePID.SetTolerance(0.1);
	alignPID.SetTolerance(0.1);
}

void Turret::Periodic()
{

	float turretDeg = (encoder.Get() * 44.4) / 360;
	limelight = nt::NetworkTableInstance::GetDefault().GetTable("limelight");

	bool sensorMode = SmartDashboard::GetBoolean("Sensor Mode", false);
	bool climbMode = SmartDashboard::GetBoolean("Climb Mode", false);
	SmartDashboard::PutNumber("Turret Encoder", turretDeg);
	if (!sensorMode)
		Move();
	else if (sensorMode)
		Align();
}

bool Turret::SetAngle(float angle)
{
	float output;

	anglePID.SetSetpoint(angle);

	output = anglePID.Calculate(encoder.Get());

	motor.Set(clamp(output, -kTurretSpeed, kTurretSpeed));

	return anglePID.AtSetpoint();
}

bool Turret::Align()
{
	float output;

	alignPID.SetSetpoint(0);

	output = alignPID.Calculate(-limelight->GetNumber("tx", 0.0));

	// SI el output es positivo, y no ha llegado a su ángulo máximo a la derecha,
	// o si el output es negativo y no ha llegado a su ángulo máximo a la izquierda, setear el motor

	motor.Set(clamp(output, -kTurretSpeed, kTurretSpeed));

	return alignPID.AtSetpoint();
}

void Turret::Reset()
{
	encoder.Reset();
}

void Turret::Move()
{
	motor.Set((-control.GetRawButton(cRightBumper) + control.GetRawButton(cLeftBumper)) * kTurretSpeed);
}