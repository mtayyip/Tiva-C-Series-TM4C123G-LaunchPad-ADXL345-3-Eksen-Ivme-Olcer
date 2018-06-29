/*
 * Tiva_i2c.h
 *
 *  Created on: 13 Mar 2018
 *      Author: MuhammetTayyip
 */

#ifndef TIVA_I2C_H_
#define TIVA_I2C_H_


void initI2C1_ADXL345(void);
uint8_t readI2C1_ADXL345(uint16_t device_address, uint16_t device_register);
void writeI2C1_ADXL345(uint16_t device_address, uint16_t device_register, uint8_t device_data);


#endif /* TIVA_I2C_H_ */
