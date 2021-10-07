#ifndef SPI_H
#define SPI_H

void spi_init(void);

void spi_transmit(char cData);

uint8_t spi_read(void);

#endif