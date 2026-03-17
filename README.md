# UART Protocol — STM32F401xC

A bare-metal UART transmit example for the **STM32F401xC** microcontroller using the STM32 LL (Low-Layer) drivers. The firmware continuously sends `"HELLO\n"` over **USART2** at 115200 baud.

---

## Hardware

| Item | Detail |
|------|--------|
| MCU | STM32F401xC (e.g. STM32F401C-DISCO or Nucleo-F401RE) |
| UART peripheral | USART2 |
| TX pin | PA2 (AF7) |
| Baud rate | 115 200 |
| Data format | 8-bit, no parity, 1 stop bit |
| System clock | 16 MHz (HSI default) |

Connect a USB-to-serial adapter (or the board's ST-Link VCP) to **PA2** and **GND**.

---

## Project Structure

```
UART_Protocol/
├── Src/
│   ├── main.c                  # Application entry point
│   ├── startup_stm32f401xx.S  # Startup assembly file
│   ├── syscall.c               # System call stubs
│   └── sysmem.c                # Heap memory stubs
├── Inc/                        # User include directory
├── Drivers/
│   ├── CMSIS/                  # ARM CMSIS core & device headers
│   └── STM32F4xx_HAL_Driver/   # STM32F4 LL/HAL driver sources
├── cmake/
│   └── vscode_generated.cmake  # Auto-generated CMake settings
├── CMakeLists.txt              # Top-level CMake build file
├── CMakePresets.json           # CMake presets (Debug / Release)
├── stm32f401xc_flash.ld        # Linker script
└── README.md
```

---

## How It Works

`uart2_init()` configures USART2 for TX-only operation:

1. Enables the **GPIOA** peripheral clock (AHB1 bus).
2. Enables the **USART2** peripheral clock (APB1 bus).
3. Sets **PA2** to Alternate Function mode with AF7 (USART2_TX).
4. Configures USART2: 8-bit data, no parity, 1 stop bit, 115200 baud @ 16 MHz.
5. Enables USART2.

`uart2_write(char ch)` transmits a single byte by polling the TXE (Transmit Data Register Empty) flag before writing.

The `main` loop calls `uart2_write` five times to send `HELLO\n`, then executes a short busy-wait delay before repeating.

---

## Requirements

- **ARM GCC toolchain** (`arm-none-eabi-gcc`) — recommended: 10.3-2021.10 or newer
- **CMake** 3.20 or newer
- **Ninja** (or Make) build system
- **OpenOCD** or **ST-Link Utility** for flashing

---

## Build Instructions

```bash
# Configure (Debug)
cmake -B build -DCMAKE_BUILD_TYPE=Debug --preset Debug

# Build
cmake --build build

# Output files
build/UART_Protocol.elf
build/UART_Protocol.hex
build/UART_Protocol.bin
```

To build a Release (size-optimised) binary:

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release --preset Release
cmake --build build
```

---

## Flash & Debug

**Using OpenOCD:**

```bash
openocd -f interface/stlink.cfg -f target/stm32f4x.cfg \
        -c "program build/UART_Protocol.elf verify reset exit"
```

**Using STM32CubeProgrammer CLI:**

```bash
STM32_Programmer_CLI -c port=SWD -w build/UART_Protocol.hex -rst
```

---

## Serial Monitor

Open any serial terminal (e.g. PuTTY, Tera Term, `minicom`) with:

- **Port**: the COM/ttyUSB port connected to PA2
- **Baud**: 115200
- **Data**: 8N1

You should see `HELLO` printed repeatedly.

---

## License

Driver sources in `Drivers/` are provided by STMicroelectronics under their own license terms (see `Drivers/STM32F4xx_HAL_Driver/Release_Notes.html`). Application code in `Src/main.c` is released under the MIT License.
