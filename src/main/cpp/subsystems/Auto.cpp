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
	SmartDashboard::PutNumber("Skew", targetSkew);
	*/

	DeterminePosition();


}



bool Auto::Move(float distance, float speed){
	
	SmartDashboard::PutNumber("Moving to", distance);

	movePID.SetSetpoint(-distance);
	
	float output = movePID.Calculate(-chasis.GetEncoderAverage());

	chasis.Drive(0, clamp(output,-speed,speed));

	return movePID.AtSetpoint();
}


bool Auto::Turn(float angle, float speed){

	SmartDashboard::PutNumber("Turning To", angle);

	turnPID.SetSetpoint(angle);
	float output = turnPID.Calculate(chasis.ReadGyroDeg());

	chasis.Drive(clamp(output,-speed,speed),0);


	return turnPID.AtSetpoint();
}

// Resetear todo
void Auto::Reset()
{



	chasis.Reset();

	movePID.Reset();
	movePID.SetTolerance(0.1),

	turnPID.Reset();
	turnPID.SetTolerance(0.1);

	limelightPID.Reset();

	moveToTurning = true;

	displacementRight = 0;
	displacementLeft = 0;
	currentX = 0;
	currentY = 0;
	heading = 0;
	// Resetear motores y sensores
	DeterminePosition();
}


void Auto::Run(){


}

bool Auto::MoveTo(vector<float> coordinate, float speed){


	//Calcular el ángulo que debe girar según la coordenada actual, la coordenada meta, y la dirección a la que está viendo
	//Girar el ángulo
	//Determinar si ya llegó al ángulo
	//Resetear encoders
	//Determinar distancia según coordenada actual y coordenada meta
	//Avanzar distancia
	//Determinar si ya llegó a la coordenada
	//Asignar la coordenada meta como la nueva coordenada actual


}

void Auto::DeterminePosition(){

	float
		leftDelta = chasis.ReadLeftEncoders() - displacementLeft, // Esto tiene que cambia
		rightDelta = chasis.ReadRightEncoders() - displacementRight;

	SmartDashboard::PutNumber("Heading", heading);

	SmartDashboard::PutNumber("leftDelta", leftDelta);
	SmartDashboard::PutNumber("rightDelta", rightDelta);

	SmartDashboard::PutNumber("Disp R", displacementRight);
	SmartDashboard::PutNumber("Disp L", displacementLeft);

	
	if (fabs(chasis.ReadRightEncoders() - chasis.ReadLeftEncoders()) < 1.0e-6) //Si ambas ruedas avanzaron (casi) exactamente lo mismo
	{
		currentY += leftDelta * cos(heading);
		currentX += rightDelta * sin(heading);
	}
	else
	{
		float difference = (rightDelta - leftDelta);
		float r = kUnitsAxisWidth * (leftDelta + rightDelta) / (2 * difference != 0 ? difference : 1e-9);
		float wd = difference / kUnitsAxisWidth;

		currentY += r * sin(wd + heading) - r * sin(heading);
		currentX += -r * cos(wd + heading) + r * cos(heading);

		heading = fmod(heading + wd, 360);
	}

	SmartDashboard::PutNumber("X", currentX);
	SmartDashboard::PutNumber("Y", currentY);

	displacementRight = chasis.ReadRightEncoders();
	displacementLeft = chasis.ReadLeftEncoders();
	displacementAngle = chasis.ReadGyroRad();


}

void Auto::Init(){

	Reset();

	autoStep = 0;
	positionTheta = 0;
	positionR = 0;
}

