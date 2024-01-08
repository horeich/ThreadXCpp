/**
 * @file                peripheral_pins.h
 * @author              Simon Schrampfer, Andreas Reichle
 * @brief 
 * @version             0.1
 * @date                2021-05-16
 * 
 * @copyright           All rights reserved
 * 
 */

#ifndef PERIPHERAL_PINS_H_
#define PERIPHERAL_PINS_H_

#include "pinmap.h"
#include "peripheral_names.h" // controller specific

#ifdef __cplusplus
extern "C" {
#endif

extern const PinMap PinMap_UART_TX[];
extern const PinMap PinMap_UART_RX[];
extern const PinMap PinMap_UART_RTS[];
extern const PinMap PinMap_UART_CTS[];

#ifdef __cplusplus
}
#endif

#endif // PERIPHERAL_PINS_H_