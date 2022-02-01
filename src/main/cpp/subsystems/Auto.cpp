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


	



void Drivetrain::RunAuto(){

	float requiredDistance = 200;
	
	Align(100);
	
	/*
	float error = fabs(fabs(encoderFrontRight.GetPosition()-encoderFrontLeft.GetPosition())/2*kDistancePerRotation-requiredDistance);
	
	if(error>0.1){
		MoveForward(requiredDistance);
	}
	*/

	/*

	
	TurnToAngle(90);
	
	SmartDashboard::PutString("Running","Running");
	//|SmartDashboard::PutNumber("Error",error);
    SmartDashboard::PutNumber("SetPoint", requiredDistance);
*/

	/*
	float victorSpeed = 0.2;
	testVictor.Set(victorSpeed);
	SmartDashboard::PutNumber("Test Motor Speed", testVictor.Get());
	SmartDashboard::PutNumber("Test Victor Channel", testVictor.GetChannel());
	SmartDashboard::PutString("Test Victor's dear name", testVictor.GetName());
	*/	
}


void Drivetrain::MoveForward(float distance){
	PIDFrontRight.SetReference(-distance/kDistancePerRotation, CANSparkMax::ControlType::kPosition);
	PIDFrontLeft.SetReference(distance/kDistancePerRotation, CANSparkMax::ControlType::kPosition);
}

void Drivetrain::TurnToAngle(float angle){
	PIDFrontRight.SetReference((angle*M_PI/180*30)/kDistancePerRotation, CANSparkMax::ControlType::kPosition);
	PIDFrontLeft.SetReference((angle*M_PI/180*30)/kDistancePerRotation, CANSparkMax::ControlType::kPosition);
}

void Drivetrain::ResetAuto(){

	PIDFrontLeft.SetP(kP);
    PIDFrontLeft.SetI(kI);
    PIDFrontLeft.SetD(kD);
    PIDFrontLeft.SetIZone(kIz);
    PIDFrontLeft.SetFF(kFF);
    PIDFrontLeft.SetOutputRange(kMinOutput, kMaxOutput);
	

	PIDFrontRight.SetP(kP);
    PIDFrontRight.SetI(kI);
    PIDFrontRight.SetD(kD);
    PIDFrontRight.SetIZone(kIz);
    PIDFrontRight.SetFF(kFF);
    PIDFrontRight.SetOutputRange(kMinOutput, kMaxOutput);

	gyroPID.EnableContinuousInput(-360,360);
	gyroPID.SetIntegratorRange(-0.5,0.5);
	gyroPID.SetTolerance(0.1,1);	


	encoderFrontRight.SetPosition(0);
	encoderFrontLeft.SetPosition(0);
	encoderBackRight.SetPosition(0);
	encoderBackLeft.SetPosition(0);
	
	frontToTarget = 0;
	gotLimelightDistance = false;
	
}

void Drivetrain::Align(float requiredDistance){

	std::shared_ptr<nt::NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
	double horizontalAngle = table->GetNumber("tx",0.0);
	double verticalAngle = table->GetNumber("ty",0.0);
	double targetArea = table->GetNumber("ta",0.0);
	double targetSkew = table->GetNumber("ts",0.0);

	SmartDashboard::PutNumber("Horizontal", horizontalAngle);
	SmartDashboard::PutNumber("Vertical", verticalAngle);
	SmartDashboard::PutNumber("Area", targetArea);
	SmartDashboard::PutNumber("Skew", targetSkew);



	if(frontToTarget == 0 && !gotLimelightDistance){
		
		
		float verticalAngleRadians = verticalAngle*M_PI/180;

		frontToTarget = (kObjectiveHeight-kLimelightHeight)/tan(kLimelightAngle+verticalAngleRadians)-kLimelightToFront;
		
		if(frontToTarget != 0){
			gotLimelightDistance = true;
		}
	}

	SmartDashboard::PutNumber("Distancia a recorrer", frontToTarget - requiredDistance);

	if(frontToTarget != 0 && gotLimelightDistance){
		MoveForward(frontToTarget - requiredDistance);
	}

}