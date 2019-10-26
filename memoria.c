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

//#define DEBUG_ON				/* Para proposito de DEBUG */

#ifdef DEBUG_ON
	#include <stdio.h>
#endif

#define mem_IMG1 &IMAGE_1[0]
#define mem_IMG2 &IMAGE_2[0]
#define mem_IMG3 &IMAGE_3[0]
#define mem_IMG4 &IMAGE_4[0]
#define mem_IMG5 &IMAGE_5[0]

/* Para mandar el comando Read a la memoria y después los 3 bytes de direcciones */
uint32_t full_address  = 0x00000000;
uint8_t  dirByte1	=  0x00;
uint8_t  dirByte2	=  0x00;
uint8_t  dirByte3	=  0x00;

uint8_t  IMAGE_1[MAX] = {0}; /* Imagen garabada en memoria 0x7000 */
uint8_t  IMAGE_2[MAX] = {0}; /* Imagen garabada en memoria 0x8000 */
uint8_t  IMAGE_3[MAX] = {0}; /* Imagen garabada en memoria 0x9000 */
uint8_t  IMAGE_4[MAX] = {0}; /* Imagen garabada en memoria 0xA000 */
uint8_t  IMAGE_5[MAX] = {0}; /* Imagen garabada en memoria 0xB000 */

uint32_t g_dir_Img1  = 0x007000;
uint32_t g_dir_Img2  = 0x008000;
uint32_t g_dir_Img3  = 0x009000;
uint32_t g_dir_Img4  = 0x00A000;
uint32_t g_dir_Img5  = 0x00B000;

void memoria_READ_IMAGEN(const uint8_t bitmap[]){
	uint16_t index = 0;
	mem_Imagenes_t Imagen;

	if (bitmap == memoria_IMG1())
		Imagen = IMG_1;
	if (bitmap == memoria_IMG2())
		Imagen = IMG_2;
	if (bitmap == memoria_IMG3())
		Imagen = IMG_3;
	if (bitmap == memoria_IMG4())
		Imagen = IMG_4;
	if (bitmap == memoria_IMG5())
		Imagen = IMG_5;

  for (index = 0 ; index < MAX; index++)
	  memoria_READ_byte( LCD_CMD, 0x03, Imagen);
}

uint8_t* memoria_IMG1 (void)
{
	uint8_t* ptr_IMG1 = mem_IMG1;
	return (ptr_IMG1);
}

uint8_t* memoria_IMG2 (void)
{
	uint8_t* ptr_IMG2 = mem_IMG2;
	return (ptr_IMG2);
}

uint8_t* memoria_IMG3 (void)
{
	uint8_t* ptr_IMG3 = mem_IMG3;
	return (ptr_IMG3);
}

uint8_t* memoria_IMG4 (void)
{
	uint8_t* ptr_IMG4 = mem_IMG4;
	return (ptr_IMG4);
}

uint8_t* memoria_IMG5 (void)
{
	uint8_t* ptr_IMG5 = mem_IMG5;
	return (ptr_IMG5);
}

void memoria_READ_byte(uint8_t data_or_command, uint8_t data, mem_Imagenes_t Image )
{
	uint8_t DATA_read;
	static uint16_t index = 0;
	static boolean_t flag_1 = FALSE;
	static boolean_t flag_2 = FALSE;
	static boolean_t flag_3 = FALSE;
	static boolean_t flag_4 = FALSE;
	static boolean_t flag_5 = FALSE;

	switch (Image)
	{
		case IMG_1:
			if (flag_1 == FALSE) {
				full_address = g_dir_Img1;
			}
			dirByte1 = (full_address >> 0 ) & (0xFF); // Byte LOW
			dirByte2 = (full_address >> 8 ) & (0xFF);
			dirByte3 = (full_address >> 16) & (0xFF); // Byte HIGH

			flag_1 = TRUE;
			break;	// end case

		case IMG_2:
			if (flag_2 == FALSE) {
				full_address = g_dir_Img2;
			}
			dirByte1 = (full_address >> 0 ) & (0xFF); // Byte LOW
			dirByte2 = (full_address >> 8 ) & (0xFF);
			dirByte3 = (full_address >> 16) & (0xFF); // Byte HIGH

			flag_2 = TRUE;
			break;	// end case

		case IMG_3:
			if (flag_3 == FALSE) {
				full_address = g_dir_Img3;
			}
			dirByte1 = (full_address >> 0 ) & (0xFF); // Byte LOW
			dirByte2 = (full_address >> 8 ) & (0xFF);
			dirByte3 = (full_address >> 16) & (0xFF); // Byte HIGH

			flag_3 = TRUE;
			break;	// end case

		case IMG_4:
			if (flag_4 == FALSE) {
				full_address = g_dir_Img4;
			}
			dirByte1 = (full_address >> 0 ) & (0xFF); // Byte LOW
			dirByte2 = (full_address >> 8 ) & (0xFF);
			dirByte3 = (full_address >> 16) & (0xFF); // Byte HIGH

			flag_4 = TRUE;
			break;	// end case

		case IMG_5:
			if (flag_5 == FALSE) {
				full_address = g_dir_Img5;
			}
			dirByte1 = (full_address >> 0 ) & (0xFF); // Byte LOW
			dirByte2 = (full_address >> 8 ) & (0xFF);
			dirByte3 = (full_address >> 16) & (0xFF); // Byte HIGH

			flag_5 = TRUE;
			break;	// end case

		default:
			break;
	}	//end switch (Image)

	GPIO_clear_pin(GPIO_D, CS_mem);

	if(data_or_command)
		GPIO_set_pin(GPIO_D, DATA_OR_CMD_PIN);
	else
		GPIO_clear_pin(GPIO_D, DATA_OR_CMD_PIN);

	SPI_start_tranference(SPI_0);
	DATA_read = SPI_tranference(SPI_0, data);	// Comando READ
	DATA_read = SPI_tranference(SPI_0, dirByte3);	// MSB de direccion
	DATA_read = SPI_tranference(SPI_0, dirByte2);
	DATA_read = SPI_tranference(SPI_0, dirByte1);	// LSB de direccion
	DATA_read = SPI_tranference(SPI_0, 0x00);		// Recibir el dato
	SPI_stop_tranference(SPI_0);

	GPIO_set_pin(GPIO_D, CS_mem);

	if (index >= MAX){
		index = 0;	// Inicia a rellenar un nuevo arreglo de Imagen
	}

	if ((index >= 0) && (index < MAX)) {
		if (Image == IMG_1)
			IMAGE_1[index] = DATA_read;
		if (Image == IMG_2)
			IMAGE_2[index] = DATA_read;
		if (Image == IMG_3)
			IMAGE_3[index] = DATA_read;
		if (Image == IMG_4)
			IMAGE_4[index] = DATA_read;
		if (Image == IMG_5)
			IMAGE_5[index] = DATA_read;

#ifdef DEBUG_ON
		printf(" \n%x - 0x7000[%d]", IMAGE_1[index], index);
#endif

	}

	index++; //** Apuntar al siguiente elemento del arreglo de forma correspondiente */
	full_address++; //** Apuntar a la siguiente dirección de memoria */
}

