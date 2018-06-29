/*
 * Tiva_i2c.c
 *
 *  Created on: 13 Mar 2018
 *      Author: MuhammetTayyip
 */
#include <stdint.h>
#include <stdbool.h>
#include "Tiva_i2c.h"
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_i2c.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/i2c.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"

//A6-->SCL I2C1
//A7-->SDA I2C1

void initI2C1_ADXL345(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C1);
    SysCtlPeripheralReset(SYSCTL_PERIPH_I2C1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinConfigure(GPIO_PA6_I2C1SCL);
    GPIOPinConfigure(GPIO_PA7_I2C1SDA);
    GPIOPinTypeI2CSCL(GPIO_PORTA_BASE, GPIO_PIN_6);
    GPIOPinTypeI2C(GPIO_PORTA_BASE, GPIO_PIN_7);
    I2CMasterInitExpClk(I2C1_BASE, SysCtlClockGet(), false);
    HWREG(I2C1_BASE + I2C_O_FIFOCTL) = 80008000;
}

uint8_t readI2C1_ADXL345(uint16_t device_address, uint16_t device_register)
{
    I2CMasterSlaveAddrSet(I2C1_BASE, device_address, false);
    I2CMasterDataPut(I2C1_BASE, device_register);
    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_SINGLE_SEND);
    while(I2CMasterBusy(I2C1_BASE));
    I2CMasterSlaveAddrSet(I2C1_BASE, device_address, true);
    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE);
    while(I2CMasterBusy(I2C1_BASE));
    return( I2CMasterDataGet(I2C1_BASE));
}

void writeI2C1_ADXL345(uint16_t device_address, uint16_t device_register, uint8_t device_data)
{
    I2CMasterSlaveAddrSet(I2C1_BASE, device_address, false);
    I2CMasterDataPut(I2C1_BASE, device_register);
    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_START);
    while(I2CMasterBusy(I2C1_BASE));
    I2CMasterDataPut(I2C1_BASE, device_data);
    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);
    while(I2CMasterBusy(I2C1_BASE));
}
