#include "retarget.hpp"

#include "tx_api.h"

void *operator new (std::size_t count)
{
    if (count < TX_BYTE_POOL_MIN)
    {
      /* We should at least allocate TX_BYTE_POOL_MIN */
    //   allocated_mem_size = TX_BYTE_POOL_MIN;
    }

    return (void*)1;
}