#include "system_clock.h"

uint8_t set_sys_clock_pll_msi(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    // Error_Handler();
  }
  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE|RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_11;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 6;
  RCC_OscInitStruct.PLL.PLLN = 20;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    // Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    // Error_Handler();
  }
  /** Enable MSI Auto calibration
  */
  HAL_RCCEx_EnableMSIPLLMode();
//     RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
//     RCC_OscInitTypeDef RCC_OscInitStruct = {0};
//     // RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

// // #if MBED_CONF_TARGET_LSE_AVAILABLE
//     // Enable LSE Oscillator to automatically calibrate the MSI clock
//     RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE;
//     RCC_OscInitStruct.PLL.PLLState   = RCC_PLL_NONE; // No PLL update
//     RCC_OscInitStruct.LSEState       = RCC_LSE_ON; // External 32.768 kHz clock on OSC_IN/OSC_OUT
//     if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
//         return 0; // FAIL
//     }

//     /* Enable the CSS interrupt in case LSE signal is corrupted or not present */
//     HAL_RCCEx_DisableLSECSS();
// // #endif /* MBED_CONF_TARGET_LSE_AVAILABLE */

//     /* Enable MSI Oscillator and activate PLL with MSI as source */
//     RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE|RCC_OSCILLATORTYPE_MSI;
//     RCC_OscInitStruct.LSEState = RCC_LSE_ON;
//     RCC_OscInitStruct.MSIState = RCC_MSI_ON;
//     RCC_OscInitStruct.MSICalibrationValue = 0;
//     RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_11;
//     RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
//     RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
//     RCC_OscInitStruct.PLL.PLLM = 6;
//     RCC_OscInitStruct.PLL.PLLN = 20;
//     RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
//     RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
//     RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
//     if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
//         return 0; // FAIL
//     }

// #if MBED_CONF_TARGET_LSE_AVAILABLE
//     /* Enable MSI Auto-calibration through LSE */
//     HAL_RCCEx_EnableMSIPLLMode();
// #endif /* MBED_CONF_TARGET_LSE_AVAILABLE */

// #if DEVICE_USBDEVICE
//     /* Select MSI output as USB clock source */
//     PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USB;
//     PeriphClkInitStruct.UsbClockSelection = RCC_USBCLKSOURCE_MSI; /* 48 MHz */
//     HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);
// #endif /* DEVICE_USBDEVICE */

//     // Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers
//     RCC_ClkInitStruct.ClockType      = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
//     RCC_ClkInitStruct.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK; /* 80 MHz */
//     RCC_ClkInitStruct.AHBCLKDivider  = RCC_SYSCLK_DIV1;         /* 80 MHz */
//     RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;           /* 80 MHz */
//     RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;           /* 80 MHz */
//     if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK) {
//         return 0; // FAIL
//     }

//     // Output clock on MCO1 pin(PA8) for debugging purpose
// #if DEBUG_MCO == 4
//     HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO1SOURCE_MSI, RCC_MCODIV_2); // 2 MHz
// #endif

     return 1; // OK
}