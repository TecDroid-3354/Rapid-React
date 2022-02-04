#include "subsystems/PIDSubsystems/MovePID.h"

// Controlador PID para avanzar el chasis
MovePID::MovePID(Drivetrain &ch, double kP, double kI, double kD)
	: PIDSubsystem(frc2::PIDController(kP, kI, kD)) // Creamos un controlador llamado m_controller por default, con las variables PID seleccionadas
	  ,
	  chasis{ch} // Indicamos que la variable local chasis es igual al chasis que recibe el controlador
{
	m_controller.SetIntegratorRange(-0.5, 0.5); // Indicamos valores de integración para hacerlo más suave
	m_controller.SetTolerance(0.1, 1);			// Indicamos la tolerancia, 0.1 significa que el error debe ser menor a 0.1 para considerarse en la posición correcta
}

// Obtiene la variable de control, que es el promedio de los encoders
double MovePID::GetMeasurement()
{
	return chasis.GetEncoderAverage();
}

// Utiliza el output generado por el controlador para hacer el chasis avanzar
void MovePID::UseOutput(double output, double setpoint)
{
	chasis.Drive(0, std::clamp(output, -0.4, 0.4)); // Drive recibe un valor de giro y un valor de avance, estamos utilizando el output como el valor de avance, limitado a una velocidad máxima seleccionada
}

// Indica si el controlador ya llegó a la meta
bool MovePID::AtSetpoint()
{
	return m_controller.AtSetpoint();
}