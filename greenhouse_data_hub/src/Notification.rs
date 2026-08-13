use crate::model::SensorData;

/// Bildet den Notification-Zweig aus dem Flowchart nach:
/// - Temp < 18       -> Notification
/// - Humd. > 80      -> Notification
/// - sonst           -> NONE (keine Notification)
pub fn check_and_notify(data: &SensorData) {
    if data.notify_temp_low {
        send_notification(&format!(
            "⚠️ Temperatur zu niedrig: {:.1}°C (< 18°C)",
            data.temp_indoor
        ));
    }

    if data.notify_humd_high {
        send_notification(&format!(
            "⚠️ Luftfeuchtigkeit zu hoch: {:.1}% (> 80%)",
            data.humidity
        ));
    }

    if data.has_no_notification() {
        // Entspricht dem "NONE"-Zweig im Diagramm - bewusst kein Alarm.
        println!("Status ok, keine Notification nötig.");
    }
}

/// Platzhalter für den tatsächlichen Versand (z.B. Push, E-Mail, MQTT-Topic).
/// Hier einfach ersetzen durch die gewünschte Benachrichtigungsart.
fn send_notification(message: &str) {
    println!("[NOTIFICATION] {message}");
}