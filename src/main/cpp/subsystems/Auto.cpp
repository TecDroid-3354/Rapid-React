#include <frc/smartdashboard/smartdashboard.h>
#include "Constants.h"
#include <subsystems/Auto.h>
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableInstance.h"
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTableValue.h"
#include "wpi/span.h"

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

bool Auto::Move(float distance){
	
	movePID.SetSetpoint(-distance);
	
	double output = movePID.Calculate(-chasis.GetEncoderAverage());

	chasis.Drive(0,clamp(output,-0.4,0.4));

	SmartDashboard::PutString("Auto Step", "Move");
	return movePID.AtSetpoint();
}


bool Auto::Turn(float angle){

	turnPID.SetSetpoint(angle);
	double output = turnPID.Calculate(chasis.ReadGyro());

	chasis.Drive(clamp(output,-0.4,0.4),0);

	SmartDashboard::PutString("Auto Step", "Turn");

	return turnPID.AtSetpoint();
}

// Resetear todo
void Auto::Reset()
{

	// Resetear motores y sensores
	chasis.Reset();

	movePID.Reset();
	movePID.SetTolerance(1),

	turnPID.Reset();
	turnPID.SetTolerance(1);

	limelightPID.Reset();

	
}

void Auto::Run(){

	switch(movements[autoStep]){
		case 'a':
			SmartDashboard::PutBoolean("Done", Align(0));
			if(Align(0)){
				Reset();
				autoStep++;
			}
			break;
		
		case 'm':
			SmartDashboard::PutBoolean("Done", Move(setpoints[autoStep]));
			if(Move(setpoints[autoStep])){
				Reset();
				autoStep++;
			}
			break;

		case 't':
			SmartDashboard::PutBoolean("Done", Turn(setpoints[autoStep]));
			if(Turn(setpoints[autoStep])){
				Reset();
				autoStep++;
			}
			break;
	}

}
/*

void Auto::AdjustDistance(float requiredDistance){
	if(frontToTarget == 0 && !gotLimelightDistance){


		float verticalAngleRadians = verticalAngle*M_PI/180;

		frontToTarget = (kObjectiveHeight-kLimelightHeight)/tan(kLimelightAngle+verticalAngleRadians)-kLimelightToFront;

		if(frontToTarget != 0){
			gotLimelightDistance = true;
		}
	}

	SmartDashboard::PutNumber("Distancia a recorrer", frontToTarget - requiredDistance);

	if(frontToTarget != 0 && gotLimelightDistance){
		Move(frontToTarget - requiredDistance);
	}

}
*/
bool Auto::Align(float setpoint = 0){

	limelightPID.SetSetpoint(0);

	std::shared_ptr<nt::NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");

	double outputTurn = limelightPID.Calculate(-table->GetNumber("tx", 0.0));
	//double outputMove = limelightPID.Calculate(-table->GetNumber("ty", 0.0));

 	chasis.Drive(clamp(outputTurn, -0.4, 0.4), 0);

	return limelightPID.AtSetpoint();
}