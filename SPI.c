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
			SPI0->CTAR[0] &= ~(SPI_CTAR_CPOL_MASK);
		}
		if (SPI_HIGH_POLARITY == cpol) {
			SPI0->CTAR[0] |= SPI_CTAR_CPOL_MASK;
		}
	}
		if (SPI_1 == channel) {
			////
		}
		if (SPI_2 == channel) {
			////
		}
}






