 #include <stdint.h>

// Define the memory addresses for the Hardware Registers on your STM32L073
#define RCC_BASE      0x40021000  // Reset and Clock Control base address
#define RCC_IOPENR    (*(volatile uint32_t *)(RCC_BASE + 0x2C)) // Peripheral clock enable register

#define GPIOA_BASE    0x50000000  // GPIO Port A base address
#define GPIOA_MODER   (*(volatile uint32_t *)(GPIOA_BASE + 0x00)) // Port A Mode register (Input/Output)
#define GPIOA_ODR     (*(volatile uint32_t *)(GPIOA_BASE + 0x14)) // Port A Output Data register

// A simple manual delay function since we don't have HAL_Delay()
void manual_delay(volatile uint32_t count) {
    while (count--) {
        __asm("nop"); // Tells the CPU to do nothing for one clock cycle
    }
}

int main(void)
{
    // 1. Enable the clock for GPIO Port A (Where our LED is connected on Pin 5)
    RCC_IOPENR |= (1 << 0);

    // 2. Configure Pin PA5 as a General Purpose Output
    GPIOA_MODER &= ~(3 << (5 * 2)); // Clear bits 10 and 11
    GPIOA_MODER |=  (1 << (5 * 2)); // Set bit 10 to 1

    /* INFINITE LOOP */
    while (1)
    {
        // 3. Toggle Pin PA5 by flipping Bit 5 in the Output Data Register
        GPIOA_ODR ^= (1 << 5);

        // 4. Wait for a moment
        manual_delay(10000);
    }
}
