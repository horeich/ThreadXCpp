#include "kernel.hpp"

/* CMSIS compiler specific defines */
// #include "cmsis_compiler.h"

using namespace horos;

VOID tx_application_define(VOID *first_unused_memory)
{
  /* Empty tx_application_define() */
}

// static TX_BYTE_POOL txfr_heap;
Kernel::Kernel()
{
}

void Kernel::Initialize()
{
    // if (IS_IRQ_MODE())
    // {
    //     return;
    // }

    // TODO: Check status (already init, or inactive -> then init)

    // Call initialize to be able to create byte pool
   
    _tx_initialize_kernel_setup();

    // Allocate memory

    CHAR *heap_start_ptr = nullptr;
    heap_start_ptr = (CHAR *)_tx_initialize_unused_memory;

    char poolName[] = "txfr_byte_pool";
    TX_BYTE_POOL txfr_heap;
    UINT status = tx_byte_pool_create(&txfr_heap, poolName, heap_start_ptr, 8192);
    if (status != TX_SUCCESS)
    {
        return;
    }

    _tx_initialize_unused_memory = heap_start_ptr + 8192;
}

void Kernel::Start()
{
    // Start scheduling
    tx_kernel_enter();

    // We will never end up here
}