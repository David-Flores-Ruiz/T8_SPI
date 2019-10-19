/*
 * SPI.c
 *
 *  Created on: 17 oct 2019
 *      Author: Lanix
 */

 #include "SPI.h"

void SPI_clk(spi_channel_t channel)
{
	if (SPI_0 == channel) {
		SIM->SCGC6 |= SIM_SCGC6_SPI0_MASK; /* Bit_12 - 0x1000*/
	}
	if (SPI_1 == channel) {
		////
	}
	if (SPI_2 == channel) {
		////
	}
}

void SPI_enable(spi_channel_t channel)
{
	if (SPI_0 == channel) {
		SPI0->MCR &= ~(SPI_MCR_MDIS_MASK);	/* MDIS Bit_14 0b0.. Enables the module clocks */
	}
	if (SPI_1 == channel) {
		////
	}
	if (SPI_2 == channel) {
		////
	}
}

void SPI_set_master(spi_channel_t channel, spi_master_t master_or_slave)
{
	if (SPI_0 == channel) {
		if (SPI_MASTER == master_or_slave) {
			SPI0->MCR |= SPI_MCR_MSTR_MASK; /*MSTR bit_31: 0b1..Enables Master mode */
		}
		if (SPI_SLAVE == master_or_slave) {
			SPI0->MCR &= ~(SPI_MCR_MSTR_MASK); /* MSTR bit_31: 0b0..Enables Slave mode */
		}
	}

	if (SPI_1 == channel) {
		////
	}
	if (SPI_2 == channel) {
		////
	}
}

void SPI_fifo(spi_channel_t channel, spi_enable_fifo_t enable_or_disable)
{
	if (SPI_0 == channel) {
		if (SPI_ENABLE_FIFO == enable_or_disable) {
			SPI0->MCR &= ~(SPI_MCR_DIS_TXF_MASK); /* DIS_TXF bit_13: 0b0..TX FIFO is enabled. */
			SPI0->MCR &= ~(SPI_MCR_DIS_RXF_MASK); /* DIS_RXF bit_12: 0b0..RX FIFO is enabled. */
		}
		if (SPI_DISABLE_FIFO == enable_or_disable) {
			SPI0->MCR |= SPI_MCR_DIS_TXF_MASK; /* DIS_TXF bit_13: 0b1..TX FIFO is disabled. */
			SPI0->MCR |= SPI_MCR_DIS_RXF_MASK; /* DIS_RXF bit_12: 0b1..RX FIFO is disabled. */
		}
	}

	if (SPI_1 == channel) {
		////
	}
	if (SPI_2 == channel) {
		////
	}
}
void SPI_clock_polarity(spi_channel_t channel, spi_polarity_t cpol)/*Exixten dos CPOL en master mode pagina 1455 y en slave mode pagina 1459*/
{
	if (SPI_0 == channel) {
		if (SPI_LOW_POLARITY == cpol) {
			SPI0->CTAR[SPI_CTAR_0] &= ~(SPI_CTAR_CPOL_MASK);
		}
		if (SPI_HIGH_POLARITY == cpol) {
			SPI0->CTAR[SPI_CTAR_0] |= SPI_CTAR_CPOL_MASK;
		}
	}
	if (SPI_1 == channel) {
			////
	}
	if (SPI_2 == channel) {
			////
	}
}
void SPI_clock_phase(spi_channel_t channel, spi_phase_t cpha){
	if (SPI_0 == channel) {
		if (SPI_LOW_PHASE == cpha) {
		SPI0->CTAR[SPI_CTAR_0] &= ~(SPI_CTAR_CPHA_MASK);
		}
		if (SPI_HIGH_PHASE == cpha) {
				SPI0->CTAR[SPI_CTAR_0] |= SPI_CTAR_CPHA_MASK;
		}
	}
		if (SPI_1 == channel) {
				////
		}
		if (SPI_2 == channel) {
				////
		}
}
SPI_baud_rate(spi_channel_t channel, uint32_t baud_rate){
	if (SPI_0 == channel) {
		SPI0->CTAR[SPI_CTAR_0] = baud_rate;//Posiblemente nececite OR (|)
	}
	if (SPI_1 == channel) {
				////
	}
	if (SPI_2 == channel) {
					////
	}
}
/********************Probar Funcion**********************/
SPI_msb_first(spi_channel_t channel, spi_lsb_or_msb_t msb){
	if (SPI_0 == channel) {
		if (SPI_MSB == msb) {
			SPI0->CTAR[SPI_CTAR_0] &= ~(SPI_CTAR_LSBFE_MASK);
			}
		if (SPI_LSM == msb) {
			SPI0->CTAR[SPI_CTAR_0] |= SPI_CTAR_LSBFE_MASK;
			}
	}
	if (SPI_1 == channel) {
					////
	}
	if (SPI_2 == channel) {
					////
		}
}
SPI_frame_size(spi_channel_t channel, uint32_t frame_size){
	if (SPI_0 == channel) {
			SPI0->CTAR[SPI_CTAR_0] |=frame_size;
	}
	if (SPI_1 == channel) {
		////
	}
	if (SPI_2 == channel) {
		////
		}
}
SPI_start_tranference(spi_channel_t channel){
	if (SPI_0 == channel) {
		SPI0->MCR &= ~(SPI_MCR_HALT_MASK);
	}
	if (SPI_1 == channel) {
		////
	}
	if (SPI_2 == channel) {
		////
		}
}
void SPI_stop_tranference(spi_channel_t channel){
if (SPI_0 == channel) {
		SPI0->MCR |= (SPI_MCR_HALT_MASK);
	}
	if (SPI_1 == channel) {
		////
	}
	if (SPI_2 == channel) {
		////
		}
}
uint8_t SPI_tranference(spi_channel_t channel, uint8_t data){
	uint8_t recived_data = 0;
	SPI_start_tranference(channel);
	SPI0->PUSHR=(data)|SPI_PUSHR_EOQ_MASK;
	while((SPI0->SR & SPI_SR_TCF_MASK))
		SPI0->MCR |= (SPI_SR_TCF_MASK);
	recived_data = SPI0->POPR & 0xFF;
	return (recived_data);

}






