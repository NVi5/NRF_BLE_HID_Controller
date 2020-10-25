#ifndef MAIN_H__
#define MAIN_H__

#include "app_twi.h"

// Send TWI transaction
void Twi_send(const app_twi_transaction_t *transaction);
// Send UART string
void App_uart_send_string(uint16_t length, char *p_data);
#endif // MAIN_H__