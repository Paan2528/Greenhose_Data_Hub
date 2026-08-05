 use rusqlite::{Connection, Result, params};

struct  readsensors {
    getTime: f32,
    getTempInside: f32,
    getTempOutside: f32,
    getHumidity: f32,
    getSoilHumidPin1: f32,
    getSoilHumidPin2: f32,
    getSoilHumidPin3: f32
 }
 struct actuatorStatus{
    FanStatus: bool,
    PumpStatus: bool 

 }

 fn create_database() -> Result<()> {
    let sensors = readsensors{
        getTime: 10.0,
        getTempInside: 23.5,
        getTempOutside: 12.4,
        getHumidity: 23.0,
        getSoilHumidPin1: 24.9,
        getSoilHumidPin2: 68.0,
        getSoilHumidPin3: 72.7
    };
    let actuators = actuatorStatus{
        FanStatus: true,
        PumpStatus: false
    };
    // creat the file
    let conn = Connection::open("greenhouse_data.db")?;
    //Creat a table named greenhouse data
    conn.execute(
        "CREATE TABLE IF NOT EXISTS greenhouse_data (
        date_time TIMESTAMP,
        Temp_inside FLOAT NOT NULL,
        Temp_outside FLOAT NOT NULL,
        Humdi_inside FLOAT NOT NULL,
        Soil_Humdi1 FLOAT NOT NULL,
        Soil_Humdi2 FLOAT NOT NULL, 
        Soil_Humdi3 FLOAT NOT NULL,
        Fan_status INTEGER NOT NULL,
        Pump_status INTEGER NOT NULL)",[]) ?;

    
    conn.execute(
        "INSERT INTO greenhouse_data(
        date_time,
        Temp_inside,
        Temp_outside,
        Humdi_inside,
        Soil_Humdi1,
        Soil_Humdi2,
        Soil_Humdi3,
        Fan_status,
        Pump_status
        )VALUES(?1,?2,?3,?4,?5,?6,?7,?8,?9)",
        params![
        sensors.getTime,
        sensors.getTempInside,
        sensors.getTempOutside,
        sensors.getHumidity,
        sensors.getSoilHumidPin1,
        sensors.getSoilHumidPin2,
        sensors.getSoilHumidPin3,
        actuators.FanStatus,
        actuators.PumpStatus
        ])?;
    
    return Ok(());

 }
 fn main(){
    create_database().unwrap();
 }