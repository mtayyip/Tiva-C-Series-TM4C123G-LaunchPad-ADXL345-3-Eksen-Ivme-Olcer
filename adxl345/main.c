/*
 * main.c
 *  Created on: 29 Haziran 2018
 *      Author: Muhammet Tayyip Çankaya
 */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"

#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/debug.h"
#include "driverlib/sysctl.h"
#include "ADXL345_Accelerometer.h"

//A6-->SCL I2C1
//A7-->SDA I2C1

int main (void)
{
    double accelerationX, accelerationY, accelerationZ;
    int pitch=0,roll=0;
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE,GPIO_PIN_2);

    init_ADXL345_Accelerometer();
    SetPowerMode(0x01);

    while(1){
        accelerationX = getAcceleration_rawX();
        accelerationY = getAcceleration_rawY();
        accelerationZ = getAcceleration_rawZ();

        pitch = pitchFunction(accelerationX,accelerationY,accelerationZ);
        roll  = rollFunction(accelerationY,accelerationZ);


        /*if(pitch>=85 || pitch<=-85 || roll>=90 || roll<=-95){//öne veya arkaya kaza icin
            GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_2,4);
            SysCtlDelay(SysCtlClockGet()/2);}

        GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_2,0);*/
        if(pitch>=45 || pitch<=-45 ){
            if(pitch<=-45)
                 printf("Arkaya Dogru Egim\n");
            else
                 printf("One Dogru Egim\n");
        }

        else if(roll>=45 || roll<=-45){//saga veya sola kaza icin
             if(roll<=-45)
                 printf("Saga Dogru Egim\n");
             else
                 printf("Sola Dogru Egim\n");
        }
    }
    return 0;
}

