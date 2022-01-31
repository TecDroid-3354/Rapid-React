#include "subsystems/Drivetrain.h"
#include <frc/smartdashboard/smartdashboard.h>
#include <math.h>
#include "Constants.h"
#include <iostream>
#include <string.h>
#include <subsystems/Auto.h>

using namespace frc;
using namespace std;
using namespace nt;

void Drivetrain::RunAuto(){

	float requiredDistance = 200;
	
	
	/*
	float error = fabs(fabs(encoderFrontRight.GetPosition()-encoderFrontLeft.GetPosition())/2*kDistancePerRotation-requiredDistance);
	
	if(error>0.1){
		MoveForward(requiredDistance);
	}
	*/

	TurnToAngle(90);
	
	SmartDashboard::PutString("Running","Running");
	//|SmartDashboard::PutNumber("Error",error);
    SmartDashboard::PutNumber("SetPoint", requiredDistance);


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
	
}