use serde::{Deserialize, Serialize};

/// Die 8 Datenpunkte, die Modul 2 pro Messung erfasst und speichert.
/// Passe die Felder hier an, falls dein Aufbau andere 8 Werte vorsieht -
/// der Rest des Codes (Parser, DB, Notification) bleibt dann fast gleich.
#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct SensorData {
    pub timestamp: String,       // 1. Zeitstempel der Messung
    pub temp_indoor: f32,        // 2. Temperatur innen (°C)
    pub temp_outdoor: f32,       // 3. Temperatur außen (°C)
    pub humidity: f32,           // 4. Luftfeuchtigkeit (%)
    pub fan_status: bool,        // 5. Lüfter an/aus
    pub pump_status: bool,       // 6. Wasserpumpe an/aus
    pub notify_temp_low: bool,   // 7. Notification-Flag: Temp < 18
    pub notify_humd_high: bool,  // 8. Notification-Flag: Humd. > 80
}

impl SensorData {
    /// Erzeugt SensorData aus den rohen Werten, die per UART von Modul 1
    /// kommen (Temp indoor, Temp outdoor, Humidity, Fan, Pump).
    /// Die Notification-Flags werden hier gemäß Flowchart berechnet:
    /// Temp < 18 -> Notification, Humd. > 80 -> Notification, sonst NONE.
    pub fn from_raw(
        temp_indoor: f32,
        temp_outdoor: f32,
        humidity: f32,
        fan_status: bool,
        pump_status: bool,
    ) -> Self {
        let notify_temp_low = temp_indoor < 18.0;
        let notify_humd_high = humidity > 80.0;

        SensorData {
            timestamp: chrono::Local::now().to_rfc3339(),
            temp_indoor,
            temp_outdoor,
            humidity,
            fan_status,
            pump_status,
            notify_temp_low,
            notify_humd_high,
        }
    }

    /// true, wenn KEINE der beiden Bedingungen zutrifft -> Zweig "NONE" im Flowchart
    pub fn has_no_notification(&self) -> bool {
        !self.notify_temp_low && !self.notify_humd_high
    }
}