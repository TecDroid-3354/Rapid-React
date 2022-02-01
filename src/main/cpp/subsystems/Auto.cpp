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
	
	Align();
	
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
	
}

void Drivetrain::Align(){



	std::shared_ptr<nt::NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
		double targetOffsetAngle_Horizontal = table->GetNumber("tx",0.0);
		double targetOffsetAngle_Vertical = table->GetNumber("ty",0.0);
		double targetArea = table->GetNumber("ta",0.0);
		double targetSkew = table->GetNumber("ts",0.0);

		SmartDashboard::PutNumber("Horizontal", targetOffsetAngle_Horizontal);
		SmartDashboard::PutNumber("Vertical", targetOffsetAngle_Vertical);
		SmartDashboard::PutNumber("Area", targetArea);
		SmartDashboard::PutNumber("Skew", targetSkew);

		float a2 = targetOffsetAngle_Vertical*M_PI/180;

		float d = (h2-h1)/tan(a1+a2)-d2;


	SmartDashboard::PutNumber("Distancia", d);


	if(d != 0){
		MoveForward(d-50);
	}

}