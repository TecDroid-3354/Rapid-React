#include "subsystems/Intake.h"
#include <frc/smartdashboard/smartdashboard.h>
#include <frc/Timer.h>
#include "Constants.h"
using namespace frc;

Intake::Intake(){

};

void Intake::Periodic()
{
	Move(control.GetRightAxisX())
}

void Intake::Reset()
{
}

void Intake::Move(float speed)
{
	motor.Set(speed * kIntakeSpeed);
}
