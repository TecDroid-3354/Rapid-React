
#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/motorcontrol/VictorSP.h>
#include "frc/Timer.h"
#include "frc/Encoder.h"
#include "Constants.h"
#include "frc/drive/DifferentialDrive.h"
#include "frc/XboxController.h"
#include <frc/BuiltInAccelerometer.h>
#include <frc/SpeedControllerGroup.h>
#include <frc/SerialPort.h>
#include <frc/controller/PIDController.h>
#include <rev/SparkMaxPIDController.h>
#include <rev/CANSparkMax.h>

using namespace frc;
using namespace rev;

// Clase para manejar el chasis
class Drivetrain : public frc2::SubsystemBase
{
public:
	Drivetrain();

	// Función que ocurre todo el tiempo
	void Periodic() override;

	//Resetear los motores
	void Reset();

	// Manejar según el control
	void Drive();

	// Manejar según valores específicos
	void Drive(float y, float x);

	// Activar/Desactivar seguridad
	void SetSafetyEnabled(bool state);

	// Alinear
	void Align(float speed);

	

private:

	// Motor frente derecho
	CANSparkMax frontRight{frontRightDeviceID, CANSparkMax::MotorType::kBrushless};

	// Motor frente izquierdo
	CANSparkMax frontLeft{frontLeftDeviceID, CANSparkMax::MotorType::kBrushless};

	// Motor trasero derecho
	CANSparkMax backRight{backRightDeviceID, CANSparkMax::MotorType::kBrushless};

	// Motor trasero izquierdo
	CANSparkMax backLeft{backLeftDeviceID, CANSparkMax::MotorType::kBrushless};

	SparkMaxRelativeEncoder encoderFrontRight{frontRight.GetEncoder()};

	SparkMaxRelativeEncoder encoderFrontLeft{frontLeft.GetEncoder()};

	SparkMaxRelativeEncoder encoderBackRight{backRight.GetEncoder()};

	SparkMaxRelativeEncoder encoderBackLeft{backLeft.GetEncoder()};

	SparkMaxPIDController PIDFrontRight{frontRight.GetPIDController()};

	SparkMaxPIDController PIDFrontLeft{frontRight.GetPIDController()};

	SparkMaxPIDController PIDFrontRIght{frontRight.GetPIDController()};

	SparkMaxPIDController PIDFrontRIght{frontRight.GetPIDController()};

	// Controlador de motores derechos
	// Esto se hace para que dos motores hagan el mismo movimiento
	SpeedControllerGroup right{frontRight, backRight};

	// Controlador de motores izquierdos
	SpeedControllerGroup left{frontLeft, backLeft};

	// Control
	XboxController control{0};

	// Objeto de control diferencial
	DifferentialDrive chasis{right, left};

	bool flag = true;

	// Control de modo de escalada
	bool climbMode = false;
};
