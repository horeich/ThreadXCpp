/**
 * @file                pinmap.c
 * @author              Simon Schrampfer, Andreas Reichle
 * @brief 
 * @version             0.1
 * @date                2021-03-28
 * 
 * @copyright           All rights reserved
 * 
 */

#include "pinmap.h"

#ifdef __cplusplus
extern "C" {
#endif

extern GPIO_TypeDef *Set_GPIO_Clock(uint32_t port_idx); // defined in gpio_api.c

const uint32_t ll_pin_defines[16] = {
    LL_GPIO_PIN_0,  
    LL_GPIO_PIN_1,  
    LL_GPIO_PIN_2,  
    LL_GPIO_PIN_3, 
    LL_GPIO_PIN_4,  
    LL_GPIO_PIN_5,
    LL_GPIO_PIN_6,  
    LL_GPIO_PIN_7,  
    LL_GPIO_PIN_8,  
    LL_GPIO_PIN_9, 
    LL_GPIO_PIN_10, 
    LL_GPIO_PIN_11,
    LL_GPIO_PIN_12, 
    LL_GPIO_PIN_13, 
    LL_GPIO_PIN_14, 
    LL_GPIO_PIN_15
};

static inline void stm_pin_DisconnectDebug(PinName pin)
{
    /* empty for now */
}

static inline void stm_pin_SetAFPin(GPIO_TypeDef *gpio, PinName pin, uint32_t afnum)
{
    uint32_t ll_pin  = ll_pin_defines[STM_PIN(pin)];

    if (STM_PIN(pin) > 7) {
        LL_GPIO_SetAFPin_8_15(gpio, ll_pin, afnum);
    } else {
        LL_GPIO_SetAFPin_0_7(gpio, ll_pin, afnum);
    }
}

static inline void stm_pin_PullConfig(GPIO_TypeDef *gpio, uint32_t ll_pin, uint32_t pull_config)
{
    switch (pull_config) {
        case GPIO_PULLUP:
            LL_GPIO_SetPinPull(gpio, ll_pin, LL_GPIO_PULL_UP);
            break;
        case GPIO_PULLDOWN:
            LL_GPIO_SetPinPull(gpio, ll_pin, LL_GPIO_PULL_DOWN);
            break;
        default:
            LL_GPIO_SetPinPull(gpio, ll_pin, LL_GPIO_PULL_NO);
            break;
    }
}

void pin_function(PinName pin, int function) {
    if (pin == NC) {
        return;
    }

    uint32_t speed   = STM_PIN_SPEED(function);
    uint32_t mode    = STM_PIN_FUNCTION(function);
    uint32_t afnum   = STM_PIN_AFNUM(function);
    uint32_t port    = STM_PORT(pin);
    uint32_t ll_pin  = ll_pin_defines[STM_PIN(pin)];
    uint32_t ll_mode = 0;

    GPIO_TypeDef *const gpio = Set_GPIO_Clock(port);

    /*  Set default speed to high.
     *  For most families there are dedicated registers so it is
     *  not so important, register can be set at any time.
     *  But for families like F1, speed only applies to output.
     */

    switch (speed) {
        case STM_PIN_SPEED_MASK:
#if defined (LL_GPIO_SPEED_FREQ_VERY_HIGH)
            LL_GPIO_SetPinSpeed(gpio, ll_pin, LL_GPIO_SPEED_FREQ_VERY_HIGH);
#else
            LL_GPIO_SetPinSpeed(gpio, ll_pin, LL_GPIO_SPEED_FREQ_HIGH);
#endif
            break;
        default:
            LL_GPIO_SetPinSpeed(gpio, ll_pin, speed); // default value for backward compatibility
            break;
        }

    switch (mode) {
        case STM_PIN_INPUT:
            ll_mode = LL_GPIO_MODE_INPUT;
            break;
        case STM_PIN_OUTPUT:
            ll_mode = LL_GPIO_MODE_OUTPUT;
            break;
        case STM_PIN_ALTERNATE:
            ll_mode = LL_GPIO_MODE_ALTERNATE;
            stm_pin_SetAFPin(gpio, pin, afnum); // set correct alternative function AF TODO: rename
            break;
        case STM_PIN_ANALOG:
            ll_mode = LL_GPIO_MODE_ANALOG;
            break;
        default:
            //MBED_ASSERT(0); // FIXME:
            break;
    }
    LL_GPIO_SetPinMode(gpio, ll_pin, ll_mode);

    /*  For now by default use Speed HIGH for output or alt modes */
    if ((mode == STM_PIN_OUTPUT) || (mode == STM_PIN_ALTERNATE)) {
        if (STM_PIN_OD(function)) {
            LL_GPIO_SetPinOutputType(gpio, ll_pin, LL_GPIO_OUTPUT_OPENDRAIN);
        } else {
            LL_GPIO_SetPinOutputType(gpio, ll_pin, LL_GPIO_OUTPUT_PUSHPULL);
        }
    }

    stm_pin_PullConfig(gpio, ll_pin, STM_PIN_PUPD(function)); // Note: not really necessary here
    stm_pin_DisconnectDebug(pin);
}

void pin_mode(PinName pin, PinMode mode)
{
    if (pin == NC) {
        return;
    }

    uint32_t port_index = STM_PORT(pin);
    uint32_t ll_pin  = ll_pin_defines[STM_PIN(pin)];
    // Enable GPIO clock
    GPIO_TypeDef *gpio = Set_GPIO_Clock(port_index);

    uint32_t function = LL_GPIO_GetPinMode(gpio, ll_pin);

    if ((function == LL_GPIO_MODE_OUTPUT) || (function == LL_GPIO_MODE_ALTERNATE)) {
        if ((mode == OpenDrainNoPull) || (mode == OpenDrainPullUp) || (mode == OpenDrainPullDown)) {
            LL_GPIO_SetPinOutputType(gpio, ll_pin, LL_GPIO_OUTPUT_OPENDRAIN);
        } else {
            LL_GPIO_SetPinOutputType(gpio, ll_pin, LL_GPIO_OUTPUT_PUSHPULL);
        }
    }

    if ((mode == OpenDrainPullUp) || (mode == PullUp)) {
        stm_pin_PullConfig(gpio, ll_pin, GPIO_PULLUP);
    } else if ((mode == OpenDrainPullDown) || (mode == PullDown)) {
        stm_pin_PullConfig(gpio, ll_pin, GPIO_PULLDOWN);
    } else {
        stm_pin_PullConfig(gpio, ll_pin, GPIO_NOPULL);
    }
}






uint32_t pinmap_peripheral(PinName pin, const PinMap *map) {
    uint32_t peripheral = (uint32_t)NC;

    if (pin == (PinName)NC) {
        return (uint32_t)NC;
    }

    peripheral = pinmap_find_peripheral(pin, map);
    if ((uint32_t)NC == peripheral) { // no mapping available
                                      // FIXME: error
    }
    return peripheral;
}

uint32_t pinmap_find_peripheral(PinName pin, const PinMap *map) {
    while (map->pin != NC) { // run through all UART pheripherals
        if (map->pin == pin) {
            return map->peripheral;
        }
        map++;
    }
    return (uint32_t)NC;
}

uint32_t pinmap_find_function(PinName pin, const PinMap *map) {
    while (map->pin != NC) {
        if (map->pin == pin) {
            return map->function;
        }
        map++;
    }
    return (uint32_t)NC;
}

uint32_t pinmap_merge(uint32_t a, uint32_t b) {
    // both are the same (inc both NC)
    if (a == b) {
        return a;
    }

    // one (or both) is not connected
    if (a == (uint32_t)NC) {
        return b;
    }
    if (b == (uint32_t)NC) {
        return a;
    }

    // mis-match error case
    /// FIXME: invalid pinmap error
    return 1;
}



#ifdef __cplusplus
}
#endif