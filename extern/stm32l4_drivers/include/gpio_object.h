/**
 * @file                gpio_object.h
 * @author              Simon Schrampfer, Andreas Reichle
 * @brief 
 * @version             0.1
 * @date                2021-05-16
 * 
 * @copyright           All rights reserved
 * 
 */

#ifndef GPIO_OBJECT_H_
#define GPIO_OBJECT_H_

#include "pin_names.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint32_t mask;
    __IO uint32_t *reg_in;
    __IO uint32_t *reg_set;
    __IO uint32_t *reg_clr;
    PinName  pin;
    GPIO_TypeDef *gpio;
    uint32_t ll_pin;
} gpio_t;

static inline void gpio_write(gpio_t *obj, int value)
{
    if (value) {
        *obj->reg_set = obj->mask;
    } else {
#ifdef GPIO_IP_WITHOUT_BRR
        *obj->reg_clr = obj->mask << 16;
#else
        *obj->reg_clr = obj->mask;
#endif
    }
}

static inline int gpio_read(gpio_t *obj)
{
    return ((*obj->reg_in & obj->mask) ? 1 : 0);
}

static inline int gpio_is_connected(const gpio_t *obj)
{
    return obj->pin != (PinName)NC;
}

#ifdef __cplusplus
}
#endif

#endif // GPIO_OBJECT_H_