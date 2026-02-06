/**
 * @file hal_uart_stm32f411.c
 * @brief UART HAL implementation for STM32F411RE
 * 
 * Provides hardware-specific UART implementation for STM32F411RE microcontroller.
 * Implements the uart_hal_interface for direct register access.
 * 
 * @defgroup HAL_UART_STM32F411 STM32F411 UART Implementation
 * @ingroup HAL_UART
 * @{
 */

#include "hal_uart.h"
#include "hal_uart_config.h"

#ifdef HAL_UART_BACKEND_STM32F411

/** @defgroup STM32F411_Registers STM32F411 Register Definitions
 * @{
 */
#define USART1_BASE         0x40011000UL
#define USART2_BASE         0x40004400UL
#define USART6_BASE         0x40011400UL
#define RCC_BASE            0x40023800UL

#define RCC_APB1ENR         (*(volatile uint32_t*)(RCC_BASE + 0x40))
#define RCC_APB2ENR         (*(volatile uint32_t*)(RCC_BASE + 0x44))

// UART Register offsets
#define USART_SR    0x00
#define USART_DR    0x04
#define USART_BRR   0x08
#define USART_CR1   0x0C
#define USART_CR2   0x10

// Status register bits
#define SR_TXE      (1 << 7)
#define SR_TC       (1 << 6)
#define SR_RXNE     (1 << 5)

// Control register bits
#define CR1_UE      (1 << 13)
#define CR1_M       (1 << 12)
#define CR1_PCE     (1 << 10)
#define CR1_PS      (1 << 9)
#define CR1_TE      (1 << 3)
#define CR1_RE      (1 << 2)

// RCC APB enable bits
#define RCC_APB2ENR_USART1EN (1 << 4)  /**< USART1 clock enable */
#define RCC_APB1ENR_USART2EN (1 << 17) /**< USART2 clock enable */
#define RCC_APB2ENR_USART6EN (1 << 5)  /**< USART6 clock enable */
/** @} */ // end of STM32F411_Registers group

/** @brief Default APB1 clock frequency (16 MHz HSI) */
static uint32_t g_apb1_clock = 16000000;

/** @brief Default APB2 clock frequency (16 MHz HSI) */
static uint32_t g_apb2_clock = 16000000;

/**
 * @brief Get UART base address
 * @param instance UART instance number (0=USART1, 1=USART2, 2=USART6)
 * @return Pointer to UART base address
 */
static volatile uint32_t* get_uart_base(uint8_t instance) {
    switch(instance) {
        case 0: return (volatile uint32_t*)USART1_BASE;
        case 1: return (volatile uint32_t*)USART2_BASE;
        case 2: return (volatile uint32_t*)USART6_BASE;
        default: return (volatile uint32_t*)USART2_BASE;
    }
}

/**
 * @brief Enable UART peripheral clock
 * @param instance UART instance number
 */
static void enable_uart_clock(uint8_t instance) {
    switch(instance) {
        case 0: RCC_APB2ENR |= (1 << 4); break;  // USART1
        case 1: RCC_APB1ENR |= (1 << 17); break; // USART2
        case 2: RCC_APB2ENR |= (1 << 5); break;  // USART6
    }
}

/**
 * @brief Get APB clock frequency for UART instance
 * @param instance UART instance number
 * @return APB clock frequency in Hz
 */
static uint32_t get_apb_clock(uint8_t instance) {
    return (instance == 1) ? g_apb1_clock : g_apb2_clock;
}

/**
 * @brief Initialize UART instance (STM32F411 implementation)
 * @param instance UART instance number
 * @param config Pointer to UART configuration
 * @return UART_OK on success, UART_ERROR on failure
 */
