#include "subsystems/PIDSubsystems/TurnPID.h"

TurnPID::TurnPID(Drivetrain &ch, double kP, double kI, double kD)
	: PIDSubsystem(frc2::PIDController(kP, kI, kD)) // Creamos un controlador llamado m_controller por default, con las variables PID seleccionadas
	  ,
	  chasis{ch} // Indicamos que la variable local chasis es igual al chasis que recibe el controlador
{
	m_controller.SetIntegratorRange(-0.5, 0.5);	   // Indicamos valores de integración para hacerlo más suave
	m_controller.SetTolerance(0.1, 1);			   // Indicamos la tolerancia, 0.1 significa que el error debe ser menor a 0.1 para considerarse en la posición correcta
	m_controller.EnableContinuousInput(-360, 360); // Le indicamos al controlador que el input es continuo
}

// Obtiene la variable de control, que es la lectura del giroscopio
double TurnPID::GetMeasurement()
{
	return chasis.ReadGyro();
}

// Utiliza el output generado por el controlador para hacer el chasis girar
void TurnPID::UseOutput(double output, double setpoint)
{
	chasis.Drive(std::clamp(output, -0.4, 0.4), 0); // Drive recibe un valor de giro y un valor de avance, estamos utilizando el output como el valor de giro, limitado a una velocidad máxima seleccionada
}

// Indica si el controlador ya llegó a la meta
bool TurnPID::AtSetpoint()
{
	return m_controller.AtSetpoint();
}