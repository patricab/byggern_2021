#include <avr/io.h>
#include <spi.h>
#include <uart.h>

#define DD_MOSI PB5
#define DD_MISO PB6
#define DD_SCK PB7
#define DD_SS PB4
#define DDR_SPI DDRB

void spi_init(void)
    {
        /* Set MOSI and SCK output, all others input */
        DDR_SPI = (1<<DD_SS)|(1<<DD_MOSI)|(1<<DD_SCK);
        /* Enable SPI, Master, set clock rate fck/16 */
        SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
    }

void spi_transmit(char cData)
    {
        /* Start transmission */
        SPDR = cData;
        /* Wait for transmission complete */
        while(!(SPSR & (1<<SPIF)));
    }

uint8_t spi_read(void)
    {
        // Send dummy-byte
        SPDR = 0x00;
        // Wait for transmission complete
        while(!(SPSR & (1<<SPIF)));
        return SPDR;
    }
