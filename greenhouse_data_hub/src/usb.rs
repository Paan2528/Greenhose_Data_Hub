v+use std::io::{BufRead, BufReader};
use std::time::Duration;

use crate::model::SensorData;

/// Öffnet die USB-serielle Verbindung zu Modul 1.
/// Typische Pfade: "/dev/ttyACM0" (Arduino/USB-CDC) oder "/dev/ttyUSB0" (USB-Seriell-Adapter).
/// Tipp: `ls /dev/tty*` vor/nach dem Anstecken vergleichen, um den richtigen Pfad zu finden,
/// oder per udev-Regel einen festen Symlink (z.B. "/dev/modul1") anlegen, falls sich der
/// Gerätename je nach USB-Port ändert.
pub fn open_usb(port: &str, baud_rate: u32) -> serialport::Result<Box<dyn serialport::SerialPort>> {
    serialport::new(port, baud_rate)
        .timeout(Duration::from_millis(1000))
        .open()
}

/// Liest eine Zeile über die USB-serielle Verbindung.
/// Erwartetes Format pro Zeile von Modul 1, z.B. CSV:
/// temp_indoor,temp_outdoor,humidity,fan_status,pump_status
/// Beispiel: "21.4,15.2,55.0,1,0\n"
pub fn read_data_line(reader: &mut BufReader<Box<dyn serialport::SerialPort>>) -> Option<SensorData> {
    let mut line = String::new();
    match reader.read_line(&mut line) {
        Ok(0) => None, // keine Daten
        Ok(_) => parse_line(line.trim()),
        Err(_) => None, // Timeout oder Übertragungsfehler
    }
}

fn parse_line(line: &str) -> Option<SensorData> {
    let parts: Vec<&str> = line.split(',').collect();
    if parts.len() != 5 {
        eprintln!("Ungültiges UART-Datenformat: {line}");
        return None;
    }

    let temp_indoor = parts[0].parse().ok()?;
    let temp_outdoor = parts[1].parse().ok()?;
    let humidity = parts[2].parse().ok()?;
    let fan_status = parts[3].trim() == "1";
    let pump_status = parts[4].trim() == "1";

    Some(SensorData::from_raw(
        temp_indoor,
        temp_outdoor,
        humidity,
        fan_status,
        pump_status,
    ))
}