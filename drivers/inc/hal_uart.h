/**
 * @file hal_uart.h
 * @brief Generic UART Hardware Abstraction Layer Interface
 * 
 * This file defines a platform-independent UART interface using function pointers.
 * Platform-specific implementations must provide hal_uart_get_interface() function.
 * 
 * @defgroup HAL_UART UART Hardware Abstraction Layer
 * @{
 */

#ifndef HAL_UART_H
#define HAL_UART_H

#include <stdint.h>

/**
 * @brief UART configuration structure
 */
struct uart_config {
    uint32_t baudrate;     /**< Baud rate (e.g., 9600, 115200) */
    uint8_t data_bits;     /**< Data bits: 7, 8, or 9 */
    uint8_t stop_bits;     /**< Stop bits: 1 or 2 */
    uint8_t parity;        /**< Parity: 0=None, 1=Even, 2=Odd */
};

/** @defgroup UART_Status UART Status Codes
 * @{
 */
#define UART_OK             0  /**< Operation successful */
#define UART_ERROR          1  /**< Generic error */
#define UART_TIMEOUT        2  /**< Operation timed out */
#define UART_BUSY           3  /**< Hardware busy */
/** @} */

/**
 * @brief UART HAL interface structure
 * 
 * Defines function pointers for all UART operations. Platform-specific
 * implementations must populate this structure.
 */
struct uart_hal_interface {
    /**
     * @brief Initialize UART instance
     * @param instance UART instance number
     * @param config Pointer to UART configuration
     * @return UART_OK on success, error code otherwise
     */
    uint8_t (*init)(uint8_t instance, const struct uart_config* config);
    
    /**
     * @brief Deinitialize UART instance
     * @param instance UART instance number
     */
    void (*deinit)(uint8_t instance);
    
    /**
     * @brief Write single byte (blocking)
     * @param instance UART instance number
     * @param data Byte to write
     * @return UART_OK on success, error code otherwise
     */
    uint8_t (*write_byte)(uint8_t instance, uint8_t data);
    
    /**
     * @brief Read single byte (blocking with timeout)
     * @param instance UART instance number
     * @param data Pointer to store received byte
     * @param timeout_ms Timeout in milliseconds
     * @return UART_OK on success, error code otherwise
     */
    uint8_t (*read_byte)(uint8_t instance, uint8_t* data, uint32_t timeout_ms);
    
    /**
     * @brief Write buffer (blocking)
     * @param instance UART instance number
     * @param data Pointer to data buffer
     * @param size Number of bytes to write
     * @return UART_OK on success, error code otherwise
     */
    uint8_t (*write)(uint8_t instance, const uint8_t* data, uint16_t size);
    
    /**
     * @brief Read buffer (blocking with timeout)
     * @param instance UART instance number
     * @param data Pointer to receive buffer
     * @param size Number of bytes to read
     * @param timeout_ms Timeout in milliseconds
     * @return UART_OK on success, error code otherwise
     */
    uint8_t (*read)(uint8_t instance, uint8_t* data, uint16_t size, uint32_t timeout_ms);
    
    /**
     * @brief Check if data is available to read
     * @param instance UART instance number
     * @return 1 if data available, 0 otherwise
     */
    uint8_t (*data_available)(uint8_t instance);
    
    /**
     * @brief Check if UART is ready to transmit
     * @param instance UART instance number
     * @return 1 if ready, 0 otherwise
     */
    uint8_t (*ready_to_send)(uint8_t instance);
};

/**
 * @brief Get the UART HAL interface for current platform
 * 
 * Platform-specific implementation must provide this function.
 * 
 * @return Pointer to platform's UART interface implementation
 */
const struct uart_hal_interface* hal_uart_get_interface(void);

/**
 * @brief Initialize UART instance
 * @param instance UART instance number
 * @param config Pointer to UART configuration
 * @return UART_OK on success, error code otherwise
 */
static inline uint8_t hal_uart_init(uint8_t instance, const struct uart_config* config) {
    return hal_uart_get_interface()->init(instance, config);
}

/**
 * @brief Deinitialize UART instance
 * @param instance UART instance number
 */
static inline void hal_uart_deinit(uint8_t instance) {
    hal_uart_get_interface()->deinit(instance);
}

/**
 * @brief Write single byte (blocking)
 * @param instance UART instance number
 * @param data Byte to write
 * @return UART_OK on success, error code otherwise
 */
static inline uint8_t hal_uart_write_byte(uint8_t instance, uint8_t data) {
    return hal_uart_get_interface()->write_byte(instance, data);
}

/**
 * @brief Read single byte (blocking with timeout)
 * @param instance UART instance number
 * @param data Pointer to store received byte
 * @param timeout_ms Timeout in milliseconds
 * @return UART_OK on success, error code otherwise
 */
static inline uint8_t hal_uart_read_byte(uint8_t instance, uint8_t* data, uint32_t timeout_ms) {
    return hal_uart_get_interface()->read_byte(instance, data, timeout_ms);
}

/**
 * @brief Write buffer (blocking)
 * @param instance UART instance number
 * @param data Pointer to data buffer
 * @param size Number of bytes to write
 * @return UART_OK on success, error code otherwise
 */
static inline uint8_t hal_uart_write(uint8_t instance, const uint8_t* data, uint16_t size) {
    return hal_uart_get_interface()->write(instance, data, size);
}

/**
 * @brief Read buffer (blocking with timeout)
 * @param instance UART instance number
 * @param data Pointer to receive buffer
 * @param size Number of bytes to read
 * @param timeout_ms Timeout in milliseconds
 * @return UART_OK on success, error code otherwise
 */
static inline uint8_t hal_uart_read(uint8_t instance, uint8_t* data, uint16_t size, uint32_t timeout_ms) {
    return hal_uart_get_interface()->read(instance, data, size, timeout_ms);
}

/**
 * @brief Check if data is available to read
 * @param instance UART instance number
 * @return 1 if data available, 0 otherwise
 */
static inline uint8_t hal_uart_data_available(uint8_t instance) {
    return hal_uart_get_interface()->data_available(instance);
}

/**
 * @brief Check if UART is ready to transmit
 * @param instance UART instance number
 * @return 1 if ready, 0 otherwise
 */
static inline uint8_t hal_uart_ready_to_send(uint8_t instance) {
    return hal_uart_get_interface()->ready_to_send(instance);
}

/** @} */ // end of HAL_UART group

#endif // HAL_UART_H
