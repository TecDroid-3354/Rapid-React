
#pragma once

#include "Constants.h"
#include "frc/XboxController.h"
#include "frc/drive/DifferentialDrive.h"
#include "frc2/command/SubsystemBase.h"
#include <frc/ADIS16448_IMU.h>
#include <frc/motorcontrol/MotorControllerGroup.h>
#include <rev/CANSparkMax.h>

using namespace frc2;
using namespace rev;
using namespace frc;

class Drivetrain;

// Clase para manejar el chasis
class Drivetrain : public SubsystemBase
{

public:
	Drivetrain();

	// Función que ocurre todo el tiempo
	void Periodic() override;

	// Resetear los motores
	void Reset();

	void ResetGyro();

	void ResetEncoders();

	// Manejar según el control
	void Drive();

	// Manejar según valores específicos
	void Drive(float, float);

	// Activar/Desactivar seguridad
	void SetSafetyEnabled(bool);

	// Obtener el promedio de los cuatro encoders
	float GetEncoderAverage();

	float ReadRightEncoders();

	float ReadLeftEncoders();

	// Leer el valor del giroscopio
	float ReadGyroDeg();

private:
	// -------------------------------------- Motores ----------------------------------------------------
	// Motor frente derecho
	CANSparkMax frontRight{frontRightDeviceID, CANSparkMax::MotorType::kBrushless};

	// Motor frente izquierdo
	CANSparkMax frontLeft{frontLeftDeviceID, CANSparkMax::MotorType::kBrushless};

	// Motor trasero derecho
	CANSparkMax backRight{backRightDeviceID, CANSparkMax::MotorType::kBrushless};

	// Motor trasero izquierdo
	CANSparkMax backLeft{backLeftDeviceID, CANSparkMax::MotorType::kBrushless};

	// Controlador de motores derechos
	// Esto se hace para que dos motores hagan el mismo movimiento
	MotorControllerGroup right{frontRight, backRight};

	// Controlador de motores izquierdos
	MotorControllerGroup left{frontLeft, backLeft};

	// Objeto de control diferencial
	DifferentialDrive chasis{right, left};

	// -------------------------------------- Sensores ----------------------------------------------------
	// Encoder frente derecho
	SparkMaxRelativeEncoder encoderFrontRight{frontRight.GetEncoder()};

	// Encoder frente izquierdo
	SparkMaxRelativeEncoder encoderFrontLeft{frontLeft.GetEncoder()};

	// Encoder trasero derecho
	SparkMaxRelativeEncoder encoderBackRight{backRight.GetEncoder()};

	// Encoder trasero izquierdo
	SparkMaxRelativeEncoder encoderBackLeft{backLeft.GetEncoder()};

	// Giroscopio
	ADIS16448_IMU gyro;

	// Control
	XboxController control{0};

	// indicadores para climbmode
	bool flag = true;
	bool climbMode = false;

	// indicadores para sensormode
	bool flag2 = false;
	bool sensorMode = true;
};
