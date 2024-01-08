/**
 * @file                pinmap.h
 * @author              Simon Schrampfer, Andreas Reichle
 * @brief 
 * @version             0.1
 * @date                2021-05-15
 * 
 * @copyright           All rights reserved
 * 
 */

#ifndef PIN_MAP_H_
#define PIN_MAP_H_

#include "pin_names.h"
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* The table below gives an overview of the different alternate functions per port.
 * For more details refer yourself to the product data sheet.
 * [Taken from file stm32l0xx_hal_gpio_ex.h]
 */

/*     |   AF0  |   AF1  |   AF2  |   AF3  |   AF4  |   AF5  |   AF6  |   AF7  |
 *______________________________________________________________________________
 * PA0 |        |        |TIM2_C1 |        |USART2  |TIM2_TR |USART4  |COMP1   |
 * PA1 |EVENTOUT|        |TIM2_C2 |        |USART2  |TIM21_TR|USART4  |        |
 * PA2 |TIM21_C1|        |TIM2_C3 |        |USART2  |        |LPUART1 |COMP2   |
 * PA3 |TIM21_C2|        |TIM2_C4 |        |USART2  |        |LPUART1 |        |
 * PA4 |SPI1    |        |        |        |USART2  |TIM22_TR|        |        |
 * PA5 |SPI1    |        |TIM2_TR |        |        |TIM2_C1 |        |        |
 * PA6 |SPI1    |        |TIM3_C1 |        |LPUART1 |TIM22_C1|EVENTOUT|COMP1   |
 * PA7 |SPI1    |        |TIM3_C2 |        |        |TIM22_C2|EVENTOUT|COMP2   |
 * PA8 |MCO     |        |        |EVENTOUT|USART1  |        |        |I2C3    |
 * PA9 |MCO     |        |        |        |USART1  |        |I2C1    |I2C3    |
 * PA10|        |        |        |        |USART1  |        |I2C1    |        |
 * PA11|SPI1    |        |EVENTOUT|        |USART1  |        |I2C2    |COMP1   |
 * PA12|SPI1    |        |EVENTOUT|        |USART1  |        |I2C2    |COMP2   |
 * PA13|SWDIO   |        |        |        |        |        |LPUART1 |        |
 * PA14|SWCLK   |        |        |        |USART2  |        |LPUART1 |        |
 * PA15|SPI1    |        |TIM2_TR |EVENTOUT|USART2  |TIM2_C1 |USART4  |        |
 *______________________________________________________________________________
 * PB0 |EVENTOUT|        |TIM3_C3 |        |        |        |        |        |
 * PB1 |        |        |TIM3_C4 |        |LPUART1 |        |        |        |
 * PB2 |        |        |LPTIM1_O|        |        |        |        |I2C3    |
 * PB3 |SPI1    |        |TIM2_C2 |        |EVENTOUT|USART1  |USART5  |        |
 * PB4 |SPI1    |        |TIM3_C1 |        |TIM22_C1|USART1  |USART5  |I2C3    |
 * PB5 |SPI1    |        |LPTIM1_I|I2C1    |TIM3_C2 |USART1  |USART5  |        |
 *     |        |        |        |        |TIM22_C2|        |        |        |
 * PB6 |USART1  |I2C1    |LPTIM1_T|        |        |        |        |        |
 * PB7 |USART1  |I2C1    |LPTIM1_I|        |        |        |USART4  |        |
 * PB8 |        |        |        |        |I2C1    |        |        |        |
 * PB9 |        |        |EVENTOUT|        |I2C1    |SPI2    |        |        |
 * PB10|        |        |TIM2_C3 |        |LPUART1 |SPI2    |I2C2    |LPUART1 |
 * PB11|EVENTOUT|        |TIM2_C4 |        |LPUART1 |        |I2C2    |LPUART1 |
 * PB12|SPI2    |        |LPUART1 |        |        |I2C2    |EVENTOUT|        |
 * PB13|SPI2    |        |MCO     |        |LPUART1 |I2C2    |TIM21_C1|        |
 * PB14|SPI2    |        |RTC     |        |LPUART1 |I2C2    |TIM21_C2|        |
 * PB15|SPI2    |        |RTC     |        |        |        |        |        |
 *______________________________________________________________________________
 * PC0 |LPTIM1_I|        |EVENTOUT|        |        |        |LPUART1 |I2C3    |
 * PC1 |LPTIM1_O|        |EVENTOUT|        |        |        |LPUART1 |I2C3    |
 * PC2 |LPTIM1_I|        |SPI2    |        |        |        |        |        |
 * PC3 |LPTIM1_T|        |SPI2    |        |        |        |        |        |
 * PC4 |EVENTOUT|        |LPUART1 |        |        |        |        |        |
 * PC5 |        |        |LPUART1 |        |        |        |        |        |
 * PC6 |TIM22_C1|        |TIM3_C1 |        |        |        |        |        |
 * PC7 |TIM22_C2|        |TIM3_C2 |        |        |        |        |        |
 * PC8 |TIM22_TR|        |TIM3_C3 |        |        |        |        |        |
 * PC9 |TIM21_TR|        |        |        |        |        |        |I2C3    |
 *     |        |        |TIM3_C4 |        |        |        |        |        |
 * PC10|LPUART1 |        |        |        |        |        |USART4  |        |
 * PC11|LPUART1 |        |        |        |        |        |USART4  |        |
 * PC12|        |        |USART5  |        |        |        |USART4  |        |
 * PC13|        |        |        |        |        |        |        |        |
 * PC14|        |        |        |        |        |        |        |        |
 * PC15|        |        |        |        |        |        |        |        |
 *______________________________________________________________________________
 * PD0 |TIM21_C1|SPI2    |        |        |        |        |        |        |
 * PD1 |        |SPI2    |        |        |        |        |        |        |
 * PD2 |LPUART1 |        |TIM3_TR |        |        |        |USART5  |        |
 * PD3 |USART2  |        |SPI2    |        |        |        |        |        |
 * PD4 |USART2  |SPI2    |        |        |        |        |        |        |
 * PD5 |USART2  |        |        |        |        |        |        |        |
 * PD6 |USART2  |        |        |        |        |        |        |        |
 * PD7 |USART2  |TIM21_C2|        |        |        |        |        |        |
 * PD8 |LPUART1 |        |        |        |        |        |        |        |
 * PD9 |LPUART1 |        |        |        |        |        |        |        |
 * PD10|        |        |        |        |        |        |        |        |
 * PD11|LPUART1 |        |        |        |        |        |        |        |
 * PD12|LPUART1 |        |        |        |        |        |        |        |
 * PD13|        |        |        |        |        |        |        |        |
 * PD14|        |        |        |        |        |        |        |        |
 * PD15|        |        |        |        |        |        |        |        |
 *______________________________________________________________________________
 * PE0 |        |        |EVENTOUT|        |        |        |        |        |
 * PE1 |        |        |EVENTOUT|        |        |        |        |        |
 * PE2 |        |        |TIM3_TR |        |        |        |        |        |
 * PE3 |TIM22_C1|        |TIM3_C1 |        |        |        |        |        |
 * PE4 |TIM22_C2|        |TIM3_C2 |        |        |        |        |        |
 * PE5 |TIM21_C1|        |TIM3_C3 |        |        |        |        |        |
 * PE6 |TIM21_C2|        |TIM3_C4 |        |        |        |        |        |
 * PE7 |        |        |        |        |        |        |USART5  |        |
 * PE8 |        |        |        |        |        |        |USART4  |        |
 * PE9 |TIM2_C1 |        |TIM2_TR |        |        |        |USART4  |        |
 * PE10|TIM2_C2 |        |        |        |        |        |USART5  |        |
 * PE11|TIM2_C3 |        |        |        |        |        |USART5  |        |
 * PE12|TIM2_C4 |        |SPI1    |        |        |        |        |        |
 * PE13|        |        |SPI1    |        |        |        |        |        |
 * PE14|        |        |SPI1    |        |        |        |        |        |
 * PE15|        |        |SPI1    |        |        |        |        |        |
 *______________________________________________________________________________
 * PH0 |        |        |        |        |        |        |        |        |
 * PH1 |        |        |        |        |        |        |        |        |
 * PH9 |        |        |        |        |        |        |        |        |
 * PH10|        |        |        |        |        |        |        |        |
 *
 */

