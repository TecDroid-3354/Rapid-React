#include <frc/smartdashboard/smartdashboard.h>
#include "Constants.h"
#include <subsystems/Auto.h>
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableInstance.h"
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTableValue.h"
#include "wpi/span.h"
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

	/*

	std::shared_ptr<nt::NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
	horizontalAngle = table->GetNumber("tx",0.0);
	verticalAngle = table->GetNumber("ty",0.0);
	targetArea = table->GetNumber("ta",0.0);
	targetSkew = table->GetNumber("ts",0.0);

	SmartDashboard::PutNumber("Horizontal", horizontalAngle);
	SmartDashboard::PutNumber("Vertical", verticalAngle);
	SmartDashboard::PutNumber("Area", targetArea);
	SmartDashboard::PutNumber("Skew", targetSkew);*/
}

bool Auto::Move(float distance, float speed){
	
	movePID.SetSetpoint(-distance);
	
	float output = movePID.Calculate(-chasis.GetEncoderAverage());

	chasis.Drive(0,clamp(output,-speed,speed));

	SmartDashboard::PutString("Auto Step", "Move");
	return movePID.AtSetpoint();
}


bool Auto::Turn(float angle, float speed){

	turnPID.SetSetpoint(angle);
	float output = turnPID.Calculate(chasis.ReadGyro());

	chasis.Drive(clamp(output,-speed,speed),0);

	SmartDashboard::PutString("Auto Step", "Turn");

	return turnPID.AtSetpoint();
}

// Resetear todo
void Auto::Reset()
{

	// Resetear motores y sensores
	DeterminePosition();

	chasis.Reset();

	movePID.Reset();
	movePID.SetTolerance(0.1),

	turnPID.Reset();
	turnPID.SetTolerance(0.1);

	limelightPID.Reset();

	
}

void Auto::Run(){

	if(autoStep < setpoints.size() && MoveTo(setpoints[autoStep],kAutoSpeed)){
		autoStep++;
		Reset();
	}
}

bool Auto::MoveTo(vector<float> coordinate, float speed){

	float x = coordinate[0];
	float y = coordinate[1];

	float targetR = sqrt(pow(x,2) + pow(y,2));
	float targetTheta = atan(y / (x == 0 ? x+0.01 : x))*180/M_PI;

	float angle = targetTheta - positionTheta;
	float distance = targetR - positionR;

	if(moveToTurning){
		if(Turn(angle, speed)){
			chasis.ResetEncoders();
			moveToTurning = false;
			return true;
		} else {
			return false;
		}
	} else {
		return Move(distance, speed);
	}

}

void Auto::DeterminePosition(){

	positionTheta += chasis.ReadGyro();

	positionR += chasis.GetEncoderAverage();
}
