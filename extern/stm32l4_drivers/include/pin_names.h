/**
 * @file                pin_names.h
 * @author              Simon Schrampfer, Andreas Reichle
 * @brief 
 * @version             0.1
 * @date                2021-05-15
 * 
 * @copyright           All rights reserved
 * 
 */

#ifndef PINNAMES_H_
#define PINNAMES_H_

#include "stm32l4xx.h"
#include "stm32l4xx_ll_gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

// @TODO: maybe in own file in future
typedef enum {
    PortA = 0,
    PortB = 1,
    PortC = 2,
    PortD = 3,
    PortE = 4,
    PortF = 5,
    PortG = 6,
    PortH = 7,
    PortI = 8,
    PortJ = 9,
    PortK = 10
} PortName;

typedef enum {
    STM_PIN_INPUT = 0,
    STM_PIN_OUTPUT = 1,
    STM_PIN_ALTERNATE = 2,
    STM_PIN_ANALOG = 3,
} StmPinFunction;

typedef enum {
    PIN_INPUT = 0,
    PIN_OUTPUT
} PinDirection;

typedef enum {
    PullNone          = 0,
    PullUp            = 1,
    PullDown          = 2,
    OpenDrainPullUp   = 3,
    OpenDrainNoPull   = 4,
    OpenDrainPullDown = 5,
    PushPullNoPull    = PullNone,
    PushPullPullUp    = PullUp,
    PushPullPullDown  = PullDown,
    OpenDrain         = OpenDrainPullUp,
    PullDefault       = PullNone
} PinMode;

typedef enum {
    ALT0  = 0x100,
    ALT1  = 0x200,
    ALT2  = 0x300,
    ALT3  = 0x400
} ALTx;

typedef enum {
    PA_0  = 0x00,
    PA_0_ALT0 = PA_0 | ALT0,
    PA_0_ALT1 = PA_0 | ALT1,
    PA_1  = 0x01,
    PA_1_ALT0 = PA_1 | ALT0,
    PA_1_ALT1 = PA_1 | ALT1,
    PA_2  = 0x02,
    PA_3  = 0x03,
    PA_4  = 0x04,
    PA_4_ALT0 = PA_4 | ALT0,
    PA_5  = 0x05,
    PA_5_ALT0 = PA_5 | ALT0,
    PA_6  = 0x06,
    PA_6_ALT0 = PA_6 | ALT0,
    PA_7  = 0x07,
    PA_7_ALT0 = PA_7 | ALT0,
    PA_7_ALT1 = PA_7 | ALT1,
    PA_7_ALT2 = PA_7 | ALT2,
    PA_8  = 0x08,
    PA_9  = 0x09,
    PA_10 = 0x0A,
    PA_11 = 0x0B,
    PA_12 = 0x0C,
    PA_13 = 0x0D,
    PA_14 = 0x0E,
    PA_15 = 0x0F,
    PA_15_ALT0 = PA_15 | ALT0,

    PB_0  = 0x10,
    PB_0_ALT0 = PB_0 | ALT0,
    PB_0_ALT1 = PB_0 | ALT1,
    PB_1  = 0x11,
    PB_1_ALT0 = PB_1 | ALT0,
    PB_1_ALT1 = PB_1 | ALT1,
    PB_2  = 0x12,
    PB_3  = 0x13,
    PB_3_ALT0 = PB_3 | ALT0,
    PB_4  = 0x14,
    PB_4_ALT0 = PB_4 | ALT0,
    PB_4_ALT1 = PB_4 | ALT1,
    PB_5  = 0x15,
    PB_5_ALT0 = PB_5 | ALT0,
    PB_5_ALT1 = PB_5 | ALT1,
    PB_6  = 0x16,
    PB_6_ALT0 = PB_6 | ALT0,
    PB_7  = 0x17,
    PB_7_ALT0 = PB_7 | ALT0,
    PB_8  = 0x18,
    PB_8_ALT0 = PB_8 | ALT0,
    PB_8_ALT1 = PB_8 | ALT1,
    PB_9  = 0x19,
    PB_9_ALT0 = PB_9 | ALT0,
    PB_9_ALT1 = PB_9 | ALT1,
    PB_10 = 0x1A,
    PB_11 = 0x1B,
    PB_12 = 0x1C,
    PB_13 = 0x1D,
    PB_13_ALT0 = PB_13 | ALT0,
    PB_14 = 0x1E,
    PB_14_ALT0 = PB_14 | ALT0,
    PB_14_ALT1 = PB_14 | ALT1,
    PB_15 = 0x1F,
    PB_15_ALT0 = PB_15 | ALT0,
    PB_15_ALT1 = PB_15 | ALT1,

    PC_0  = 0x20,
    PC_0_ALT0 = PC_0 | ALT0,
    PC_0_ALT1 = PC_0 | ALT1,
    PC_1  = 0x21,
    PC_1_ALT0 = PC_1 | ALT0,
    PC_1_ALT1 = PC_1 | ALT1,
    PC_2  = 0x22,
    PC_2_ALT0 = PC_2 | ALT0,
    PC_2_ALT1 = PC_2 | ALT1,
    PC_3  = 0x23,
    PC_3_ALT0 = PC_3 | ALT0,
    PC_3_ALT1 = PC_3 | ALT1,
    PC_4  = 0x24,
    PC_4_ALT0 = PC_4 | ALT0,
    PC_5  = 0x25,
    PC_5_ALT0 = PC_5 | ALT0,
    PC_6  = 0x26,
    PC_6_ALT0 = PC_6 | ALT0,
    PC_7  = 0x27,
    PC_7_ALT0 = PC_7 | ALT0,
    PC_8  = 0x28,
    PC_8_ALT0 = PC_8 | ALT0,
    PC_9  = 0x29,
    PC_9_ALT0 = PC_9 | ALT0,
    PC_10 = 0x2A,
    PC_10_ALT0 = PC_10 | ALT0,
    PC_11 = 0x2B,
    PC_11_ALT0 = PC_11 | ALT0,
    PC_12 = 0x2C,
    PC_13 = 0x2D,
    PC_14 = 0x2E,
    PC_15 = 0x2F,

    PD_2  = 0x32,

    PH_0  = 0x70,
    PH_1  = 0x71,

    // ADC internal channels
    // ADC_TEMP = 0xF0,
    // ADC_VREF = 0xF1,
    NC = (int)0xFFFFFFFF,
} PinName;

#ifdef __cplusplus
}
#endif

#endif // PINNAMES_H_