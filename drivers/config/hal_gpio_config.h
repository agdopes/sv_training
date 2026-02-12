/**
 * @file hal_GPIO_config.h
 * @brief GPIO HAL Configuration
 * 
 * Select backend implementation by uncommenting one of the HAL_GPIO_BACKEND_* defines.
 * Configure maximum instances and default timeout values.
 */

#ifndef HAL_GPIO_CONFIG_H
#define HAL_GPIO_CONFIG_H

/**
 * @defgroup HAL_GPIO_Config GPIO HAL Configuration
 * @{
 */

/**
 * @brief Backend selection - STM32G0B1RE hardware
 */
#define HAL_GPIO_BACKEND_STM32G0B1     /**< STM32G0B1RE hardware backend */

/**
 * @brief Maximum number of GPIO instances supported
 */
#define HAL_GPIO_MAX_INSTANCES  6

/**
 * @brief Default timeout for blocking operations (milliseconds)
 */
#define HAL_GPIO_DEFAULT_TIMEOUT_MS  1000

/** @} */ // end of HAL_GPIO_Config group

#endif // HAL_GPIO_CONFIG_H
