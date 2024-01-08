// #include "stm32l4xx_hal.h"

#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

// #define THREAD_STACK_SIZE 2048
// #define THREAD_POOL_SIZE 9120
// #define AZURE_THREAD_PRIORITY 4

// TX_THREAD thread0;


// UCHAR memory_area[THREAD_POOL_SIZE];

// ULONG azure_thread_stack[THREAD_STACK_SIZE / sizeof(ULONG)];

// static void thread0_entry(ULONG parameter)
// {
//   // serial_t uart;
//   // serial_init(&uart, PA_2, PA_3);

//   app_run();
//   // tx_time_get();

//   // tx_time_get();

//   // tx_time_get();

//   // HAL_GetTick();

//   // tx_thread_sleep(2);
//   // if (status != TX_SUCCESS)

 

//   // UINT status;

//   // printf("Starting Azure thread\r\n\r\n");

//   // // Initialize the network
//   // if ((status = stm_network_init(WIFI_SSID, WIFI_PASSWORD, WIFI_MODE)))
//   // {
//   //     printf("ERROR: Failed to initialize the network (0x%08x)\r\n", status);
//   // }

//   // else if ((status = azure_iot_nx_client_entry(&nx_ip, &nx_pool, &nx_dns_client, sntp_time)))
//   // {
//   //     printf("ERROR: Failed to run Azure IoT (0x%04x)\r\n", status);
//   // }
// }

void threadFunc(void* arg)
{

}

/*
  No HAL API calls in here!
*/
// void tx_application_define(void *first_unused_memory)
// {
  // osKernelInitialize();

  // osThreadAttr_t attr;
  // attr.stack_size = 1024;
  // attr.priority = osPriorityNormal;
  // attr.name = "testThread";

  // osThreadNew(threadFunc, nullptr, &attr);


  // Create main thread here
  // int* test = new int(3);
  // test++;

  // char byte_pool_0_name[12] = "byte pool 0";

  // // Byte pool for all threads
  
  // TX_BYTE_POOL byte_pool_0;
  
  // UINT status = tx_byte_pool_create(
  //     &byte_pool_0,
  //     byte_pool_0_name,
  //     first_unused_memory,
  //     2048);

  // if (status != TX_SUCCESS)
  // {
  //   return;
  // }

  // // Allocate the stack for thread 0.
  // CHAR *pointer; //= TX_NULL;
  // status = tx_byte_allocate(&byte_pool_0, (VOID **)&pointer, THREAD_STACK_SIZE, TX_NO_WAIT);
  // if (status != TX_SUCCESS)
  // {
  //   return;
  // }

  // char thread0Name[] = "thread0";

  // // Create Azure thread
  // status = tx_thread_create(&thread0,
  //                           thread0Name,
  //                           thread0_entry,
  //                           0,
  //                           pointer,
  //                           2048,
  //                           1,
  //                           1,
  //                           TX_NO_TIME_SLICE,
  //                           TX_AUTO_START);

  // if (status != TX_SUCCESS)
  // {
  //   return;
  //   // printf("ERROR: Azure IoT thread creation failed\r\n");
  // }

  // int x = 0;
  // x++;
// }



int main(void)
{
  // SystemCoreClockUpdate();
  HAL_Init(); // calls HAL_InitTick

  set_sys_clock_pll_msi();

  // HAL_DBGMCU_DisableDBGStopMode();

  MX_GPIO_Init();
  // MX_USART2_UART_Init();
  HAL_GetTick();

  // serial_t uart;
  // serial_init(&uart, PA_2, PA_3);
  
  

  // serial_putc(&uart, '5');
  HAL_GetTick();

 
  // The scheduler now takes over control of the application
  app_run();
  // osKernelInitialize();

  // osThreadAttr_t attr;
  // attr.stack_size = 1024;
  // attr.priority = osPriorityNormal;
  // attr.name = "testThread";

  // osThreadNew(threadFunc, nullptr, &attr);

  // osKernelStart();
  // tx_kernel_enter();


  return 0;
}

void HAL_MspInit(void)
{
  /* USER CODE BEGIN MspInit 0 */

  /* USER CODE END MspInit 0 */

  __HAL_RCC_SYSCFG_CLK_ENABLE();
  __HAL_RCC_PWR_CLK_ENABLE();

  /* System interrupt init*/

  /* USER CODE BEGIN MspInit 1 */

  /* USER CODE END MspInit 1 */
}

/**
* @brief RNG MSP Initialization
* This function configures the hardware resources used in this example
* @param hrng: RNG handle pointer
* @retval None
*/
// void HAL_RNG_MspInit(RNG_HandleTypeDef* hrng)
// {
//   RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
//   if(hrng->Instance==RNG)
//   {
//   /* USER CODE BEGIN RNG_MspInit 0 */

//   /* USER CODE END RNG_MspInit 0 */
//   /** Initializes the peripherals clock
//   */
//     PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RNG;
//     PeriphClkInit.RngClockSelection = RCC_RNGCLKSOURCE_PLLSAI1;
//     PeriphClkInit.PLLSAI1.PLLSAI1Source = RCC_PLLSOURCE_MSI;
//     PeriphClkInit.PLLSAI1.PLLSAI1M = 6;
//     PeriphClkInit.PLLSAI1.PLLSAI1N = 12;
//     PeriphClkInit.PLLSAI1.PLLSAI1P = RCC_PLLP_DIV7;
//     PeriphClkInit.PLLSAI1.PLLSAI1Q = RCC_PLLQ_DIV2;
//     PeriphClkInit.PLLSAI1.PLLSAI1R = RCC_PLLR_DIV2;
//     PeriphClkInit.PLLSAI1.PLLSAI1ClockOut = RCC_PLLSAI1_48M2CLK;
//     if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
//     {
//       Error_Handler();
//     }

