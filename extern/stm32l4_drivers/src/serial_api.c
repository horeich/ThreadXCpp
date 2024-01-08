/**
 * @file                serial_api.c
 * @author              Simon Schrampfer, Andreas Reichle
 * @brief 
 * @version             0.1
 * @date                2021-05-15
 * 
 * @copyright           All rights reserved
 * 
 */

#include "serial_api.h"

#ifdef __cplusplus
extern "C" {
#endif

#define NUM_OF_UART         5 //  STM32L071 has a maximum of 5 UART handlers

uint32_t serial_irq_ids[NUM_OF_UART] = {0};
UART_HandleTypeDef uart_handlers[NUM_OF_UART];

static uart_irq_handler irq_handler;

static void serial_set_flow_control_direct_(serial_t *obj, FlowControl type, const serial_fc_pinmap_t *pinmap)
{
    struct serial_s *obj_s = SERIAL_S(obj);

    if (type == FlowControlNone) {
        // Disable hardware flow control
        obj_s->hw_flow_ctl = UART_HWCONTROL_NONE;
    }
    if (type == FlowControlRTS) {
        // Enable RTS
        BMHL_ASSERT(pinmap->rx_flow_pin != (PinName)NC);
        obj_s->hw_flow_ctl = UART_HWCONTROL_RTS;
        obj_s->pin_rts = pinmap->rx_flow_pin;
        // Enable the pin for RTS function
        pin_function(pinmap->rx_flow_pin, pinmap->rx_flow_function);
        pin_mode(pinmap->rx_flow_pin, PullNone);
    }
    if (type == FlowControlCTS) {
        // Enable CTS
        BMHL_ASSERT(pinmap->tx_flow_pin != (PinName)NC);
        obj_s->hw_flow_ctl = UART_HWCONTROL_CTS;
        obj_s->pin_cts = pinmap->tx_flow_pin;
        // Enable the pin for CTS function
        pin_function(pinmap->tx_flow_pin, pinmap->tx_flow_function);
        pin_mode(pinmap->tx_flow_pin, PullNone);
    }
    if (type == FlowControlRTSCTS) {
        // Enable CTS & RTS
        BMHL_ASSERT(pinmap->rx_flow_pin != (PinName)NC);
        BMHL_ASSERT(pinmap->tx_flow_pin != (PinName)NC);
        obj_s->hw_flow_ctl = UART_HWCONTROL_RTS_CTS;
        obj_s->pin_rts = pinmap->rx_flow_pin;;
        obj_s->pin_cts = pinmap->tx_flow_pin;;
        // Enable the pin for CTS function
        pin_function(pinmap->tx_flow_pin, pinmap->tx_flow_function);
        pin_mode(pinmap->tx_flow_pin, PullNone);
        // Enable the pin for RTS function
        pin_function(pinmap->rx_flow_pin, pinmap->rx_flow_function);
        pin_mode(pinmap->rx_flow_pin, PullNone);
    }

    init_uart(obj);
}

int8_t get_uart_index(UARTName uart_name) {
    uint8_t index = 0;

#if defined(USART1_BASE)
    if (uart_name == UART_1) {
        return index;
    }
    index++;
#endif

#if defined(USART2_BASE)
    if (uart_name == UART_2) {
        return index;
    }
    index++;
#endif

    return -1;
}

void serial_init(serial_t *obj, PinName tx, PinName rx) {

    uint32_t uart_tx = pinmap_peripheral(tx, PinMap_UART_TX);
    uint32_t uart_rx = pinmap_peripheral(rx, PinMap_UART_RX);
    int peripheral = (int)pinmap_merge(uart_tx, uart_rx);

    int tx_function = (int)pinmap_find_function(tx, PinMap_UART_TX);
    int rx_function = (int)pinmap_find_function(rx, PinMap_UART_RX);

    const serial_pinmap_t pinmap = {peripheral, tx, tx_function, rx, rx_function};

    struct serial_s *obj_s = SERIAL_S(obj);
    obj_s->uart            = (UARTName)pinmap.peripheral; // e.g. UART_1/UART_2/...

#if defined(USART1_BASE)
    if (obj_s->uart == USART1_BASE) {
        __HAL_RCC_USART1_CLK_ENABLE();
    }
#endif

#if defined(USART2_BASE)
    if (obj_s->uart == UART_2) {
        __HAL_RCC_USART2_CLK_ENABLE();
    }
#endif

    obj_s->index = get_uart_index(obj_s->uart);
    // @TODO: maybe add assert obj_s->index >= 0;
    
    pin_function(pinmap.tx_pin, pinmap.tx_function);
    pin_mode(pinmap.tx_pin, PullUp);
    pin_function(pinmap.rx_pin, pinmap.rx_function);
    pin_mode(pinmap.rx_pin, PullUp);

    obj_s->baudrate    = SERIAL_DEFAULT_BAUD_RATE;
    obj_s->databits    = UART_WORDLENGTH_8B;
    obj_s->stopbits    = UART_STOPBITS_1;
    obj_s->parity      = UART_PARITY_NONE;
    obj_s->hw_flow_ctl = UART_HWCONTROL_NONE;

    obj_s->pin_tx = pinmap.tx_pin;
    obj_s->pin_rx = pinmap.rx_pin;

    init_uart(obj);
}

void serial_free(serial_t *obj)
{
    struct serial_s *obj_s = SERIAL_S(obj);

#if defined(USART1_BASE)
    if (obj_s->uart == UART_1) {
        __HAL_RCC_USART1_FORCE_RESET();
        __HAL_RCC_USART1_RELEASE_RESET();
        __HAL_RCC_USART1_CLK_DISABLE();
    }
#endif

#if defined(USART2_BASE)
    if (obj_s->uart == UART_2) {
        __HAL_RCC_USART2_FORCE_RESET();
        __HAL_RCC_USART2_RELEASE_RESET();
        __HAL_RCC_USART2_CLK_DISABLE();
    }
#endif

    // Reset GPIOs to open-drain no-pull
    pin_function(obj_s->pin_tx, STM_PIN_DATA(STM_MODE_INPUT, GPIO_NOPULL, 0));
    pin_function(obj_s->pin_rx, STM_PIN_DATA(STM_MODE_INPUT, GPIO_NOPULL, 0));

    serial_irq_ids[obj_s->index] = 0;
}

void serial_baud(serial_t *obj, uint32_t baudrate) {
    struct serial_s *obj_s = SERIAL_S(obj);

    obj_s->baudrate = baudrate;

    if (init_uart(obj) == HAL_OK) {
        return;
    }
}

void serial_set_flow_control(serial_t *obj, FlowControl type, PinName rxflow, PinName txflow)
{
    struct serial_s *obj_s = SERIAL_S(obj);

    UARTName uart_rts = (UARTName)pinmap_peripheral(rxflow, PinMap_UART_RTS);
    UARTName uart_cts = (UARTName)pinmap_peripheral(txflow, PinMap_UART_CTS);

    if (((UARTName)pinmap_merge(uart_rts, obj_s->uart) == (UARTName)NC) || ((UARTName)pinmap_merge(uart_cts, obj_s->uart) == (UARTName)NC)) {
        BMHL_ASSERT(0);
        return;
    }

    int peripheral = (int)pinmap_merge(uart_rts, uart_cts);

    int tx_flow_function = (int)pinmap_find_function(txflow, PinMap_UART_CTS);
    int rx_flow_function = (int)pinmap_find_function(rxflow, PinMap_UART_RTS);

    const serial_fc_pinmap_t explicit_uart_fc_pinmap = 
        {peripheral, txflow, tx_flow_function, rxflow, rx_flow_function};

    serial_set_flow_control_direct_(obj, type, &explicit_uart_fc_pinmap);
}

// UTILITY functions to init HAL UART
// ******************************************************************************************

HAL_StatusTypeDef init_uart(serial_t *obj) {
    struct serial_s *obj_s    = SERIAL_S(obj);
    UART_HandleTypeDef *huart = &uart_handlers[obj_s->index];

    huart->Instance            = (USART_TypeDef *)obj_s->uart;
    huart->Init.BaudRate       = obj_s->baudrate;
    huart->Init.StopBits       = obj_s->stopbits;
    huart->Init.Parity         = obj_s->parity;
    huart->Init.HwFlowCtl      = obj_s->hw_flow_ctl;
    huart->Init.OverSampling   = UART_OVERSAMPLING_16; // maximum allowed baud: 32MHz/16 = 2MHz
    huart->Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;

    huart->AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;

    if (obj_s->pin_rx == NC) {
        huart->Init.Mode = UART_MODE_TX;
    } else if (obj_s->pin_tx == NC) {
        huart->Init.Mode = UART_MODE_RX;
    } else {
        huart->Init.Mode = UART_MODE_TX_RX;
    }

    return HAL_UART_Init(huart);
}



int serial_writable(serial_t *obj) {
    struct serial_s *obj_s    = SERIAL_S(obj);
    UART_HandleTypeDef *huart = &uart_handlers[obj_s->index];

    // Is data already transmitted (transmit register empty)?
    return (__HAL_UART_GET_FLAG(huart, UART_FLAG_TXE) != RESET) ? 1 : 0;
}

int serial_readable(serial_t *obj) {
    struct serial_s *obj_s    = SERIAL_S(obj);
    UART_HandleTypeDef *huart = &uart_handlers[obj_s->index];

    /*  To avoid a target blocking case, let's check for
     *  possible OVERRUN error and discard it
     */
    if (__HAL_UART_GET_FLAG(huart, UART_FLAG_ORE)) {
        __HAL_UART_CLEAR_OREFLAG(huart);
    }

    // Has data been received?
    return (__HAL_UART_GET_FLAG(huart, UART_FLAG_RXNE) != RESET) ? 1 : 0;
}

void serial_putc(serial_t *obj, int c) {
    struct serial_s *obj_s    = SERIAL_S(obj);
    UART_HandleTypeDef *huart = &uart_handlers[obj_s->index];

    while (!serial_writable(obj)); // data transmitted?
    huart->Instance->TDR = (uint16_t)(c & 0x1FFU);
}

int serial_getc(serial_t *obj) {
    struct serial_s *obj_s    = SERIAL_S(obj);
    UART_HandleTypeDef *huart = &uart_handlers[obj_s->index];

    // Computing UART mask applied to RDR register
    UART_MASK_COMPUTATION(huart);
    uint16_t uhMask = huart->Mask;

    while (!serial_readable(obj)) {
    }
    /** When receiving with the parity enabled, the value read in the MSB bit
     * is the received parity bit.
     */

    return (int)(huart->Instance->RDR & uhMask);
}

// Interrupt handling
// ******************************************************************************************

void serial_irq_handler(serial_t *obj, uart_irq_handler handler, uint32_t id) {
    struct serial_s *obj_s = &(obj->serial);

    irq_handler                  = handler;
    serial_irq_ids[obj_s->index] = id; // store pointer to base serial class object
}

static void uart_irq(UARTName uart_name) {
    int8_t id = get_uart_index(uart_name);

    if (id >= 0) {
        UART_HandleTypeDef *huart = &uart_handlers[id];
        if (serial_irq_ids[id] != 0) {
            if (__HAL_UART_GET_FLAG(huart, UART_FLAG_TXE) != RESET) {
                if (__HAL_UART_GET_IT(huart, UART_IT_TXE) != RESET && __HAL_UART_GET_IT_SOURCE(huart, UART_IT_TXE)) {
                    irq_handler(serial_irq_ids[id], TxIrq);
                }
            }
            if (__HAL_UART_GET_FLAG(huart, UART_FLAG_RXNE) != RESET) {
                if (__HAL_UART_GET_IT(huart, UART_IT_RXNE) != RESET && __HAL_UART_GET_IT_SOURCE(huart, UART_IT_RXNE)) {
                    irq_handler(serial_irq_ids[id], RxIrq);
                    /* Flag has been cleared when reading the content */
                }
            }
            if (__HAL_UART_GET_FLAG(huart, UART_FLAG_ORE) != RESET) {
                if (__HAL_UART_GET_IT(huart, UART_IT_ORE) != RESET) {
                    __HAL_UART_CLEAR_FLAG(huart, UART_CLEAR_OREF);
                }
            }
        }
    }
}

#if defined(USART1_BASE)
static void uart1_irq(void)
{
    uart_irq(UART_1);
}
void USART1_IRQHandler(void) { uart1_irq(); }
#endif

#if defined(USART2_BASE)
void uart2_irq(void)
{
    uart_irq(UART_2);
}
void USART2_IRQHandler(void) { uart2_irq(); }
#endif

void serial_irq_set(serial_t *obj, SerialIrq irq, uint32_t enable) {
    struct serial_s *obj_s    = &(obj->serial);
    UART_HandleTypeDef *huart = &uart_handlers[obj_s->index];

    IRQn_Type irq_n = (IRQn_Type)0;
    // uint32_t vector = 0;

#if defined(USART1_BASE)
    if (obj_s->uart == UART_1) {
        irq_n = USART1_IRQn;
        // vector = (uint32_t)&uart1_irq;
    }
#endif

#if defined(USART2_BASE)
    if (obj_s->uart == UART_2) {
        irq_n = USART2_IRQn;
        // vector = (uint32_t)&uart2_irq;
    }
#endif

    if (enable) {
        if (irq == RxIrq) {
            __HAL_UART_ENABLE_IT(huart, UART_IT_RXNE); // receive data register not empty interrupt
        } else {                                       // TxIrq
            __HAL_UART_ENABLE_IT(huart, UART_IT_TXE);
        }
        // NVIC_ClearPendingIRQ(irq_n);
        // NVIC_SetVector(irq_n, vector);
        NVIC_EnableIRQ(irq_n);

    } else { // disable
        int all_disabled = 0;
        if (irq == RxIrq) {
            __HAL_UART_DISABLE_IT(huart, UART_IT_RXNE);
            // Check if TxIrq is disabled too
            if ((huart->Instance->CR1 & USART_CR1_TXEIE) == 0) {
                all_disabled = 1;
            }
        } else { // TxIrq
            __HAL_UART_DISABLE_IT(huart, UART_IT_TXE);
            // Check if RxIrq is disabled too
            if ((huart->Instance->CR1 & USART_CR1_RXNEIE) == 0) {
                all_disabled = 1;
            }
        }

        if (all_disabled) {
            NVIC_DisableIRQ(irq_n);
        }
    }
}

#ifdef __cplusplus
}
#endif