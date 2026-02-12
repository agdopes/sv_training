/**
 * @file hal_uart_config.h
 * @brief UART HAL Configuration
 * 
 * Select backend implementation by uncommenting one of the HAL_UART_BACKEND_* defines.
 * Configure maximum instances and default timeout values.
 */

#ifndef HAL_UART_CONFIG_H
#define HAL_UART_CONFIG_H

/**
 * @defgroup HAL_UART_Config UART HAL Configuration
 * @{
 */

/**
 * @brief Backend selection - STM32F411RE hardware
 */
#define HAL_UART_BACKEND_STM32F411     /**< STM32F411RE hardware backend */

/**
 * @brief Maximum number of UART instances supported
 */
#define HAL_UART_MAX_INSTANCES  3

/**
 * @brief Default timeout for blocking operations (milliseconds)
 */
#define HAL_UART_DEFAULT_TIMEOUT_MS  1000

/** @} */ // end of HAL_UART_Config group

#endif // HAL_UART_CONFIG_H