/*  STM PIN data as used in pin_function is coded on 32 bits as below
 *   [2:0]  Function (like in MODER reg) : Input / Output / Alt / Analog
 *     [3]  Output Push-Pull / Open Drain (as in OTYPER reg)
 *   [5:4]  as in PUPDR reg: No Pull, Pull-up, Pull-Donc
 *   [9:6]  speed config (as in OSPEEDR)
 * [13:10]  Alternate Num (as in AFRL/AFRG reg)
 * [17:14]  Channel (Analog/Timer specific)
 *    [18]  Inverted (Analog/Timer specific)
 *    [19]  Analog ADC control - Only valid for specific families
 * [32:21]  Reserved
 */

#define STM_PIN_FUNCTION_MASK           0x07
#define STM_PIN_FUNCTION_SHIFT          0x00

#define STM_PIN_OD_MASK                 0x01
#define STM_PIN_OD_SHIFT                0x03
#define STM_PIN_OD_BITS                 (STM_PIN_OD_MASK << STM_PIN_OD_SHIFT)

#define STM_PIN_PUPD_MASK               0x03
#define STM_PIN_PUPD_SHIFT              0x04
#define STM_PIN_PUPD_BITS               (STM_PIN_PUPD_MASK << STM_PIN_PUPD_SHIFT)

