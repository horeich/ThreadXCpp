#include "thread.hpp"

using namespace horos;

Thread::Thread(uint32_t stackSize, Priority priority, const char* name) :
    _stackSize(stackSize),
    _priority(priority),
    _name(name)
{
}

