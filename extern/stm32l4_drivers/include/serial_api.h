/**
 * @file                serial_api.h
 * @author              Simon Schrampfer, Andreas Reichle
 * @brief 
 * @version             0.1
 * @date                2021-05-15
 * 
 * @copyright           All rights reserved
 * 
 */

#ifndef SERIAL_API_H_
#define SERIAL_API_H_

#include <stdint.h>
#include "peripheral_pins.h"
#include "bmhl_assert.h"
#include "stm32l4xx.h"
#include "stm32l4xx_hal_uart.h"
#include "stm32l4xx_hal_uart_ex.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SERIAL_S(obj) (&((obj)->serial))

#define SERIAL_DEFAULT_BAUD_RATE        115200

#define USE_LPUART_CLK_LSE              0x01
#define USE_LPUART_CLK_PCLK1            0x02
#define USE_LPUART_CLK_HSI              0x04

typedef enum {
    FlowControlNone,
    FlowControlRTS,
    FlowControlCTS,
    FlowControlRTSCTS
} FlowControl;

struct serial_s {
    UARTName uart;
    int index; // needed for irq
    uint32_t baudrate;
    uint32_t databits;
    uint32_t stopbits;
    uint32_t parity;
    PinName pin_rx;
    PinName pin_tx;
    uint32_t hw_flow_ctl;
    PinName pin_rts;
    PinName pin_cts;
};

typedef struct {
    int peripheral;
    PinName tx_pin;
    int tx_function;
    PinName rx_pin;
    int rx_function;
} serial_pinmap_t;

typedef struct {
    int peripheral;
    PinName tx_flow_pin;
    int tx_flow_function;
    PinName rx_flow_pin;
    int rx_flow_function;
} serial_fc_pinmap_t;

typedef enum {
    RxIrq,      /**< Receive Data Register Full */
    TxIrq       /**< Transmit Data Register Empty */
} SerialIrq;

// UART interrupt callback
typedef void (*uart_irq_handler)(uint32_t id, SerialIrq event);

typedef struct {
    struct serial_s serial;  /**< Target specific serial structure */
    // struct buffer_s tx_buff; /**< TX buffer */
    // struct buffer_s rx_buff; /**< RX buffer */
    // uint8_t char_match;      /**< Character to be matched */
    // uint8_t char_found;      /**< State of the matched character */
} serial_t;

// Utility function
int8_t get_uart_index(UARTName uart);

/**
 * @brief           Initializes the serial pheripheral and sets default parameters
 * 
 * @param obj       The serial object
 * @param tx        The TX pin name
 * @param rx        The RX pin name
 */
void serial_init(serial_t* obj, PinName tx, PinName rx);

/**
 * @brief           Releases the serial peripheral
 * 
 * @param obj       The serial object
 */ 
void serial_free(serial_t *obj);

/**
 * @brief           Reconfigures the serial baud rate
 *      
 * @param obj       The serial object
 * @param baudrate  The baudrate to set
 */
void serial_baud(serial_t* obj, uint32_t baudrate);

/** 
 * @brief           The serial interrupt handler registration
 *
 * @param obj       The serial object
 * @param handler   The interrupt handler which will be invoked when the interrupt fires
 * @param id        The SerialBase object
 */
void serial_irq_handler(serial_t *obj, uart_irq_handler handler, uint32_t id);

/** 
 * @brief           Checks if the serial peripheral is writable
 *
 * @param obj       The serial object
 * @return          Non-zero value if a character can be written, 0 otherwise.
 */
int serial_writable(serial_t *obj);

/** 
 * @brief           Checks if the serial peripheral is readable
 *
 * @param obj       The serial object
 * @return          Non-zero value if a character can be read, 0 if nothing to read
 */
int serial_readable(serial_t *obj);

/** 
 * @brief           Sends a character. This is a blocking call, waiting for a peripheral to be available
 *                  for writing
 *
 * @param obj       The serial object
 * @param c         The character to be sent
 */
void serial_putc(serial_t* obj, int c);

/** 
 * @brief           Get character. This is a blocking call, waiting for a character
 *
 * @param obj       The serial object
 */
int serial_getc(serial_t* obj);

/** 
 * @brief           Configures the serial interrupt. This function is used for word-approach
 *
 * @param obj       The serial object
 * @param irq       The serial IRQ type (RX or TX)
 * @param enable    Set to non-zero to enable events, or zero to disable them
 */
void serial_irq_set(serial_t *obj, SerialIrq irq, uint32_t enable);

/** 
 * @brief           Configure the serial for the flow control.
 *
 * @param obj       The serial object
 * @param type      The type of the flow control. Look at the available FlowControl types.
 * @param rxflow    The TX pin name
 * @param txflow    The RX pin name
 */
void serial_set_flow_control(serial_t *obj, FlowControl type, PinName rxflow, PinName txflow);

HAL_StatusTypeDef init_uart(serial_t* obj);

#ifdef __cplusplus
}
#endif

#endif // SERIAL_API_H_