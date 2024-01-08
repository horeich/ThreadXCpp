/**
 * @file                digital_out.hpp
 * @author              Simon Schrampfer, Andreas Reichle
 * @brief
 * @version             0.1
 * @date                2021-04-12
 *
 * @copyright           All rights reserved
 *
 */

#ifndef DIGITAL_OUT_H_
#define DIGITAL_OUT_H_

#include "gpio_api.h"

class DigitalOut {
  public:
    DigitalOut(PinName pin);
    DigitalOut(PinName pin, int value);
    ~DigitalOut() = default;

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
    DigitalOut &operator=(int value) {
        write(value);
        return *this;
    }

    /**
     * @brief           A shorthand for write() using the assignment operator which copies the
     *                  state from the DigitalInOut argument.
     *
     * @param rhs       The DigitalOut object to copy state from
     */
    DigitalOut &operator=(DigitalOut &rhs);

  protected:
    // #if !defined(DOXYGEN_ONLY)
    gpio_t gpio;
    // #endif // !defined(DOXYGEN_ONLY)
};

#endif // DIGITAL_OUT_H_
