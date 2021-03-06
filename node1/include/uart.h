#ifndef UART_H
#define UART_H

/**
* NOTE: The scheema uses a 16 bit packet length, with 15 data bits, and a terminator 
* which uses an EOT (0x04) character
**/

/**
  @brief Send data over UART

  @param data Data to be sent

  @retval 0 if successful, 1 if errors occured
 */
int uart_tx(char data); // Parts are copied from the Atmega162 datasheet!

/**
  @brief Recieve data over UART, fills RX buffer (rx_data)

  @retval 0 if succesful, 1 if error occured
 */
unsigned char uart_rx(void); // Parts are copied from the Atmega162 datasheet!

/**
  @brief Initialize UART 

  @param baud Baudrate of UART transaction
*/
void uart_init(unsigned long baud);

#endif