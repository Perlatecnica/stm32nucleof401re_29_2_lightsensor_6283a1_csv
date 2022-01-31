/* Copyright (c) 2022 Perlatecnica
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/****************************************************
*            RAPID PROTOTYPING WITH NUCLEO          *
* Example Code 00: Light sensor 6283A1              *
* Author: Mauro D'Angelo                            *
* Organization: Perlatecnica APS ETS				*
*****************************************************/
//#define CSV



#include "mbed.h"
#include "LightSensor.h"

// It creates an instance of the DigitalOut class.
// myled is the name of the variable (instance).
// The instance shall 'point' to the pin LED1, that is the led on the board
DigitalOut myled(LED1);

UnbufferedSerial pc(USBTX, USBRX);

// it gets the instance of Light Sensor driver
LightSensor* ls = LightSensor::getInstance();
uint32_t* buffer;

void printcsv(){
	printf("%lu,%lu,%lu,%lu,%lu,%lu\r\n", (unsigned long)buffer[0],(unsigned long)buffer[1],(unsigned long)buffer[2],(unsigned long)buffer[3],(unsigned long)buffer[4],(unsigned long)buffer[5]);
}

// Entry point
int main() {
	pc.baud(115200);
	buffer = ls->getBuffer();

	// Print CSV head
    printf("RED,VISIBLE,BLUE,GREEN,IR,CLEAR\r\n");

    while(true){
    	ls->updateValues();
    	printcsv();
    	ThisThread::sleep_for(200ms);
    }
}


