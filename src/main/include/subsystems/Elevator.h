#pragma once
#include <frc/smartdashboard/smartdashboard.h>
#include <frc/Timer.h>
#include "Constants.h"
#include "frc2/command/SubsystemBase.h"
#include <frc/motorcontrol/VictorSP.h>
#include "frc/XboxController.h"
#include <frc/motorcontrol/MotorControllerGroup.h>
#include "frc/DigitalInput.h"
#include <frc/motorcontrol/MotorControllerGroup.h>
#include <rev/CANSparkMax.h>

using namespace frc;
using namespace frc2;
using namespace rev;

class Elevator : public SubsystemBase
{

public:
    Elevator();

    void Periodic();

    void Reset();

    // Subir elevador
    void Elevate(float speed);

    // Subir robot
    void Climb(float speed);

    void MoveArms(float speed);

private:
    // Motor del elevador
    VictorSP elevator{pElevator};

    // Motores de los brazos

    CANSparkMax rightArm{rightArmDeviceID, CANSparkMax::MotorType::kBrushed};
    CANSparkMax leftArm{leftArmDeviceID, CANSparkMax::MotorType::kBrushed};

    MotorControllerGroup arms{rightArm, leftArm};

    // Limit Switch que detecta si el elevador ha llegado a su límite
    DigitalInput limitTop{sElevatorSwitchTop};
    DigitalInput limitBottom{sElevatorSwitchBottom};

    // Control
    XboxController control{0};
};
