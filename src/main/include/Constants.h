

#ifndef CONSTANTS_H
#define CONSTANTS_H


#include <math.h>



//---------------------------Limelight----------------------------------

constexpr int kObjectiveHeight = 135;
constexpr int kLimelightHeight = 35;
constexpr float kLimelightAngle = 40 * M_PI / 180;
constexpr float kLimelightToFront = 68;

//----------------------------Spark-IDs---------------------------------

static const int frontRightDeviceID = 1;
static const int frontLeftDeviceID = 2;
static const int backRightDeviceID = 3;
static const int backLeftDeviceID = 4;
static const int shooterDeviceID = 5;

//------------------------------Speeds----------------------------------

constexpr float kAutoSpeed = 0.4;

//-----------------------------Constants---------------------------------

constexpr double kDistancePerRotation = 3.141592653589 * 6 * 2.54 / 10.71; // PI por diámetro de llanta en pulgadas por cm a in entre la reducción de la caja
constexpr double kP = 0.1;
constexpr double kI = 1e-4;
constexpr double kD = 1;
constexpr double kIz = 0;
constexpr double kFF = 0;



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