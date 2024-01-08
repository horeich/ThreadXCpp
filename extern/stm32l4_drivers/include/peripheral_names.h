/**
 * @file                peripheral_names.h
 * @author              Simon Schrampfer, Andreas Reichle
 * @brief 
 * @version             0.1
 * @date                2021-05-16
 * 
 * @copyright           All rights reserved
 * 
 */

#ifndef PERIPHERAL_NAMES_H_
#define PERIPHERAL_NAMES_H_

//#include "cmsis.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    UART_1 = (int)USART1_BASE,
    UART_2 = (int)USART2_BASE,
#if defined USART3_BASE
    UART_3 = (int)USART3_BASE,
#endif
#if defined UART4_BASE
    UART_4 = (int)UART4_BASE,
#endif
#if defined UART5_BASE
    UART_5 = (int)UART5_BASE,
#endif
    LPUART_1 = (int)LPUART1_BASE,
} UARTName;

#ifdef __cplusplus
}
#endif

#endif // PERIPHERAL_NAMES_H_