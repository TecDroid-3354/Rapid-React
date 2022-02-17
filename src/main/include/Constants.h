

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <math.h>

//---------------------------Limelight----------------------------------

constexpr int kObjectiveHeight = 135;
constexpr int kLimelightHeight = 35;
constexpr float kLimelightAngle = 40 * M_PI / 180;
constexpr float kLimelightToFront = 68;

//----------------------------Spark-IDs---------------------------------

constexpr int frontRightDeviceID = 1;
constexpr int frontLeftDeviceID = 2;
constexpr int backRightDeviceID = 3;
constexpr int backLeftDeviceID = 4;
constexpr int shooterDeviceID = 5;
constexpr int feederDeviceID = 6;

//----------------------------PWM Ports---------------------------------

constexpr int pIntake = 0;
constexpr int pTurret = 1;
constexpr int pServoRight = 2;
constexpr int pServoLeft = 3;

//------------------------------DIO Ports----------------------------------

constexpr int pEncoderShooterA = 0;
constexpr int pEncoderShooterB = 1;
constexpr int pEncoderTurretA = 2;
constexpr int pEncoderTurretB = 3;

//------------------------------Speeds----------------------------------

constexpr float kAutoSpeed = 0.4;
constexpr float kFeederSpeed = 1;
constexpr float kIntakeSpeed = 1;
constexpr float kTurretSpeed = 0.5;

//-----------------------------Constants---------------------------------

constexpr double kDistancePerRotation = 3.141592653589 * 6 * 2.54 / 10.71; // PI por diámetro de llanta en pulgadas por cm a in entre la reducción de la caja
constexpr double kP = 0.1;
constexpr double kI = 1e-4;
constexpr double kD = 1;
constexpr double kIz = 0;
constexpr double kFF = 0;
constexpr double kUnitsAxisWidth = 70; // Distancia entre ruedas

//-----------------------------PID Constants---------------------------------

constexpr double kMoveP = 0.1, kMoveI = 0, kMoveD = 0;

constexpr double kTurnP = 0.1, kTurnI = 0, kTurnD = 0.01;

constexpr double kLimeP = 0.1, kLimeI = 0, kLimeD = 0.001;

constexpr double kShooterP = 0, kShooterI = 0, kShooterD = 0;

constexpr double kTurretEncoderP = 0, kTurretEncoderI = 0, kTurretEncoderD = 0;

constexpr double kTurretAlignP = 0, kTurretAlignI = 0, kTurretAlignD = 0;

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