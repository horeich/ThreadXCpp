/**
 * @file                digital_in_out.h
 * @author              Simon Schrampfer, Andreas Reichle
 * @brief
 * @version             0.1
 * @date                2021-04-18
 *
 * @copyright           All rights reserved
 *
 */

#ifndef DIGITAL_IN_OUT_H_
#define DIGITAL_IN_OUT_H_

#include "gpio_api.h"

class DigitalInOut {
  public:
    /**
     * @brief               Create a DigitalInOut connected to the specified pin
     *
     * @param pin           DigitalInOut pin to connect to
     */
    // DigitalInOut(PinName pin);

    /**
     * @brief               DigitalInOut connected to the specified pin
     *
     * @param pin          DigitalInOut pin to connect to
     * @param direction    the initial direction of the pin
     * @param mode         the initial mode of the pin
     * @param value        the initial value of the pin if is an output
     */
    DigitalInOut(PinName pin, PinDirection direction, PinMode mode, int value);

    /**
     * @brief           Sets the output to logical 0 (low) or 1 (high)
     *
     * @param value     0 for logical 0, 1 for logical 1
     */
    void write(int value);

    /**
     * @brief           Returns the output state of the pin (high/low)
     *
     * @return int      1 for logical 1 (high), 0 for logical 0 (low)
     */
    int read();

    /**
     * @brief           Sets the pin as output pin (push-pull logic)
     *
     */
    void output();

    /**
     * @brief           Sets the pin as input pin (open-drain logic)
     *
     */
    void input();

    /**
     * @brief           Sets the input mode
     *
     * @param pull      PullUp, PullDown, PullNone, OpenDrain
     */
    void mode(PinMode pull);

    /**
     * @brief           Returns the output setting
     *
     * @return int      Non-zero value if pin is connected, 0 if initialized with NC
     */
    int is_connected();

    /**
     * @brief           A shorthand for read()
     *
     * @return int      1 for logical 1 (high), 0 for logical 0 (low)
     */
    operator int() { return read(); }

    /**
     * @brief           A shorthand for write()
     * 
     * @param value     1 for logical 1 (high), 0 for logical 0 (low) 
     * 
     */
    DigitalInOut &operator=(int value) {
        write(value);
        return *this;
    }

    /**
     * @brief           A shorthand for write() using the assignment operator which copies the
     *                  state from the DigitalInOut argument.
     *
     * @param rhs       The DigitalOut object to copy state from
     * 
     */
    DigitalInOut &operator=(DigitalInOut &rhs);

  protected:
    // #if !defined(DOXYGEN_ONLY)
    gpio_t gpio;
    // #endif // !defined(DOXYGEN_ONLY)
};

#endif // DIGITAL_IN_OUT_H_
