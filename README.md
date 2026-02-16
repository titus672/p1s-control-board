# p1s-control-board

A Raspberry Pi Pico-based controller for the Mictuning P1S. This project utilizes the Pico's PIO (Programmable I/O) to interface with external switch panels and logic hardware.

## Project Structure

The repository is organized as follows:

* **`src/`**: Contains the primary firmware source code.
    * `switch_panel.c` / `switch_panel.h`: Main application logic.
    * `switch_panel.pio`: Custom PIO state machine code.
    * `pico-sdk/`: The Raspberry Pi Pico SDK (git submodule).
* **`pulseview_captures/`**: Logic analyzer traces documenting board states:
    * Includes captures for Horn Blast, Jeep windshield lights, and Top 3 enable/disable sequences.

## Getting Started

### 1. Clone the Repository
To ensure the `pico-sdk` submodule is populated, clone using the `--recursive` flag:

git clone --recursive https://github.com/titus672/p1s-control-board.git

### 2. Build the Firmware
Ensure you have the ARM GCC toolchain and CMake installed.

cd src
mkdir build
cd build
cmake .. -DPICO_BOARD=pico2_w -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
make

### 3. Flash to Pico
1. Hold the **BOOTSEL** button on your Pico and plug it into your USB port.
2. Drag and drop the `p1s_switch_panel.uf2` file from `src/build/` onto the RPI-RP2 drive.

## Development Notes
* **PIO Interfacing**: The `switch_panel.pio` file is compiled into `switch_panel.pio.h` during the build process.
* **Logic Analysis**: Refer to the existing captures in `pulseview_captures/` using [Sigrok PulseView](https://sigrok.org/wiki/PulseView) for timing references.
