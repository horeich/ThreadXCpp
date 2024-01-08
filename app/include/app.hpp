#ifndef _APP_H_
#define _APP_H_

#include "kernel.hpp"

#include "digitalOut.hpp"

#include "thread.hpp"

#include "cmsis_os2.h"

void app_run();

class App
{
public:
    static void Run();

    
};

class MainThread
{
public:
    void Func();
};

#endif // _APP_H_