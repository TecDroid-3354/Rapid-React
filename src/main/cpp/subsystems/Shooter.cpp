#include "subsystems/Shooter.h"

#include "Constants.h"
#include "frc/smartdashboard/Smartdashboard.h"
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableInstance.h"
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTableValue.h"
#include "wpi/span.h"

using namespace frc;

Shooter::Shooter()
{

	speedPID.SetTolerance(0.1);
}

void Shooter::Periodic()
{

	limelight = nt::NetworkTableInstance::GetDefault().GetTable("limelight");

	bool climbMode = SmartDashboard::GetBoolean("Climb Mode", false);
	bool sensorMode = SmartDashboard::GetBoolean("Sensor Mode", false);

	if (!climbMode)
	{
		if (!sensorMode)
		{
			Shoot(control.GetRightTriggerAxis());
		}

		else
		{
			Shoot(CalculateDistance(kLimelightAngle));
		}
	}
}

bool Shooter::ReachRPM(float rpm)
{
	double speed;

	speedPID.SetSetpoint(rpm);
	speed = speedPID.Calculate(encoder.GetRate());
	mShooter.Set(std::clamp(speed, -1.0, 1.0));

	return speedPID.AtSetpoint();
}

void Shooter::Shoot(float speed)
{
	mShooter.Set(speed);
	/*
	if (ReachRPM(CalculateRPM()))
	{
		Feed();
	}
	*/
}

void Shooter::Feed()
{
	mFeeder.Set(kFeederSpeed);
}

double Shooter::CalculateRPM()
{
	float angle = limelight->GetNumber("ty", 0) * M_PI / 180;

	return CalculateDistance(angle); // Aquí irá la función de rpm según distancia
}

double Shooter::CalculateDistance(float angle)
{
	return (kObjectiveHeight - kLimelightHeight) / tan(kLimelightAngle + angle) - kLimelightToFront;
}

void Shooter::SetServos(float length)
{
	mServoRight.Set(length);
	mServoLeft.Set(length);
}

void Shooter::ResetServos()
{
	mServoRight.Set(0);
	mServoRight.Set(0);
}

void Shooter::ResetMotors()
{
	mFeeder.RestoreFactoryDefaults();
	mShooter.RestoreFactoryDefaults();
}

void Shooter::ResetEncoder()
{
	encoder.Reset();
}

void Shooter::Reset()
{
	ResetServos();
	ResetEncoder();
	ResetMotors();
}
