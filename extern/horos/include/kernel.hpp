#ifndef KERNEL_HPP
#define KERNEL_HPP

// #include "cmsis_compiler.h"

#include "retarget.hpp"

// Make sure to include with C linkage as threadX libs do not feature extern "C"
#ifdef __cplusplus
extern "C" {
#endif

#include "tx_initialize.h"

#include "tx_api.h"
#include "tx_port.h"
#include "tx_thread.h"

#ifdef __cplusplus
}
#endif

// #define IS_IRQ_MODE()                           (__get_IPSR() != 0U)

namespace horos
{

class Kernel
{
public:
    Kernel();

    static void Initialize();

    static void Start();
};

}

#endif // KERNEL_HPP