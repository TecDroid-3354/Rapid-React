
/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Elevator.h"
#include "Constants.h"
#include <frc/smartdashboard/smartdashboard.h>

using namespace frc;
using namespace std;
using namespace nt;

Elevator::Elevator()
{
    bool TopSwitch = limitTop.Get();
    bool BottomSwitch = limitBottom.Get();

    SmartDashboard::PutBoolean("Top Switch", TopSwitch);
    SmartDashboard::PutBoolean("Bottom Switch", BottomSwitch);
    // rightArm.SetInverted(false);
    // leftArm.SetInverted(true);
}

void Elevator::Periodic()
{

    bool climbMode = SmartDashboard::GetBoolean("Climb Mode", false);
    if (climbMode)
    {
        Elevate(control.GetRawAxis(cRightTrigger) - control.GetRawAxis(cLeftTrigger));
        /*
        if (!limitTop.Get() && control.GetRawAxis(cLeftTrigger) > 0)
        {
            Elevate(control.GetRawAxis(cRightTrigger) - control.GetRawAxis(cLeftTrigger));
        }
        else
        {
            Elevate(0);
        }

        if (!limitBottom.Get() && control.GetRawAxis(cRightTrigger) > 0)
        {
            Climb(control.GetRawAxis(cRightTrigger) * kElevatorSpeed);
        }
        else
        {
            Climb(0);
        }
        */

        bool climbMode = SmartDashboard::GetBoolean("Climb Mode", false);
        if (climbMode)
        {
            MoveArms(kArmsSpeed);
        }
    }
}

void Elevator::Reset()
{
}

void Elevator::Elevate(float speed)
{
    elevator.Set(speed);
}

void Elevator::Climb(float speed)
{
    elevator.Set(-speed);
}

void Elevator::MoveArms(float speed)
{
    rightArm.Set((-control.GetRawButton(cRightBumper) + control.GetRawButton(cLeftBumper)) * kTurretSpeed);
    leftArm.Set((-control.GetRawButton(cRightBumper) + control.GetRawButton(cLeftBumper)) * kTurretSpeed);
}