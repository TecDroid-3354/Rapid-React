#include "Constants.h"
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTableInstance.h"
#include "networktables/NetworkTableValue.h"
#include "wpi/span.h"
#include <frc/smartdashboard/smartdashboard.h>
#include <subsystems/Auto.h>
#include <vector>

using namespace frc;
using namespace std;
using namespace nt;

/*
void Auto::Run(){

	float requiredDistance = 200;

	Align(100);


	float error = fabs(fabs(encoderFrontRight.GetPosition()-encoderFrontLeft.GetPosition())/2*kDistancePerRotation-requiredDistance);

	if(error>0.1){
		MoveForward(requiredDistance);
	}


	TurnToAngle(90);

	SmartDashboard::PutString("Running","Running");
	//|SmartDashboard::PutNumber("Error",error);
	SmartDashboard::PutNumber("SetPoint", requiredDistance);

	float victorSpeed = 0.2;
	testVictor.Set(victorSpeed);
	SmartDashboard::PutNumber("Test Motor Speed", testVictor.Get());
	SmartDashboard::PutNumber("Test Victor Channel", testVictor.GetChannel());
	SmartDashboard::PutString("Test Victor's dear name", testVictor.GetName());

}*/

Auto::Auto(Drivetrain &ch) : chasis{ch}
{ // El :chasis{ch}  es como poner chasis = ch adentro de la función
}

void Auto::Periodic()
{

	DeterminePosition();
	SmartDashboard::PutNumber("X", currentX);
	SmartDashboard::PutNumber("Y", currentY);
	/*
	std::shared_ptr<nt::NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
	horizontalAngle = table->GetNumber("tx",0.0);
	verticalAngle = table->GetNumber("ty",0.0);
	targetArea = table->GetNumber("ta",0.0);
	targetSkew = table->GetNumber("ts",0.0);

	SmartDashboard::PutNumber("Horizontal", horizontalAngle);
	SmartDashboard::PutNumber("Vertical", verticalAngle);
	SmartDashboard::PutNumber("Area", targetArea);
	SmartDashboard::PutNumber("Skew", targetSkew);
	*/

	SmartDashboard::PutNumber("Auto Step", autoStep);
	SmartDashboard::PutBoolean("Turning", moveToTurning);
}

bool Auto::Move(float distance, float speed)
{

	SmartDashboard::PutNumber("Moving to", distance);

	movePID.SetSetpoint(-distance);

	float output = movePID.Calculate(-chasis.GetEncoderAverage());

	chasis.Drive(0, clamp(output, -speed, speed));

	return movePID.AtSetpoint();
}

bool Auto::Turn(float angle, float speed)
{

	SmartDashboard::PutNumber("Turning To", angle);

	turnPID.SetSetpoint(angle);
	float output = turnPID.Calculate(chasis.ReadGyroDeg());

	chasis.Drive(clamp(output, -speed, speed), 0);

	return turnPID.AtSetpoint();
}

// Resetear todo
void Auto::Reset()
{



	chasis.Reset();

	movePID.Reset();
	movePID.SetTolerance(0.1);

	turnPID.Reset();
	turnPID.SetTolerance(0.1);

	limelightPID.Reset();

	moveToTurning = true;
}

void Auto::Run()
{

	if (autoStep < setpoints.size() && MoveTo(setpoints[autoStep], kAutoSpeed))
	{
		Reset();
		autoStep++;
	}
}

bool Auto::MoveTo(vector<float> coordinate, float speed)
{

	float x = coordinate[0] - currentX;
	float y = coordinate[1] - currentY;

	float distance = sqrt(pow(x, 2) + pow(y, 2));
	float angle = atan(y / (x == 0 ? 0.01 : x)) * 180 / M_PI;

	if (moveToTurning)
	{
		if (Turn(angle, speed))
		{
			moveToTurning = false;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return Move(distance, speed);
	}
}

void Auto::DeterminePosition()
{

	float rightDelta = chasis.ReadRightEncoders() - absoluteRightDisplacement;
	float leftDelta = chasis.ReadLeftEncoders() - absoluteLeftDisplacement;
	float heading = chasis.ReadGyro();

	float new_x, new_y;

	if (fabs(leftDelta - rightDelta) < 1.0e-6)
	{ // basically going straight
		new_x = currentX + leftDelta * cos(heading);
		new_y = currentY + rightDelta * sin(heading);
	}
	else
	{
		float R = kUnitsAxisWidth * (leftDelta + rightDelta) / (2 * (rightDelta - leftDelta));
		float wd = (rightDelta - leftDelta) / kUnitsAxisWidth;

		new_x = currentX + R * sin(wd + heading) - R * sin(heading);
		new_y = currentY - R * cos(wd + heading) + R * cos(heading);
	}

	absoluteRightDisplacement = chasis.ReadRightEncoders();
	absoluteLeftDisplacement = chasis.ReadLeftEncoders();
}

void Auto::Init()
{

	Reset();

	autoStep = 0;
	positionTheta = 0;
	positionR = 0;
}

