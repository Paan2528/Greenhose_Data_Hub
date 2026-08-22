
🌱 Greenhouse Data Hub

Semester project for **Programming within Operating Systems** and **Microcontroller Programming** (SAE Institute Hamburg).

A smart greenhouse system that captures sensor data via Arduino, transfers it to a Raspberry Pi over USB, and logs, monitors, and visualizes it in a native desktop GUI.

## Overview

The project consists of two modules that communicate over a serial connection:

```
Arduino (sensors + actuators)
        │  USB (serial), 9600 baud
        ▼
Raspberry Pi Data Hub (Rust)
   ├─ reads & parses sensor data
   ├─ checks thresholds → notification
   ├─ writes to SQLite database
   └─ writes internal log
        │
        ▼
Greenhouse GUI (C++ / Qt)
   reads the serial connection and displays
   temperature, humidity, soil moisture,
   fan and pump status live
```

## Features

- Captures indoor/outdoor temperature, humidity, and three soil moisture sensors via Arduino
- Automatic control of fan and pump based on sensor values
- Data transfer over USB from the Arduino to the Raspberry Pi
- Persists measurement data in a SQLite database as well as an internal log
- Notifications for critical values (e.g. temperature < 18 °C or humidity > 80%)
- Live display of all readings in a Qt desktop GUI

## Project Structure

| Folder | Description |
|---|---|
| `arduino/feature/arduino_sensor` | Arduino sketch for sensor acquisition (indoor/outdoor temperature, humidity) |
| `arduino/feature/arduino_actuators` | Arduino sketch for actuator control |
| `Arduino_FAN_ON_OF` | Fan control logic |
| `Arduino_PUMP_ON_OFF` | Irrigation pump control logic |
| `greenhouse_data_hub` | Rust application for the Raspberry Pi: reads data over the USB connection, checks thresholds, writes to SQLite and the internal log |
| `raspberry_pi/greenhouse_GUI` | Qt/C++ desktop application for live visualization of sensor data |
| `database` | Database/logging components |
| `workflow.pdf` | Workflow diagram of the system |
| `Greenhouse_DataHub_Pitch.pptx.pdf` | Project pitch presentation |

## Data Format

The Arduino sends data as a comma-separated line over the USB connection:

```
tempIn,tempOut,humidIn,soil1,soil2,soil3,fanStatus,pumpStatus
```

Example:

```
21.4,15.2,55.0,42.0,39.5,44.1,1,0
```

## Tech Stack

- **Microcontroller:** Arduino (C++)
- **Data Hub (Raspberry Pi):** Rust — `serialport`, `rusqlite`, `serde`, `chrono`
- **GUI:** C++ with Qt Widgets (`QSerialPort`, Qt Creator `.ui` file)
- **Database:** SQLite

## Setup

### Arduino

1. Flash the sketch from `arduino/feature/arduino_sensor` or `Arduino_FAN_ON_OF` / `Arduino_PUMP_ON_OFF` onto the board using the Arduino IDE.
2. Baud rate: `9600`.

### Raspberry Pi Data Hub (Rust)

```bash
cd greenhouse_data_hub
cargo build --release
cargo run --release
```

The USB port (default: `/dev/ttyACM0`) and baud rate can be adjusted in `src/main.rs`.

> A systemd service for automatically starting the data hub on boot is planned but not yet finished.

### GUI (Qt)

```bash
cd raspberry_pi/greenhouse_GUI
cmake -B build
cmake --build build
```

Then run the resulting application. The serial port used by the GUI is configured in `mainwindow.cpp`.

## Team

Group project with multiple team members. The hardware setup and Arduino wiring, as well as most of the software (Rust data hub, database, Qt GUI), were implemented by [Paan2528](https://github.com/Paan2528).
