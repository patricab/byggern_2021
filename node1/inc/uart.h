#ifndef UART_H
#define UART_H

// RX buffer
extern unsigned char rx_data[16];

/**
* NOTE: The scheema uses a 16 bit packet length, with 15 data bits, and a terminator 
* which uses an EOT (0x04) character
**/

/**
  @brief Send data over UART

  @param data Data to be sent

  @retval 0 if successful, 1 if errors occured
 */
int uart_tx(unsigned char data); //taken from the datasheet

/**
  @brief Recieve data over UART, fills RX buffer (rx_data)

  @retval 0 if succesful, 1 if error occured
 */
int uart_rx(void);

/**
  @brief Initialize UART 

  @param baud Baudrate of UART transaction
*/
void uart_init(int baud);

#endif