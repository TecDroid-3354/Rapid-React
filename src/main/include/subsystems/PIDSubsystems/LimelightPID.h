#include <frc2/command/PIDSubsystem.h>
#include "Constants.h"
#include "subsystems/Drivetrain.h"

class LimelightPID : public PIDSubsystem
{
public:
	// El controlador recibe el subsistema que va a controlar y las variables PID
	LimelightPID(Drivetrain &, double, double, double);

	// Obtiene la variable de control
	double GetMeasurement() override;

	// Utiliza el resultado del cálculo PID
	void UseOutput(double output, double setpoint) override;

	// Indica si ya se llegó a la meta
	bool AtSetpoint();

private:
	Drivetrain &chasis;
};
