
#include <frc/smartdashboard/smartdashboard.h>
#include <frc/Timer.h>
#include "Constants.h"
#include "frc2/command/SubsystemBase.h"
#include <rev/CANSparkMax.h>
#include "Constants.h"
#include "frc/XboxController.h"

using namespace frc;
using namespace frc2;
using namespace rev;

class Intake : public SubsystemBase{


    public:
        Intake();

        void Periodic();

        void Reset();

        void Move();
    
    private:

        // Motor del intake
	    CANSparkMax motor{shooterDeviceID, CANSparkMax::MotorType::kBrushed};

	    // Control
	    XboxController control{0};
};
