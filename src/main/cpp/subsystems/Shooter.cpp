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
}

bool Shooter::ReachRPM(float rpm)
{

	speedPID.SetSetpoint(rpm);
	double speed = speedPID.Calculate(encoder.GetRate());
	mShooter.Set(std::clamp(speed, -1.0, 1.0));

	return speedPID.AtSetpoint();
}

void Shooter::Shoot()
{

	if (ReachRPM(CalculateRPM()))
	{
		Feed();
	}
}

void Shooter::Feed()
{
	mFeeder.Set(kFeederSpeed);
}

double Shooter::CalculateRPM()
{
	float angle = limelight->GetNumber("ty", 0) * M_PI / 180;

	return CalculateDistance(angle);
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