#include "subsystems/Drivetrain.h"
#include <frc/smartdashboard/smartdashboard.h>
#include <math.h>
#include "Constants.h"
#include <iostream>
#include <string.h>

using namespace frc;
using namespace std;






/*Clase para controlar el autónomo*/
class Auto : public frc2::SubsystemBase
{
public:
	/*
	   El autónomo recibe los objetos del chasis, la torre y el disparador para poderlos controlar
	*/
	explicit Auto(Drivetrain);

	// Función que ocurre todo el tiempo
	void Periodic() override;

	// Resetear
	void Reset();

	// Desactivar
	void Disable();

	// Se encuentra activo?
	bool IsActive();

	// Mover el chasis
	bool Move(float setpoint);

	// Mover mientras prepara el disparador
	bool MoveLoad(float setpoint);

	// Girar
	bool Turn(float setpoint);

	// Activar el intake
	bool Intake(float setpoint);

	// Disparar
	bool Launch();

	// Iniciar
	bool Start();

	// Determinar si recorrió la distancia seleccionada
	bool AtDistance();

	// Determinar si giró el ángulo adecuado
	bool AtAngle();

private:
	// ADIS16448_IMU gyro;
	BuiltInAccelerometer accelerometer;

	// Encoder
	Encoder encoder{sEncoderA, sEncoderB, true, Encoder::EncodingType::k4X};

	// Cámara pixy
	//PixySource source;

	// Chasis
	Drivetrain &chasis;

	// Torre
	//Tower &tower;

	// Disparador
	//Shooter &shooter;

	// Gyro output que controla la velocidad de giro del chasis
	//GyroOutput *turnOutput = new GyroOutput(chasis);

	// Encoder output que controla la velocidad de avance del chasis
	//EncoderOutput *speedOutput = new EncoderOutput(chasis);

	// Controla la velocidad de giro del chasis  según el PID y el giroscopio
	//PIDController turn{kTurnP, kTurnI, kTurnD, &gyro, turnOutput};

	// Controla la velocidad del chasis según el PID y los encoders
	//PIDController speed{kSpeedP, kSpeedI, kSpeedD, &encoder, speedOutput};

	// Comando que prepara el disparador y la torre
	//Prepare *prepare = new Prepare(&shooter, &tower);

	// Comando que dispara
	//Shoot *shoot = new Shoot(&shooter, &tower);

	// Temporizador
	frc::Timer timer;
};
