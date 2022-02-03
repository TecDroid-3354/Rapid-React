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

		LimelightPID(Drivetrain &ch, double kP, double  kI, double  kD)
			: PIDSubsystem(frc2::PIDController(kP, kI, kD)), chasis{ch}{
				m_controller.EnableContinuousInput(-45,45);
				m_controller.SetIntegratorRange(-0.5,0.5);
				m_controller.SetTolerance(0.1,1);	
			}


		double GetMeasurement() override{
			/*std::shared_ptr<nt::NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
			return table.Get("tx",0.0);*/
			return 0;
		} 

		void UseOutput(double output, double setpoint) override{
			chasis.Drive(0,std::clamp(output,-0.3,0.3));
		}

		bool AtSetpoint() {
  			return m_controller.AtSetpoint();
		}

	private:
		Drivetrain &chasis;
};

//Controlador PID para avanzar con encoders
class MovePID : public PIDSubsystem {

	public:

		MovePID(Drivetrain &ch, double kP, double  kI, double  kD)
			: PIDSubsystem(frc2::PIDController(kP, kI, kD)), chasis{ch}{
				m_controller.SetIntegratorRange(-0.5,0.5);
				m_controller.SetTolerance(0.1,1);	
			}


		double GetMeasurement() override{
			SmartDashboard::PutNumber("PID Input", chasis.GetEncoderAverage());
			return chasis.GetEncoderAverage();
		} 

		void UseOutput(double output, double setpoint) override{
			chasis.Drive(0,clamp(output,-0.4,0.4));
			SmartDashboard::PutNumber("Encoder PID Output",std::clamp(output,-0.3,0.3));
		}

		bool AtSetpoint() {
  			return m_controller.AtSetpoint();
		}

	private:
		Drivetrain &chasis;
};

//Controlador PID para girar con giroscopio
class TurnPID : public PIDSubsystem{

//
	public:

		TurnPID(Drivetrain &ch, double kP, double kI, double kD) 
		: PIDSubsystem(frc2::PIDController(kP,kI,kD)),  // A la vez que creamos el TurnPID, creamos un controlador PID llamado m_controller
		chasis{ch}{ //La variable chasis de esta clase ahora es una referencia al chasis global
			m_controller.EnableContinuousInput(-360,360);
			m_controller.SetTolerance(0.1,1); //El 0.1 significa que para que el PID sepa que ya llegó, debe estar a 0.1 de la meta
			m_controller.SetIntegratorRange(-0.5,0.5);
		} 

		double GetMeasurement() override{
			return chasis.ReadGyro();
		}

		void UseOutput(double output, double setpoint) override{
			chasis.Drive(clamp(output,-0.4,0.4),0);
		}

		bool AtSetpoint(){
			return m_controller.AtSetpoint();
		}

	private:

		Drivetrain &chasis;

	
};


/*Clase para controlar el autónomo*/
class Auto : public frc2::SubsystemBase
{
public:
	/*
	   El autónomo recibe los objetos del chasis, la torre y el disparador para poderlos controlar
	*/
	explicit Auto(Drivetrain&);

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
	Drivetrain &chasis;

	
	double kP = 0.1, kI = 1e-4, kD = 1, kIz = 0, kFF = 0;

	LimelightPID limelightPID{chasis, kP,kI,kD};

	float frontToTarget = 0;
	bool gotLimelightDistance = false;

	MovePID movePID{chasis,kP,kI,kD};

	TurnPID turnPID{chasis,kP,kI,kD};

	// Temporizador
	frc::Timer timer;

	double horizontalAngle, verticalAngle, targetArea, targetSkew;
};
