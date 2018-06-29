/*
 * ADXL345_Accelerometer.c
 *
 *  Created on: 13 Mar 2018
 *      Author: MuhammetTayyip
 */
#include <stdint.h>
#include "Tiva_i2c.h"
#include "ADXL345_Accelerometer.h"
#include <math.h>

void init_ADXL345_Accelerometer(){initI2C1_ADXL345();}

void SetPowerMode(unsigned char powerMode) {
    uint8_t i2c_data = readI2C1_ADXL345(0x53,0x2d);
    if (powerMode==1){
        i2c_data = i2c_data | (powerMode<<3);}
    else if (powerMode==0){
        i2c_data &= ~(1<<3);}
    writeI2C1_ADXL345(0x53,0x2d,i2c_data);
}

int16_t getAcceleration_rawX(){
    uint8_t accelData1, accelData2;
    accelData1=readI2C1_ADXL345(0x53,0x32);
    accelData2=readI2C1_ADXL345(0x53,0x33);
    rawX = (accelData2<<8)|accelData1;
    return (rawX* 0.004 * ADXL345_GRAVITY_EARTH);
}


int16_t getAcceleration_rawY(){
    uint8_t accelData1, accelData2;
    accelData1=readI2C1_ADXL345(0x53,0x34);
    accelData2=readI2C1_ADXL345(0x53,0x35);
    rawY = (accelData2<<8)|accelData1;
    return (rawY* 0.004 * ADXL345_GRAVITY_EARTH);
}

int16_t getAcceleration_rawZ(){
    uint8_t accelData1, accelData2;
    accelData1=readI2C1_ADXL345(0x53,0x36);
    accelData2=readI2C1_ADXL345(0x53,0x37);
    rawZ = (accelData2<<8)|accelData1;
    return (rawZ* 0.004 * ADXL345_GRAVITY_EARTH);
}

int pitchFunction(double X,double Y,double Z){
    return (atan2(X, sqrt(Y*Y + Z*Z))*180.0)/3.1415;}

int rollFunction(double Y,double Z){
    return (atan2(Y, Z)*180.0)/3.1415;}
