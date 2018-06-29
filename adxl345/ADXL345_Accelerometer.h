/*
 * ADXL345_Accelerometer.h
 *
 *  Created on: 13 Mar 2018
 *      Author: MuhammetTayyip
 */

#ifndef ADXL345_ACCELEROMETER_H_
#define ADXL345_ACCELEROMETER_H_

#define ADXL345_GRAVITY_EARTH  9.80665

int16_t rawX,rawY, rawZ;
void init_ADXL345_Accelerometer(void);
void SetPowerMode(unsigned char powerMode);
int16_t getAcceleration_rawX();
int16_t getAcceleration_rawY();
int16_t getAcceleration_rawZ();
int pitchFunction(double X,double Y,double Z);
int rollFunction(double Y,double Z);
#endif /* ADXL345_ACCELEROMETER_H_ */
