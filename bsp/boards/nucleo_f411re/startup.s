/**
 * @file startup.s
 * @brief startup for STM32F411RE
 */

    .syntax unified
    .cpu cortex-m4
    .thumb

.global Reset_Handler

/* Vector table */
    .section .isr_vector,"a",%progbits
    .word _estack
    .word Reset_Handler
    .word 0
    .word 0

/* Reset handler */
    .section .text.Reset_Handler
    .type Reset_Handler, %function
Reset_Handler:
    /* Copy .data from flash to RAM */
    ldr r0, =_sdata
    ldr r1, =_edata
    ldr r2, =_sidata
1:  cmp r0, r1
    beq 2f
    ldr r3, [r2], #4
    str r3, [r0], #4
    b 1b

    /* Zero .bss */
2:  ldr r0, =_sbss
    ldr r1, =_ebss
    movs r2, #0
3:  cmp r0, r1
    beq 4f
    str r2, [r0], #4
    b 3b
    bl SystemInit
    /* Call main */
4:  bl main

    /* Loop forever */
5:  b 5b

.size Reset_Handler, .-Reset_Handler
