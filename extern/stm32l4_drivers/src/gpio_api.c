/**
 * @file                gpio_api.c
 * @author              Simon Schrampfer, Andreas Reichle
 * @brief
 * @version             0.1
 * @date                2021-05-16
 *
 * @copyright           All rights reserved
 *
 */

#include "gpio_api.h"
#include "bmhl_assert.h"

#ifdef __cplusplus
extern "C" {
#endif

// #ifdef __cplusplus
//  const uint32_t ll_pin_defines[16] = {LL_GPIO_PIN_0,  LL_GPIO_PIN_1,  LL_GPIO_PIN_2,  LL_GPIO_PIN_3, LL_GPIO_PIN_4,  LL_GPIO_PIN_5,
//                                       LL_GPIO_PIN_6,  LL_GPIO_PIN_7,  LL_GPIO_PIN_8,  LL_GPIO_PIN_9, LL_GPIO_PIN_10, LL_GPIO_PIN_11,
//                                       LL_GPIO_PIN_12, LL_GPIO_PIN_13, LL_GPIO_PIN_14, LL_GPIO_PIN_15};
// #else
// extern const uint32_t ll_pin_defines[16]; // defined in pin_map.c
// #endif

// Interface functions
// ******************************************************************************************

static inline void gpio_init_in_(gpio_t *gpio, PinName pin, PinMode mode) {
    gpio_init(gpio, pin); // fills gpio structure and enables clock
    if (pin != NC) {
        gpio_dir(gpio, PIN_INPUT);
        gpio_mode(gpio, mode);
    }
}

static inline void gpio_init_out_(gpio_t *gpio, PinName pin, PinMode mode, int value) {
    gpio_init(gpio, pin); // fills gpio structure and enables clock
    if (pin != NC) {
        gpio_write(gpio, value);
        gpio_dir(gpio, PIN_OUTPUT);
        gpio_mode(gpio, mode);
    }
}

// C-API functions
// ******************************************************************************************

void gpio_init_inout(gpio_t *gpio, PinName pin, PinDirection direction, PinMode mode, int value) {
    if (direction == PIN_INPUT) {
        gpio_init_in_(gpio, pin, mode);
        if (pin != NC) {
            gpio_write(gpio, value);
        }
    } else {
        gpio_init_out_(gpio, pin, mode, value);
    }
}

void gpio_init_in(gpio_t *gpio, PinName pin) { gpio_init_in_ex(gpio, pin, PullDefault); }

void gpio_init_out(gpio_t *gpio, PinName pin) { gpio_init_out_ex(gpio, pin, 0); }

void gpio_init_in_ex(gpio_t *gpio, PinName pin, PinMode mode) { gpio_init_in_(gpio, pin, mode); }

void gpio_init_out_ex(gpio_t *gpio, PinName pin, int value) { gpio_init_out_(gpio, pin, PullNone, value); }

uint32_t gpio_set(PinName pin) {
    // BMHL_ASSERT(pin != (PinName)NC); // TODO:
    pin_function(pin, STM_PIN_DATA(STM_MODE_INPUT, GPIO_NOPULL, 0));
    return (uint32_t)(1 << ((uint32_t)pin & 0xF)); // returns the pin mask
}

// API functions (see gpi_object.h for further functions)
// ******************************************************************************************

void gpio_dir(gpio_t *obj, PinDirection direction) // TODO: make inline
{
    if (direction == PIN_INPUT) {
        LL_GPIO_SetPinMode(obj->gpio, obj->ll_pin, LL_GPIO_MODE_INPUT);
    } else { // PIN_OUTPUT
        LL_GPIO_SetPinMode(obj->gpio, obj->ll_pin, LL_GPIO_MODE_OUTPUT);
    }
}

void gpio_mode(gpio_t *obj, PinMode mode) { pin_mode(obj->pin, mode); }

// HAL init functions
// ******************************************************************************************

void gpio_init(gpio_t *obj, PinName pin) {
    obj->pin = pin;
    if (pin == (PinName)NC) {
        return; // allow nc but return
    }

    uint32_t port_index = STM_PORT(pin);

    // Enable GPIO clock
    GPIO_TypeDef *gpio = Set_GPIO_Clock(port_index);

    //#if defined(ALTC) // not implemented: analog pin alternative defintions
    // if (pin == PA_0C) {
    //     HAL_SYSCFG_AnalogSwitchConfig(SYSCFG_SWITCH_PA0, SYSCFG_SWITCH_PA0_CLOSE);
    // }
    // if (pin == PA_1C) {
    //     HAL_SYSCFG_AnalogSwitchConfig(SYSCFG_SWITCH_PA1, SYSCFG_SWITCH_PA1_CLOSE);
    // }
    // if (pin == PC_2C) {
    //     HAL_SYSCFG_AnalogSwitchConfig(SYSCFG_SWITCH_PC2, SYSCFG_SWITCH_PC2_CLOSE);
    // }
    // if (pin == PC_3C) {
    //     HAL_SYSCFG_AnalogSwitchConfig(SYSCFG_SWITCH_PC3, SYSCFG_SWITCH_PC3_CLOSE);
    // }
    //#endif /* ALTC */

    // Fill GPIO object structure for future use
    obj->mask    = gpio_set(pin);
    obj->gpio    = gpio;
    obj->ll_pin  = ll_pin_defines[STM_PIN(obj->pin)];
    obj->reg_in  = &gpio->IDR;
    obj->reg_set = &gpio->BSRR;
#ifdef GPIO_IP_WITHOUT_BRR
    obj->reg_clr = &gpio->BSRR;
#else
    obj->reg_clr = &gpio->BRR;
#endif
}

GPIO_TypeDef *Set_GPIO_Clock(uint32_t port_idx) {
    uint32_t gpio_add = 0;
    switch (port_idx) {
    case PortA:
        gpio_add = GPIOA_BASE;
        __HAL_RCC_GPIOA_CLK_ENABLE();
        break;
    case PortB:
        gpio_add = GPIOB_BASE;
        __HAL_RCC_GPIOB_CLK_ENABLE();
        break;
#if defined(GPIOC_BASE)
    case PortC:
        gpio_add = GPIOC_BASE;
        __HAL_RCC_GPIOC_CLK_ENABLE();
        break;
#endif
#if defined GPIOD_BASE
    case PortD:
        gpio_add = GPIOD_BASE;
        __HAL_RCC_GPIOD_CLK_ENABLE();
        break;
#endif
#if defined GPIOE_BASE
    case PortE:
        gpio_add = GPIOE_BASE;
        __HAL_RCC_GPIOE_CLK_ENABLE();
        break;
#endif
#if defined GPIOF_BASE
    case PortF:
        gpio_add = GPIOF_BASE;
        __HAL_RCC_GPIOF_CLK_ENABLE();
        break;
#endif
#if defined GPIOG_BASE
    case PortG:
#if defined PWR_CR2_IOSV /* TARGET_STM32L4 / TARGET_STM32L5 */
        __HAL_RCC_PWR_CLK_ENABLE();
        HAL_PWREx_EnableVddIO2();
#endif
        gpio_add = GPIOG_BASE;
        __HAL_RCC_GPIOG_CLK_ENABLE();
        break;
#endif
#if defined GPIOH_BASE
    case PortH:
        gpio_add = GPIOH_BASE;
        __HAL_RCC_GPIOH_CLK_ENABLE();
        break;
#endif
#if defined GPIOI_BASE
    case PortI:
        gpio_add = GPIOI_BASE;
        __HAL_RCC_GPIOI_CLK_ENABLE();
        break;
#endif
#if defined GPIOJ_BASE
    case PortJ:
        gpio_add = GPIOJ_BASE;
        __HAL_RCC_GPIOJ_CLK_ENABLE();
        break;
#endif
#if defined GPIOK_BASE
    case PortK:
        gpio_add = GPIOK_BASE;
        __HAL_RCC_GPIOK_CLK_ENABLE();
        break;
#endif
    default:
        // error("Pinmap error: wrong port number.");
        break;
    }
    return (GPIO_TypeDef *)gpio_add;
}

#ifdef __cplusplus
}
#endif