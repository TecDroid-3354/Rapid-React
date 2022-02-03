

#ifndef CONSTANTS_H
#define CONSTANTS_H

//----------------------------Ports----------------------------------
    
    //constexpr int mChasisFrontRight = 0;
    //constexpr int mChasisBackRight = 7;
    //constexpr int mChasisFrontLeft = 1;
    //constexpr int mChasisBackLeft = 6;
    constexpr int mIntake = 0;
    constexpr int mShooter = 4;
    constexpr int mElevator = 5;
    constexpr int mClimber = 3;
    constexpr int mBalancer = 2;
    //constexpr int mIntake = 1;
    constexpr int pStopperFront = 1;
    constexpr int pStopperBack = 2;
    constexpr int pIntakeFront = 7;
    constexpr int pIntakeBack = 6;

//---------------------------Limelight----------------------------------

	constexpr int kObjectiveHeight = 135;
	constexpr int kLimelightHeight = 35;
	constexpr float kLimelightAngle = 40*M_PI/180;
    constexpr float kLimelightToFront = 68;


//----------------------------Spark-IDs---------------------------------

  
    static const int frontRightDeviceID = 1;
    static const int frontLeftDeviceID = 2;
    static const int backRightDeviceID = 3;
    static const int backLeftDeviceID = 4;


//------------------------------Speeds----------------------------------


    constexpr float kPanelSpeed = 1;
    constexpr float kAutoSpeed = 0.7;
    constexpr float kAutoTurn = 0.7;
    constexpr float kAutoBalance = 0.7;
    constexpr float kShooterSpeed = 1;
    constexpr float kTowerSpeed = 1;
    constexpr float kIntakeSpeed = 1;
    constexpr float kClimberSpeed = 0.6;
    constexpr float kSliderSpeed = 1;
    constexpr float kElevatorSpeed = 1;


//------------------------------Sensors----------------------------------

    constexpr int sPanelSwitch = 0;
    constexpr int sElevatorSwitch = 1;
    constexpr int sEncoderA  = 8;
    constexpr int sEncoderB = 9;
    constexpr int sPixy = 2;

//-----------------------------Constants---------------------------------

    constexpr int kPanelHits = 10;
    constexpr float  kPrepareTime = 0.2;
    constexpr float  kShootTime = 4;
    constexpr float  kChargeTime = 1.5;
    constexpr double kDistancePerRotation = 3.141592653589*6*2.54/10.71; //PI por diámetro de llanta en pulgadas por cm a in entre la reducción de la caja
    

//-------------------------------Auto-------------------------------------

    constexpr float kMaxOutput = 0.4;
    constexpr float kMinOutput = -0.4;
    
//---------------------------Control Map---------------------------------

    constexpr int cButtonA = 1;
    constexpr int cButtonB = 2;
    constexpr int cButtonX = 3;
    constexpr int cButtonY = 4;
    constexpr int cLeftBumper = 5;
    constexpr int cRightBumper = 6;
    constexpr int cSelect = 7;
    constexpr int cStart = 8;
    
    constexpr int cLeftAxisX = 0;
    constexpr int cLeftAxisY = 1;
    constexpr int cLeftTrigger = 2;
    constexpr int cRightTrigger = 3;
    constexpr int cRightAxisX = 4;
    constexpr int cRightAxisY = 5;
    

#endif