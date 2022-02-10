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
	limelight = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
}

bool Turret::SetAngle(float angle)
{
	anglePID.SetSetpoint(angle);

	float output = anglePID.Calculate(encoder.Get());

	motor.Set(clamp(output, -kTurretSpeed, kTurretSpeed));

	return anglePID.AtSetpoint();
}

bool Turret::Align()
{

	alignPID.SetSetpoint(0);

	float output = alignPID.Calculate(-limelight->GetNumber("tx", 0.0));

	motor.Set(clamp(output, -kTurretSpeed, kTurretSpeed));

	return alignPID.AtSetpoint();
}

void Turret::Reset()
{
	encoder.Reset();
}