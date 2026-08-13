mod model;
mod notification;
mod storage;
mod usb;
mod Model;
mod Notification;
mod Storage;

use std::io::BufReader;

use storage::Database;

const USB_PORT: &str = "/dev/ttyACM0";
const BAUD_RATE: u32 = 9600;
const DB_PATH: &str = "sensor_data.db";
const INTERNAL_STORAGE_PATH: &str = "internal_storage.log";

fn main() {
    println!("Modul 2 (Raspberry Pi Data Hub) gestartet...");

    let port = match usb::open_usb(USB_PORT, BAUD_RATE) {
        Ok(p) => p,
        Err(e) => {
            eprintln!("Konnte USB-Port {USB_PORT} nicht öffnen: {e}");
            return;
        }
    };
    let mut reader = BufReader::new(port);

    let db = match Database::new(DB_PATH) {
        Ok(db) => db,
        Err(e) => {
            eprintln!("Datenbank konnte nicht initialisiert werden: {e}");
            return;
        }
    };

    // Hauptschleife: entspricht dem fortlaufenden Durchlauf
    // Raspberry Pi data hub -> Data -> Notification -> Database -> Internal storage
    loop {
        let Some(data) = usb::read_data_line(&mut reader) else {
            continue; // keine/ungültige Daten, nächste Runde
        };

        // Zweig: Temp < 18 / Humd. > 80 -> Notification, sonst NONE
        notification::check_and_notify(&data);

        // Database
        if let Err(e) = db.insert(&data) {
            eprintln!("Fehler beim Schreiben in die Datenbank: {e}");
        }

        // Internal storage
        if let Err(e) = storage::write_internal_storage(INTERNAL_STORAGE_PATH, &data) {
            eprintln!("Fehler beim Schreiben in den internen Speicher: {e}");
        }
    }
}