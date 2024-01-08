#include "app.hpp"
// #include "tx_api.h"

using namespace horos;

void app_run()
{//Definition für deklaration in app.h
    

    App::Run();
}

void mainTask()
{
    // int* test = new int();
    // test++;
    

}

void MainThread::Func()
{

}

void App::Run() 
{
    Kernel::Initialize();
    char test[] = "te";

    MainThread mainThread;

    Thread thread(3, Thread::Priority::Normal, test);
    thread.RunTask(&mainThread, &MainThread::Func);

    // Kernel::Start();
    // _tx_initialize_kernel_setup();



    DigitalOut out(PA_5, 1);

    // osThreadAttr_t attr;
    // attr.stack_size = 1024;
    // attr.priority = osPriorityNormal;
    // attr.name = "testThread";


    // osThreadNew(threadFunc, nullptr, &attr);

    while (1)
    {
        // serial_putc(&uart, '5');
        // out.write(1);

        // tx_time_get();

        // tx_thread_sleep(10);
        // out.write(0);
        // tx_thread_sleep(10);
    }
}