#define STM_PIN_SPEED_MASK              0x0F
#define STM_PIN_SPEED_SHIFT             0x06
#define STM_PIN_SPEED_BITS              (STM_PIN_SPEED_MASK << STM_PIN_SPEED_SHIFT)

#define STM_PIN_AFNUM_MASK              0x0F
#define STM_PIN_AFNUM_SHIFT             0x0A
#define STM_PIN_AFNUM_BITS              (STM_PIN_AFNUM_MASK << STM_PIN_AFNUM_SHIFT)

/**
 * @brief       Returns valid bit code according to the given pin function (see table above)
 * 
 */
#define STM_PIN_FUNCTION(X)         (((X) >> STM_PIN_FUNCTION_SHIFT) & STM_PIN_FUNCTION_MASK)
#define STM_PIN_OD(X)               (((X) >> STM_PIN_OD_SHIFT) & STM_PIN_OD_MASK)
#define STM_PIN_PUPD(X)             (((X) >> STM_PIN_PUPD_SHIFT) & STM_PIN_PUPD_MASK)
#define STM_PIN_SPEED(X)            (((X) >> STM_PIN_SPEED_SHIFT) & STM_PIN_SPEED_MASK)
#define STM_PIN_AFNUM(X)            (((X) >> STM_PIN_AFNUM_SHIFT) & STM_PIN_AFNUM_MASK)


#define STM_PIN_DEFINE(FUNC_OD, PUPD, AFNUM)  ((int)(FUNC_OD) |\
            ((STM_PIN_SPEED_MASK & STM_PIN_SPEED_MASK) << STM_PIN_SPEED_SHIFT) |\
            (((PUPD) & STM_PIN_PUPD_MASK) << STM_PIN_PUPD_SHIFT) |\
            (((AFNUM) & STM_PIN_AFNUM_MASK) << STM_PIN_AFNUM_SHIFT))

#define STM_PIN_DATA(FUNC_OD, PUPD, AFNUM) \
            STM_PIN_DEFINE(FUNC_OD, PUPD, AFNUM)

#define STM_MODE_INPUT               (STM_PIN_INPUT)
#define STM_MODE_OUTPUT_PP           (STM_PIN_OUTPUT)
#define STM_MODE_OUTPUT_OD           (STM_PIN_OUTPUT | STM_PIN_OD_BITS)
#define STM_MODE_AF_PP               (STM_PIN_ALTERNATE)
#define STM_MODE_AF_OD               (STM_PIN_ALTERNATE | STM_PIN_OD_BITS)
#define STM_MODE_ANALOG              (STM_PIN_ANALOG)
#define STM_MODE_ANALOG_ADC_CONTROL  (STM_PIN_ANALOG | STM_PIN_ANALOG_CONTROL_BIT)

// High nibble = port number (0=A, 1=B, 2=C, 3=D, 4=E, 5=F, 6=G, 7=H)
// Low nibble  = pin number
#define STM_PORT(X)         (((uint32_t)(X) >> 4) & 0xF)
#define STM_PIN(X)          ((uint32_t)(X) & 0xF)

typedef struct {
    PinName pin;
    int peripheral;
    int function;
} PinMap;


extern const uint32_t ll_pin_defines[16];

/**
 * @brief               Configures pin (mode, speed, output type and pull-up/pull-down)
 *                      HAL equivalent for USART2:
 *                      __HAL_RCC_GPIOA_CLK_ENABLE();
                        GPIO_InitTypeDef GPIO_InitStruct = {0};
                        GPIO_InitStruct.Pin              = GPIO_PIN_2 | GPIO_PIN_3;
                        GPIO_InitStruct.Mode             = GPIO_MODE_AF_OD;
                        GPIO_InitStruct.Pull             = GPIO_PULLUP;
                        GPIO_InitStruct.Speed            = GPIO_SPEED_FREQ_VERY_HIGH;
                        GPIO_InitStruct.Alternate        = GPIO_AF4_USART2;
                        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
 *
 * 
 * @param pin           
 * @param function 
 */
void pin_function(PinName pin, int function);

/**
 * @brief               Configures pin either pull-up or pull-down       
 * 
 * @param pin 
 * @param mode 
 */
void pin_mode(PinName pin, PinMode mode);

uint32_t pinmap_peripheral(PinName pin, const PinMap *map);

uint32_t pinmap_find_peripheral(PinName pin, const PinMap *map);

uint32_t pinmap_merge(uint32_t a, uint32_t b);

uint32_t pinmap_find_function(PinName pin, const PinMap *map);


#ifdef __cplusplus
}
#endif

#endif // PIN_MAP_H_