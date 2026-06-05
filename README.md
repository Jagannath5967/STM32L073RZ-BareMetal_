# STM32L073RZ Bare-Metal Blinking LED

A lightweight, bare-metal C project targeting the **NUCLEO-L073RZ** development board (featuring the STM32L073VTI6 ultra-low-power ARM Cortex-M0+ MCU). 

This project completely bypasses the standard STM32CubeMX visual initialization tool (`.ioc` configuration) and the Hardware Abstraction Layer (HAL) library. Instead, it implements a standard blinking LED routine using **direct register manipulation** via standard memory mapping and manual bitwise operations.

---

## Technical Overview & Architecture

### 1. Clock Management (RCC)
Before interfacing with any peripheral on an ARM Cortex-M architecture, the peripheral's clock domain must be energized to reduce dynamic power consumption. 
* **Target Register:** Reset and Clock Control Peripheral Clock Enable Register (`RCC_IOPENR` at address `0x4002102C`).
* **Operation:** Set Bit 0 to high (`1 << 0`) to enable the clock gate for **GPIO Port A**.

### 2. GPIO Configuration
The physical green user LED (**LD2**) on the NUCLEO-L073RZ is permanently wired to pin **PA5**.
* **Target Register:** GPIO Port A Mode Register (`GPIOA_MODER` at address `0x50000000`).
* **Operation:** Configures Pin 5 into *General Purpose Output Mode* by setting bits [11:10] to `01`.

### 3. State Toggling & Timing Loop
* **Target Register:** GPIO Port A Output Data Register (`GPIOA_ODR` at address `0x50000014`).
* **Operation:** Leverages a Bitwise XOR operation (`^=`) targeting Bit 5 to cleanly flip the state between high (3.3V) and low (0V) inside an infinite execution loop (`while(1)`).
* **Timing:** Utilizes a lightweight assembly `nop` loop block to create a deterministic software delay without relying on hardware timers or interrupt handlers.

---

## Repository Structure

```text
.
├── Core
│   └── Src
│       └── main.c
├── .gitignore
└── README.md
Toolchain & Development Environment
IDE: STM32CubeIDE v2.1.1 (Linux Environment)

Compiler: GNU Tools for ARM Embedded Processors (arm-none-eabi-gcc)

Debugger: ST-LINK/V2-1 onboard programmer via GDB Server over SWD (Serial Wire Debug)

Hardware: NUCLEO-L073RZ Development Board
EOF
