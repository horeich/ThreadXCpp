/**
 * @file                digital_out.cpp
 * @author              Simon Schrampfer, Andreas Reichle
 * @brief
 * @version             0.1
 * @date                2021-04-18
 *
 * @copyright           All rights reserved
 *
 */

#include "digitalOut.hpp"

DigitalOut::DigitalOut(PinName pin) : gpio() { gpio_init_out(&gpio, pin); }

DigitalOut::DigitalOut(PinName pin, int value) : gpio() { gpio_init_out_ex(&gpio, pin, value); }

void DigitalOut::write(int value) { gpio_write(&gpio, value); }

int DigitalOut::read() { return gpio_read(&gpio); }

int DigitalOut::is_connected() { return gpio_is_connected(&gpio); }

DigitalOut &DigitalOut::operator=(DigitalOut &rhs) {
    write(rhs.read());
    return *this;
}

