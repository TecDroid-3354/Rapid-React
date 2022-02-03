#pragma once

#include "subsystems/Drivetrain.h"
#include <frc/smartdashboard/smartdashboard.h>
#include <math.h>
#include "Constants.h"
#include <iostream>
#include <string.h>

using namespace frc;
using namespace std;


	
class LimelightPID : public PIDSubsystem {

	public:

		LimelightPID(Drivetrain *ch, double kP, double  kI, double  kD)
			: PIDSubsystem(frc2::PIDController(kP, kI, kD)){
				m_controller.EnableContinuousInput(-45,45);
				m_controller.SetIntegratorRange(-0.5,0.5);
				m_controller.SetTolerance(0.1,1);	
				chasis = ch;
			}


		double GetMeasurement() override{
			std::shared_ptr<nt::NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
			return table->GetNumber("tx",0.0);
		} 

		void UseOutput(double output, double setpoint) override{
			chasis->Drive(0,-std::clamp(output,-0.3,0.3));
		}

		bool AtSetpoint() {
  			return m_controller.AtSetpoint();
		}

	private:
		Drivetrain *chasis;
};




/*Clase para controlar el autónomo*/
class Auto : public frc2::SubsystemBase
{
public:
	/*
	   El autónomo recibe los objetos del chasis, la torre y el disparador para poderlos controlar
	*/
	explicit Auto(Drivetrain*);

	// Función que ocurre todo el tiempo
	void Periodic() override;

	// Resetear
	void Reset();

	// Mover el chasis
	void Move(float);

	void Turn(float);

	void AdjustDistance(float);

	void Align();

private:
	// Cámara pixy
	//PixySource source;

	// Chasis
	Drivetrain *chasis;

	/*SparkMaxRelativeEncoder encoderFrontRight{chasis->GetFrontRight()->GetEncoder()};

	SparkMaxRelativeEncoder encoderFrontLeft{chasis->GetFrontLeft()->GetEncoder()};

	SparkMaxRelativeEncoder encoderBackRight{chasis->GetBackRight()->GetEncoder()};

	SparkMaxRelativeEncoder encoderBackLeft{chasis->GetBackLeft()->GetEncoder()};

	SparkMaxPIDController PIDFrontRight{chasis->GetFrontRight()->GetPIDController()};

	SparkMaxPIDController PIDFrontLeft{chasis->GetFrontLeft()->GetPIDController()};

	SparkMaxPIDController PIDBackRight{chasis->GetBackRight()->GetPIDController()};

	SparkMaxPIDController PIDBackLeft{chasis->GetBackLeft()->GetPIDController()};
*/
	double kP = 0.1, kI = 1e-4, kD = 1, kIz = 0, kFF = 0, kMaxOutput = 0.2, kMinOutput = -0.2;

	LimelightPID limelightPID{chasis, kP,kI,kD};

	float frontToTarget = 0;
	bool gotLimelightDistance = false;

	// Temporizador
	frc::Timer timer;

	double horizontalAngle, verticalAngle, targetArea, targetSkew;
};