static uint8_t stm32_uart_init(uint8_t instance, const struct uart_config* config) {
    if (instance >= HAL_UART_MAX_INSTANCES || config == 0) {
        return UART_ERROR;
    }
    
    volatile uint32_t* base = get_uart_base(instance);
    volatile uint32_t* cr1 = (volatile uint32_t*)((uint32_t)base + USART_CR1);
    volatile uint32_t* cr2 = (volatile uint32_t*)((uint32_t)base + USART_CR2);
    volatile uint32_t* brr = (volatile uint32_t*)((uint32_t)base + USART_BRR);
    
    // Enable clock
    enable_uart_clock(instance);
    
    // Disable UART
    *cr1 &= ~CR1_UE;
    
    // Configure data bits
    if (config->data_bits == 9) {
        *cr1 |= CR1_M;
    } else {
        *cr1 &= ~CR1_M;
    }
    
    // Configure parity
    if (config->parity == 0) {
        *cr1 &= ~CR1_PCE;
    } else {
        *cr1 |= CR1_PCE;
        if (config->parity == 2) {
            *cr1 |= CR1_PS;  // Odd
        } else {
            *cr1 &= ~CR1_PS; // Even
        }
    }
    
    // Configure stop bits
    *cr2 &= ~(3 << 12);
    if (config->stop_bits == 2) {
        *cr2 |= (2 << 12);
    }
    
    // Configure baud rate
    uint32_t clock = get_apb_clock(instance);
    *brr = clock / config->baudrate;
    
    // Enable TX and RX
    *cr1 |= (CR1_TE | CR1_RE);
    
    // Enable UART
    *cr1 |= CR1_UE;
    
    return UART_OK;
}

/**
 * @brief Deinitialize UART instance (STM32F411 implementation)
 * @param instance UART instance number
 */
static void stm32_uart_deinit(uint8_t instance) {
    if (instance >= HAL_UART_MAX_INSTANCES) return;
    
    volatile uint32_t* base = get_uart_base(instance);
    volatile uint32_t* cr1 = (volatile uint32_t*)((uint32_t)base + USART_CR1);
    
    *cr1 &= ~CR1_UE;
}

/**
 * @brief Write single byte (STM32F411 implementation)
 * @param instance UART instance number
 * @param data Byte to write
 * @return UART_OK on success, UART_ERROR or UART_TIMEOUT on failure
 */
static uint8_t stm32_uart_write_byte(uint8_t instance, uint8_t data) {
    if (instance >= HAL_UART_MAX_INSTANCES) return UART_ERROR;
    
    volatile uint32_t* base = get_uart_base(instance);
    volatile uint32_t* sr = (volatile uint32_t*)((uint32_t)base + USART_SR);
    volatile uint32_t* dr = (volatile uint32_t*)((uint32_t)base + USART_DR);
    
    // Wait for TXE
    uint32_t timeout = 100000;
    while ((*sr & SR_TXE) == 0) {
        if (--timeout == 0) return UART_TIMEOUT;
    }
    
    *dr = data;
    return UART_OK;
}

/**
 * @brief Read single byte (STM32F411 implementation)
 * @param instance UART instance number
 * @param data Pointer to store received byte
 * @param timeout_ms Timeout in milliseconds
 * @return UART_OK on success, UART_ERROR or UART_TIMEOUT on failure
 */
static uint8_t stm32_uart_read_byte(uint8_t instance, uint8_t* data, uint32_t timeout_ms) {
    if (instance >= HAL_UART_MAX_INSTANCES || data == 0) return UART_ERROR;
    
    volatile uint32_t* base = get_uart_base(instance);
    volatile uint32_t* sr = (volatile uint32_t*)((uint32_t)base + USART_SR);
    volatile uint32_t* dr = (volatile uint32_t*)((uint32_t)base + USART_DR);
    
    // Wait for RXNE
    uint32_t timeout = timeout_ms * 1000;
    while ((*sr & SR_RXNE) == 0) {
        if (--timeout == 0) return UART_TIMEOUT;
    }
    
    *data = (uint8_t)(*dr & 0xFF);
    return UART_OK;
}

