/**
 * @file                digital_in_out.cpp
 * @author              Simon Schrampfer, Andreas Reichle
 * @brief   
 * @version             0.1
 * @date                2021-04-12
 *  
 * @copyright           All rights reserved
 *
 */

#include "digitalInOut.hpp"

// DigitalInOut(PinName pin) : gpio() {
//     gpio_init_in(&gpio, pin);
// }

DigitalInOut::DigitalInOut(PinName pin, PinDirection direction, PinMode mode, int value) : gpio() {
    gpio_init_inout(&gpio, pin, direction, mode, value);
}

void DigitalInOut::write(int value) { gpio_write(&gpio, value); }

int DigitalInOut::read() { return gpio_read(&gpio); }

void DigitalInOut::input() { gpio_dir(&gpio, PIN_INPUT); }

void DigitalInOut::output() { gpio_dir(&gpio, PIN_OUTPUT); }

void DigitalInOut::mode(PinMode pull) { gpio_mode(&gpio, pull); }

int DigitalInOut::is_connected() { return gpio_is_connected(&gpio); }

DigitalInOut &DigitalInOut::operator= (DigitalInOut &rhs)
{
    write(rhs.read());
    return *this;
}