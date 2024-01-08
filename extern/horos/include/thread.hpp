#ifndef THREAD_HPP
#define THREAD_HPP

#include <stdint.h>

#include <functional>

#include "kernel_common.hpp"
#include "kernel.hpp"

namespace horos
{

class Thread
{
public:

    enum class Priority : uint8_t
    {
        Normal = 1,
    };

public:
    Thread(uint32_t stackSize, Priority priority, const char* name);

    template<class O>
    void RunTask(O* obj, void (O::*func )(void))
    {
        // auto func1 = [obj, func]() { return (obj->*func)(); };

        // Optimization:
        // if the capture is too large, std::function will allocate on the heap.
        // To avoid this, we only pass a reference of the function pointer.
        // That is ok because we refer to an existing function with defined storage
        auto f2 = [obj, &func](){  return (obj->*func)(); };
        _task = f2;

        // TODO: STD FUNCTION PROBABLY NOT THE RIGHT TOOL HERE, USE Callbacks from ... (needs to be added)

        // if (!IS_IRQ_MODE() && (func) != nullptr)
        // {
        
        // }
          
        // UINT status = tx_thread_create(
        //     threadPtr, 
        //     _name, // OK
        //     (void(*)(ULONG id))func,
        //     entryInput,
        //     stackStart,
        //     stackSize,
        //     _priority,
        //     _priority,
        //     THREADX_DEFAULT_TIME_SLICE,
        //     TX_AUTO_START
        //     )
        
        // if (status != TX_SUCCESS)
        // {
        //     return
        // }
   
    }

private:
        std::function<void()> _task;
        uint32_t _stackSize;
        uint32_t _cbSize;
        Priority _priority;
        const char* _name;

};


}

#endif // THREAD_HPP