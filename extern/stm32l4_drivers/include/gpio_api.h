/**
 * @file            gpio_api.h
 * @author          Simon Schrampfer, Andreas Reichle
 * @brief 
 * @version         0.1
 * @date            2021-04-12
 * 
 * @copyright       All rights reserved
 * 
 */

#ifndef GPIO_API_H_
#define GPIO_API_H_

#include <stdint.h>
#include "pinmap.h"
#include "gpio_object.h"

#ifdef __cplusplus
extern "C" {
#endif

// Init functions (consider outsource these in rtos_gpio.c to improve readability)
// ******************************************************************************************

void gpio_init_inout(gpio_t* gpio, PinName pin, PinDirection direction, PinMode mode, int value);

void gpio_init_out_ex(gpio_t *gpio, PinName pin, int value);

void gpio_init_in_ex(gpio_t *gpio, PinName pin, PinMode mode);

void gpio_init_in(gpio_t *gpio, PinName pin);

void gpio_init_out(gpio_t *gpio, PinName pin);

// API functions
// ******************************************************************************************

void gpio_mode(gpio_t *obj, PinMode mode);

void gpio_dir(gpio_t *obj, PinDirection direction);

// HAL init functions
// ******************************************************************************************

void gpio_init(gpio_t *obj, PinName pin);

uint32_t gpio_set(PinName pin);

GPIO_TypeDef *Set_GPIO_Clock(uint32_t port_idx);

#ifdef __cplusplus
}
#endif

#endif // GPIO_API_H_