
## Setup threadX for GCC

* For STM32CubeIDE add the following section into the .ld file:
       ._threadx_heap :
         {
            . = ALIGN(8);
            __RAM_segment_used_end__ = .;
            . = . + 64K;
            . = ALIGN(8);
          } >RAM_D1 AT> RAM_D1
      * The simplest way to provide memory for ThreadX is to define a new section, see ._threadx_heap above.
      * In the example above the ThreadX heap size is set to 64KBytes.
      * The ._threadx_heap must be located between the .bss and the ._user_heap_stack sections in the linker script.
      * Caution: Make sure that ThreadX does not need more than the provided heap memory (64KBytes in this example).
      * Read more in STM32CubeIDE User Guide, chapter: "Linker script".


* uncomment USER_VECT_TAB_ADDRESS

ThreadX uses following interrupts: SysTick, PendSV and SVCall with the last two being invoked exclusively from process context, to my understanding. The only one occurring asynchronously to the thread execution is periodic SysTick interrupt, which will fire every 10ms by default. This interrupt drives the timeouts, time-slicing and some pre-emption cases. Because a fair bit of RTOS housekeeping is handled inside its context, we recommend that any user-configured interrupts are set to the higher priority so that they're executed first (hence the lowest interrupt for CM4 and CM0+ is said to be "not valid if using ThreadX").

The CM4 core support 16 interrupt levels, 15 being the lowest.
The CM0 core support 4 interrupt levels, 3 being the lowest.
ThreadX uses the lowest interrupt level to operate the RTOS so is unavailable to the user application.
All other interrupt levels will cause a switch from the user application which will include ThreadX code.
Interrupt routines with a higher priority will interrupt lower priority interrupt routines.

In general, blocks are allocated from the heap, a large area of memory in your program's address space. The library manages the heap for you, usually using system calls like sbrk or mmap. One approach to allocating blocks from the heap is to maintain a list of free and allocated blocks which stores block sizes and locations. Initially, the list might contain one big block for the whole heap. When a new block is requested, the allocator will select a free block from the list. If the block is too large, it can be split into two blocks (one of the requested size, the other of whatever size is left). When an allocated block is freed, it can be merged with adjacent free blocks, since having one big free block is more useful than several small free blocks. The actual list of blocks can be stored as separate data structures or embedded into the heap.