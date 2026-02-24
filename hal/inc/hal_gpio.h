/**
 * @file hal_gpio.h
 * @brief Generic GPIO Hardware Abstraction Layer Interface
 * 
 * This file defines a platform-independent GPIO interface using function pointers.
 * Platform-specific implementations must provide hal_gpio_get_interface() function.
 * 
 * @defgroup HAL_GPIO GPIO Hardware Abstraction Layer
 * @{
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H

#include<stdint.h>


typedef struct
{
	uint32_t	pin;
	uint32_t	port;
	uint32_t	pinState;
	uint32_t	pinConfig;
	uint32_t	alternate_mode;

}gpio_config;

extern gpio_config gpioConfig[];


/** @defgroup GPIO_Status GPIO Status Codes
 * @{
 */
#define GPIO_OK             0  /**< Operation successful */
#define GPIO_ERROR          1  /**< Generic error */
#define GPIO_TIMEOUT        2  /**< Operation timed out */
#define GPIO_BUSY           3  /**< Hardware busy g/
g** @} */

typedef enum
{
	AF0 = 0,
	AF1,
	AF2,
	AF3,
	AF4,
	AF5,
	AF6,
	AF7
}alt_func_t;


/** @defgroup GPIO_PINS GPIO Pin Codes
 * @{
 */
#define PIN0			0x0
#define PIN1			0x1
#define PIN2			0x2
#define PIN3			0x3
#define PIN4			0x4
#define PIN5			0x5
#define PIN6			0x6
#define PIN7			0x7 
#define PIN8			0x8 
#define PIN9			0x9 
#define PIN10			0xA 
#define PIN11			0xB 
#define PIN12			0xC 
#define PIN13			0xD 
#define PIN14			0xE 
#define PIN15			0xF 
/** @} */

/** @defgroup GPIO_MODES GPIO Mode Codes
 * @{
 */
#define INPUT_MODE 		(0x0 << MODE_SHIFT)
#define OUTPUT_MODE 	(0x1 << MODE_SHIFT)
#define ALTERNATE_MODE 	(0x2 << MODE_SHIFT)
#define ANALOG_MODE 	(0x3 << MODE_SHIFT)
#define MODE_MASK		0x3
#define MODE_SHIFT		4
/** @} */


/** @defgroup GPIO_SPEED GPIO Speed Codes
 * @{
 */
#define VERY_LOW_SPEED	(0x0 << SPEED_SHIFT)
#define LOW_SPEED		(0x1 << SPEED_SHIFT)				
#define HIGH_SPEED		(0x2 << SPEED_SHIFT)
#define VERY_HIGH_SPEED	(0x3 << SPEED_SHIFT)
#define SPEED_MASK		0x3
#define SPEED_SHIFT		6
/** @} */

/** @defgroup GPIO_PUPDR GPIO Pull Direction Codes
 * @{
 */
#define	NO_PULL			(0x0 << PULL_SHIFT)
#define PULL_DOWN		(0x1 << PULL_SHIFT)
#define	PULL_UP			(0x2 << PULL_SHIFT)
#define	PULL_MASK		0x3
#define PULL_SHIFT		8
/** @} */


/**
 * @brief GPIO HAL interface structure
 * 
 * Defines function pointers for all GPIO operations. Platform-specific
 * implementations must populate this structure.
 */

struct gpio_hal_interface {
    /**
	 * @brief Initialize GPIO instance
     * @param instance GPIO instance number
     * @param instance GPIO pin number
	 * @param pin config (Mode | Speed | Pull)
     * @return GPIO_OK on success, error code otherwise
     */
    uint8_t (*init)(uint32_t index);
    
    /**
     * @brief Deinitialize GPIO instance
     * @param instance GPIO instance number
     * @param instance GPIO pin number
     */
    void (*deinit)(uint32_t index);
    
    /**
	 * @brief Set pin value
     * @param instance GPIO instance number
     * @param instance GPIO pin number
     * @param pin value to write
     * @return GPIO_OK on success, error code otherwise
     */
    uint8_t (*pin_set)(uint32_t index, uint32_t pin_val);
    
    /**
	 * @brief Read Pin value 
     * @param instance GPIO instance number
     * @param pin Pointer to store received bit
     * @param timeout_ms Timeout in milliseconds
     * @return GPIO_OK on success, error code otherwise
     */
    uint8_t (*pin_read)(uint32_t index, uint32_t *pin_value);
	


    uint8_t (*pin_toggle)(uint32_t index);
    
};

/**
 * @brief Get the GPIO HAL interface for current platform
 * 
 * Platform-specific implementation must provide this function.
 * 
 * @return Pointer to platform's GPIO interface implementation
 */
const struct gpio_hal_interface* hal_gpio_get_interface(void);

/**
 * @brief Initialize GPIO instance
 * @param instance GPIO instance number
 * @param instance GPIO pin number
 * @param config Pointer to GPIO configuration
 * @return UART_OK on success, error code otherwise
 */
static inline uint8_t hal_gpio_init(uint32_t index) {
    return hal_gpio_get_interface()->init(index);
}

/**
 * @brief Deinitialize UART instance
 * @param instance GPIO instance number
 * @param instance GPIO pin number
 */
static inline void hal_gpio_deinit(uint32_t index) {
    hal_gpio_get_interface()->deinit(index);
}

/**
 * @brief Set pin value
 * @param instance GPIO instance number
 * @param instance GPIO pin number
 * @param pin value to write
 * @return GPIO_OK on success, error code otherwise
 */
static inline uint8_t hal_gpio_pin_set(uint32_t index, uint32_t pin_val) {
	return hal_gpio_get_interface()->pin_set(index, pin_val);
}

/**
 * @brief Read Pin value 
 * @param instance GPIO instance number
 * @param pin Pointer to store received bit
 * @param timeout_ms Timeout in milliseconds
 * @return GPIO_OK on success, error code otherwise
 */
static inline uint8_t hal_gpio_pin_read(uint32_t index, uint32_t *pin_val) {
	return hal_gpio_get_interface()->pin_read(index, pin_val);
}

static inline uint8_t hal_gpio_pin_toggle(uint32_t index) {
	return hal_gpio_get_interface()->pin_toggle(index);
}

#endif
