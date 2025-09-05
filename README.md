# Arduino Traffic Light Simulation

A simple Arduino project that simulates two traffic lights at an intersection using an Arduino Uno board and six LEDs (red, yellow, green for each light). The traffic lights alternate between directions with predefined durations using a state machine implementation.

## Features

- **State Machine Design**: Clean implementation using enum states for better code organization
- **Non-blocking Timing**: Uses `millis()` for timing without blocking the processor
- **Configurable Durations**: Easy to modify timing for each light state
- **Standard Traffic Light Sequence**: Red (30s) → Green (30s) → Yellow (5s) → Red...

## Hardware Requirements

- Arduino Uno board
- 6 LEDs (2 Red, 2 Yellow, 2 Green)
- 6 x 220Ω resistors (for LED current limiting)
- Breadboard and jumper wires
- USB cable for programming

## Circuit Connections

Connect the LEDs to the following pins:

**Traffic Light 1:**
- **Red LED**: Pin 13 (with 220Ω resistor to ground)
- **Yellow LED**: Pin 12 (with 220Ω resistor to ground)
- **Green LED**: Pin 11 (with 220Ω resistor to ground)

**Traffic Light 2:**
- **Red LED**: Pin 10 (with 220Ω resistor to ground)
- **Yellow LED**: Pin 9 (with 220Ω resistor to ground)
- **Green LED**: Pin 8 (with 220Ω resistor to ground)

**Note**: The Arduino Uno has a built-in LED on pin 13, so you can use that for the red light of traffic light 1 if desired.

## Software Requirements

- [PlatformIO](https://platformio.org/) (recommended) or Arduino IDE
- Arduino framework

## Installation

1. Clone or download this repository
2. Open the project in PlatformIO (or Arduino IDE)
3. Connect your Arduino Uno to your computer
4. Upload the code to the board

### Using PlatformIO

```bash
# Install PlatformIO if not already installed
# Then navigate to the project directory
cd arduino-trafficlight

# Build and upload
pio run -t upload
```

### Using Arduino IDE

1. Open `src/main.cpp` in Arduino IDE
2. Select "Arduino Uno" from Tools > Board
3. Select the correct COM port
4. Click Upload

## Usage

Once uploaded, the traffic lights will start automatically and cycle through 5 states:

1. **Traffic Light 1 Red, Traffic Light 2 Green** (30s)
2. **Traffic Light 1 Red, Traffic Light 2 Yellow** (5s)
3. **All Red** (2s) - Safety transition period
4. **Traffic Light 1 Green, Traffic Light 2 Red** (30s)
5. **Traffic Light 1 Yellow, Traffic Light 2 Red** (5s)
6. Repeats the cycle

The lights are synchronized to prevent conflicts and include a brief all-red period for safety during transitions. The timing is handled by the Arduino's internal timer and doesn't require any user interaction.

## Code Structure

- `src/main.cpp`: Main program with 5-state state machine logic for two synchronized traffic lights
- `simulation.cpp`: Console-based simulation of the traffic light sequence (for testing without hardware)
- `platformio.ini`: PlatformIO configuration file

## Simulation

A console-based simulation is included (`simulation.cpp`) that demonstrates the traffic light sequence without requiring Arduino hardware. The simulation uses shortened timing for faster demonstration:

- Green/Yellow periods: 3/0.5 seconds (vs 30/5 seconds on Arduino)
- All Red period: 0.2 seconds (vs 2 seconds on Arduino)

To run the simulation:
```bash
g++ simulation.cpp -o simulation -std=c++11
./simulation
```

## Customization

You can modify the timing constants in `src/main.cpp`:

```cpp
const unsigned long redDuration = 30000;    // 30 seconds
const unsigned long greenDuration = 30000;  // 30 seconds
const unsigned long yellowDuration = 5000;  // 5 seconds
```

## Troubleshooting

- **LEDs not lighting up**: Check your circuit connections and resistor values
- **Wrong timing**: Verify the duration constants in the code
- **Upload fails**: Ensure the correct board and port are selected

## License

This project is open source and available under the [MIT License](LICENSE).

## Contributing

Feel free to submit issues and enhancement requests!