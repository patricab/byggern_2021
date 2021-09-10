#ifndef UART_H
#define UART_H


/**
  @brief Send data over UART

  @param data Data to be sent

   @retval 0 if successful, 1 if errors occured
 */
int uart_tx(unsigned char data); //taken from the datasheet

/**
 * @brief Recieve data over UART

   @retval unsigned char
 */
unsigned char uart_rx(void);

#endif