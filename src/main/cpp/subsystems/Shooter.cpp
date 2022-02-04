#include "subsystems/Shooter.h"

#include "Constants.h"
using namespace frc;

Shooter::Shooter() {

  
}

void Shooter::Periodic() {
    SetMotor(control.GetRightTriggerAxis());
}

 
  
void Shooter::SetMotor(float speed){
  motor.Set(speed);
}
