/*
 * memoria_S25FL132K.c
 *
 *  Created on: 20 oct 2019
 *      Author: pacas
 */
/* #include "memoria.h"
#include "GPIO.h"
#include "SPI.h"

void MEMORIA_cs(memoria_enable_cs CS){
	if (CS == MEMORIA_DISABLE_CS) {
	GPIO_clear_pin(GPIO_D, CS_PIN);
	}
	if (CS == MEMORIA_ENABLE_CS) {
		GPIO_clear_pin(GPIO_D, CS_PIN);
	}
void memoria_read()
void memoria_write_byte(uint8_t command, uint32_t direccion){
	MEMORIA_cs(MEMORIA_DISABLE_CS);
	SPI_start_tranference(SPI_0);
	SPI_tranference(SPI_0, COMMAND);
	SPI_tranference(SPI_0, direccion);
}
*/
