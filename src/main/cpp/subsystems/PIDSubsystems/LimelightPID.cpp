#include "subsystems/PIDSubsystems/LimelightPID.h"

LimelightPID::LimelightPID(Drivetrain &ch, double kP, double kI, double kD)
	: PIDSubsystem(frc2::PIDController(kP, kI, kD)), chasis{ch}
{
	m_controller.EnableContinuousInput(-45, 45);
	m_controller.SetIntegratorRange(-0.5, 0.5);
	m_controller.SetTolerance(0.1, 1);
}

double LimelightPID::GetMeasurement()
{
	/*std::shared_ptr<nt::NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
	return table.Get("tx",0.0);*/
	return 0;
}

void LimelightPID::UseOutput(double output, double setpoint)
{
	chasis.Drive(0, std::clamp(output, -0.3, 0.3));
}

bool LimelightPID::AtSetpoint()
{
	return m_controller.AtSetpoint();
}