/**
 * @brief Write buffer (STM32F411 implementation)
 * @param instance UART instance number
 * @param data Pointer to data buffer
 * @param size Number of bytes to write
 * @return UART_OK on success, error code otherwise
 */
static uint8_t stm32_uart_write(uint8_t instance, const uint8_t* data, uint16_t size) {
    if (data == 0) return UART_ERROR;
    
    for (uint16_t i = 0; i < size; i++) {
        uint8_t status = stm32_uart_write_byte(instance, data[i]);
        if (status != UART_OK) return status;
    }
    
    // Wait for TC
    volatile uint32_t* base = get_uart_base(instance);
    volatile uint32_t* sr = (volatile uint32_t*)((uint32_t)base + USART_SR);
    uint32_t timeout = 100000;
    while ((*sr & SR_TC) == 0) {
        if (--timeout == 0) return UART_TIMEOUT;
    }
    
    return UART_OK;
}

/**
 * @brief Read buffer (STM32F411 implementation)
 * @param instance UART instance number
 * @param data Pointer to receive buffer
 * @param size Number of bytes to read
 * @param timeout_ms Timeout in milliseconds
 * @return UART_OK on success, error code otherwise
 */
static uint8_t stm32_uart_read(uint8_t instance, uint8_t* data, uint16_t size, uint32_t timeout_ms) {
    if (data == 0) return UART_ERROR;
    
    for (uint16_t i = 0; i < size; i++) {
        uint8_t status = stm32_uart_read_byte(instance, &data[i], timeout_ms);
        if (status != UART_OK) return status;
    }
    
    return UART_OK;
}

/**
 * @brief Check if data is available (STM32F411 implementation)
 * @param instance UART instance number
 * @return 1 if data available, 0 otherwise
 */
static uint8_t stm32_uart_data_available(uint8_t instance) {
    if (instance >= HAL_UART_MAX_INSTANCES) return 0;
    
    volatile uint32_t* base = get_uart_base(instance);
    volatile uint32_t* sr = (volatile uint32_t*)((uint32_t)base + USART_SR);
    
    return (*sr & SR_RXNE) ? 1 : 0;
}

/**
 * @brief Check if ready to send (STM32F411 implementation)
 * @param instance UART instance number
 * @return 1 if ready, 0 otherwise
 */
static uint8_t stm32_uart_ready_to_send(uint8_t instance) {
    if (instance >= HAL_UART_MAX_INSTANCES) return 0;
    
    volatile uint32_t* base = get_uart_base(instance);
    volatile uint32_t* sr = (volatile uint32_t*)((uint32_t)base + USART_SR);
    
    return (*sr & SR_TXE) ? 1 : 0;
}

/**
 * @brief STM32F411 UART interface implementation
 */
static const struct uart_hal_interface stm32_uart_interface = {
    .init = stm32_uart_init,
    .deinit = stm32_uart_deinit,
    .write_byte = stm32_uart_write_byte,
    .read_byte = stm32_uart_read_byte,
    .write = stm32_uart_write,
    .read = stm32_uart_read,
    .data_available = stm32_uart_data_available,
    .ready_to_send = stm32_uart_ready_to_send
};

/**
 * @brief Get STM32F411 UART interface
 * @return Pointer to STM32F411 UART interface implementation
 */
const struct uart_hal_interface* hal_uart_get_interface(void) {
    return &stm32_uart_interface;
}

/**
 * @brief Set APB clock frequencies for STM32F411
 * 
 * Platform-specific function to configure clock frequencies for accurate
 * baud rate calculation.
 * 
 * @param apb1_hz APB1 clock frequency in Hz
 * @param apb2_hz APB2 clock frequency in Hz
 */
void hal_uart_stm32_set_clock(uint32_t apb1_hz, uint32_t apb2_hz) {
    g_apb1_clock = apb1_hz;
    g_apb2_clock = apb2_hz;
}

/** @} */ // end of HAL_UART_STM32F411 group

#endif // HAL_UART_BACKEND_STM32F411
