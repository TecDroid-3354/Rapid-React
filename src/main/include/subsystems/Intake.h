
#include <frc/smartdashboard/smartdashboard.h>
#include <frc/Timer.h>
#include "Constants.h"
#include "frc2/command/SubsystemBase.h"
#include <frc/motorcontrol/VictorSP.h>
#include "Constants.h"
#include "frc/XboxController.h"
#include <frc/motorcontrol/MotorControllerGroup.h>
#include <rev/CANSparkMax.h>

using namespace frc;
using namespace frc2;
using namespace rev;

class Intake : public SubsystemBase
{

public:
	Intake();

	void Periodic();

	void Reset();

	void Move(float speed);

private:
	// Motor del intake
	CANSparkMax motor{intakeDeviceID, CANSparkMax::MotorType::kBrushed};

	// Control
	XboxController control{0};
};