//     /* Peripheral clock enable */
//     __HAL_RCC_RNG_CLK_ENABLE();
//   /* USER CODE BEGIN RNG_MspInit 1 */

//   /* USER CODE END RNG_MspInit 1 */
//   }

// }

/**
* @brief RNG MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hrng: RNG handle pointer
* @retval None
*/
// void HAL_RNG_MspDeInit(RNG_HandleTypeDef* hrng)
// {
//   if(hrng->Instance==RNG)
//   {
//   /* USER CODE BEGIN RNG_MspDeInit 0 */

//   /* USER CODE END RNG_MspDeInit 0 */
//     /* Peripheral clock disable */
//     __HAL_RCC_RNG_CLK_DISABLE();
//   /* USER CODE BEGIN RNG_MspDeInit 1 */

//   /* USER CODE END RNG_MspDeInit 1 */
//   }

// }

/* Includes ------------------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim6;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
 * @brief  This function configures the TIM6 as a time base source.
 *         The time source is configured  to have 1ms time base with a dedicated
 *         Tick interrupt priority.
 * @note   This function is called  automatically at the beginning of program after
 *         reset by HAL_Init() or at any time when clock is configured, by HAL_RCC_ClockConfig().
 * @param  TickPriority: Tick interrupt priority.
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority)
{
  RCC_ClkInitTypeDef clkconfig;
  uint32_t uwTimclock, uwAPB1Prescaler;

  uint32_t uwPrescalerValue;
  uint32_t pFLatency;
  HAL_StatusTypeDef status = HAL_OK;

  /* Enable TIM6 clock */
  __HAL_RCC_TIM6_CLK_ENABLE();

  /* Get clock configuration */
  HAL_RCC_GetClockConfig(&clkconfig, &pFLatency);

  /* Get APB1 prescaler */
  uwAPB1Prescaler = clkconfig.APB1CLKDivider;
  /* Compute TIM6 clock */
  if (uwAPB1Prescaler == RCC_HCLK_DIV1)
  {
    uwTimclock = HAL_RCC_GetPCLK1Freq();
  }
  else
  {
    uwTimclock = 2UL * HAL_RCC_GetPCLK1Freq();
  }

  /* Compute the prescaler value to have TIM6 counter clock equal to 1MHz */
  uwPrescalerValue = (uint32_t)((uwTimclock / 1000000U) - 1U);

  /* Initialize TIM6 */
  htim6.Instance = TIM6;

  /* Initialize TIMx peripheral as follow:

  + Period = [(TIM6CLK/1000) - 1]. to have a (1/1000) s time base.
  + Prescaler = (uwTimclock/1000000 - 1) to have a 1MHz counter clock.
  + ClockDivision = 0
  + Counter direction = Up
  */
  htim6.Init.Period = (1000000U / 1000U) - 1U;
  htim6.Init.Prescaler = uwPrescalerValue;
  htim6.Init.ClockDivision = 0;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

  status = HAL_TIM_Base_Init(&htim6);
  if (status == HAL_OK)
  {
    /* Start the TIM time Base generation in interrupt mode */
    status = HAL_TIM_Base_Start_IT(&htim6);
    if (status == HAL_OK)
    {
      /* Enable the TIM6 global Interrupt */
      HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);
      /* Configure the SysTick IRQ priority */
      if (TickPriority < (1UL << __NVIC_PRIO_BITS))
      {
        /* Configure the TIM IRQ priority */
        HAL_NVIC_SetPriority(TIM6_DAC_IRQn, TickPriority, 0U);
        uwTickPrio = TickPriority;
      }
      else
      {
        status = HAL_ERROR;
      }
    }
  }

  /* Return function status */
  return status;
}

void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

void Error_Handler(void) {
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1) {
    }
    /* USER CODE END Error_Handler_Debug */
}


/**
 * @brief  Suspend Tick increment.
 * @note   Disable the tick increment by disabling TIM6 update interrupt.
 * @param  None
 * @retval None
 */
void HAL_SuspendTick(void)
{
  /* Disable TIM6 update Interrupt */
  __HAL_TIM_DISABLE_IT(&htim6, TIM_IT_UPDATE);
}

/**
 * @brief  Resume Tick increment.
 * @note   Enable the tick increment by Enabling TIM6 update interrupt.
 * @param  None
 * @retval None
 */
void HAL_ResumeTick(void)
{
  /* Enable TIM6 Update interrupt */
  __HAL_TIM_ENABLE_IT(&htim6, TIM_IT_UPDATE);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* Prevent unused argument(s) compilation warning */
  // UNUSED(htim);

  if (htim->Instance == TIM6) {
    HAL_IncTick();
  }
}

/**
  * @brief  This function handles TIM interrupt request.
  * @retval None
  */
void TIM6_DAC_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&htim6);
}

#ifdef __cplusplus
}
#endif