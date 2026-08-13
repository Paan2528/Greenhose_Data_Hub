use rusqlite::{params, Connection, Result};
use std::fs::OpenOptions;
use std::io::Write;

use crate::model::SensorData;

/// "Database" im Flowchart: SQLite-Datenbank mit allen 8 erfassten Werten.
pub struct Database {
    conn: Connection,
}

impl Database {
    pub fn new(path: &str) -> Result<Self> {
        let conn = Connection::open(path)?;
        conn.execute(
            "CREATE TABLE IF NOT EXISTS sensor_data (
                id              INTEGER PRIMARY KEY AUTOINCREMENT,
                timestamp       TEXT NOT NULL,
                temp_indoor     REAL NOT NULL,
                temp_outdoor    REAL NOT NULL,
                humidity        REAL NOT NULL,
                fan_status      INTEGER NOT NULL,
                pump_status     INTEGER NOT NULL,
                notify_temp_low INTEGER NOT NULL,
                notify_humd_high INTEGER NOT NULL
            )",
            [],
        )?;
        Ok(Database { conn })
    }

    pub fn insert(&self, data: &SensorData) -> Result<()> {
        self.conn.execute(
            "INSERT INTO sensor_data
                (timestamp, temp_indoor, temp_outdoor, humidity,
                 fan_status, pump_status, notify_temp_low, notify_humd_high)
             VALUES (?1, ?2, ?3, ?4, ?5, ?6, ?7, ?8)",
            params![
                data.timestamp,
                data.temp_indoor,
                data.temp_outdoor,
                data.humidity,
                data.fan_status as i32,
                data.pump_status as i32,
                data.notify_temp_low as i32,
                data.notify_humd_high as i32,
            ],
        )?;
        Ok(())
    }
}

/// "Internal storage" im Flowchart: zusätzliches lokales Backup als Log-Datei,
/// falls die Datenbank z.B. nicht erreichbar ist oder zusätzlich benötigt wird.
pub fn write_internal_storage(path: &str, data: &SensorData) -> std::io::Result<()> {
    let json_line = serde_json::to_string(data).unwrap_or_default();

    let mut file = OpenOptions::new()
        .create(true)
        .append(true)
        .open(path)?;

    writeln!(file, "{json_line}")?;
    Ok(())
}