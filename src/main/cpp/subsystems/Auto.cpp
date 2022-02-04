#include "subsystems/Drivetrain.h"
#include <frc/smartdashboard/smartdashboard.h>
#include <math.h>
#include "Constants.h"
#include <iostream>
#include <string.h>
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

Auto::Auto(Drivetrain &ch):chasis{ch}{

}

void Auto::Periodic(){
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


void Auto::Move(float distance){
	
	movePIDController.SetSetpoint(-distance);
	
	double output = movePIDController.Calculate(-chasis.GetEncoderAverage());

	chasis.Drive(0,clamp(output,-0.7,0.7));
}


void Auto::Turn(float angle){

	turnPIDController.SetSetpoint(-angle);
	double output = turnPIDController.Calculate(chasis.ReadGyro());

	chasis.Drive(clamp(output,-0.6,0.6),0);
	
}



void Auto::Reset(){

	chasis.Reset();

	movePIDController.Reset();
	
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

void Auto::Align(){
	
}*/