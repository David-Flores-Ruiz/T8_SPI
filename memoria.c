/*
 * memoria.c
 *
 *  Created on: 21 oct 2019
 *      Author: Lanix
 */


#include "memoria.h"
#include "LCD_nokia.h"
#include "GPIO.h"
#include "SPI.h"
#include "stdint.h"
#include "Bits.h"

uint8_t Img_1[MAX] = {0}; /* Led Zepellin */


void memoria_READ_IMAGEN(const uint8_t bitmap[]){
	uint16_t index = 0;
  for (index = 0 ; index < MAX; index++)
	  memoria_READ_byte( LCD_CMD, 0x03, 0x00, 0x70, 0x00);
}

void memoria_READ_byte(uint8_t data_or_command, uint8_t data, uint8_t dir1, uint8_t dir2, uint8_t dir3)
{
	uint8_t DATA;
	static uint16_t index = 0;

	GPIO_clear_pin(GPIO_D, CS1);
	//LCD_nokia_delay();

	if(data_or_command)
		GPIO_set_pin(GPIO_D, DATA_OR_CMD_PIN);
	else
		GPIO_clear_pin(GPIO_D, DATA_OR_CMD_PIN);

	SPI_start_tranference(SPI_0);

	SPI_tranference(SPI_0, data);	// Comando READ
	SPI_tranference(SPI_0, dir1);	// 3 Bytes de direccion
	SPI_tranference(SPI_0, dir2);
	DATA = SPI_tranference(SPI_0, dir3);

	SPI_stop_tranference(SPI_0);

	//	GPIO_set_pin(GPIO_D, CS1);

	if ((index >= 0) && (index < MAX)) {
		Img_1[index] = DATA;
	}

	index++; //** Apuntar al siguiente elemento del arreglo de forma correspondiente */

}


