#ifndef KERNEL_COMMON_HPP
#define KERNEL_COMMON_HPP

#include <stdint.h>

// #define IS_IRQ_MODE()                           (__get_IPSR() != 0U) // Interrupt Program Status Register

#define THREADX_DEFAULT_TIME_SLICE                4

namespace horos
{

enum class ThreadError : uint8_t
{
    None,
};

}

#endif // KERNEL_COMMON_HPP