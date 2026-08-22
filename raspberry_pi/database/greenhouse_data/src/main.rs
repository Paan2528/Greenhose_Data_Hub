use rusqlite::{Connection, Result, params};
use std::fs::OpenOptions;
use std::io::{BufRead, BufReader, Write};
use std::time::Duration;

fn main() {
    
    let port_name = "/dev/ttyACM0"; //check when connect with port
    let baud_rate = 9600;
    let csv_file_path = "greenhouse_dataHub";

    //Creat CSV. file for data recode
    let mut file = OpenOptions::new()
        .creat(true)
        .append(true)
        .open(csv_file_path)
        .expect("Can't creat or open file!")

    // Heat of CSV file or name of column
    if file.metadata().map(|m| m.len() ==0).unwrap_or(false){
        writeln!(file, "creat_at, tempIn, tempOut, humdiIn, humdiPlant1, humdiPlant2,humdiPlant3, fanStatus, pumpStatus")
        .expect("weite not susses!")
    }

    //Connect with UART
    let port = serialport::new(port_name, baud_rate)
        .timeout(Duration::from_secs(3))
        .open()
        .expect("Can't open Serial port");
    
        // waiting for get the data

    let mut reader = BufReader::new(port);
    
    

    loop{

        let mut line = String::new();
        line.clear();
        if let Ok(bytes_read) = reader.read_line(&mut line){
            if bytes_read > 0 {
                let trimmed = line.trim();
                let parts: Vec<&str> = trimmed.split(",").collect();

                //check that get data 8 column
                if parts.len() == 8 {
                    let tempIn_parsed = parts[0].parse::<f64>();
                    let tempOut_parsed = parts[1].parse::<f64>();
                    let humdiIn_parsed = parts[2].parse::<f64>();
                    let humdiPlant1_parsed = parts[3].parse::<i64>();
                    let humdiPlant2_parsed = parts[4].parse::<i64>();
                    let humdiPlant3_parsed = parts[5].parse::<i64>();
                    let fanStatus_parsed = parts[6].parse::<i32>();
                    let pumpStatus_parsed = parts[7].parse::<i32>();

                    if let (Ok(tempIn),Ok(tempOut), Ok(humdiIn), Ok(humdiPlant1), Ok(humdiPlant2), Ok(humdiPlant3), Ok(fanStatus), Ok(pumpStatus))=
                    (
                        tempIn_parsed,
                        tempOut_parsed
                        humdiIn_parsed,
                        humdiPlant1_parsed,
                        humdiPlant2_parsed,
                        humdiPlant3_parsed,
                        fanStatus,
                        pumpStatus_parsed
                    ){
                        // Timestamp ISO 8601
                        let timestamp = Local::now().format("%Y-%m-%d %H:%M:%S").to_string();
                        // Creat new CSV
                        let csv_row = format!("{},{},{},{},{},{},{},{},{} \n", timestamp,tempIn, tempOut, humdiIn, humdiPlant1, humdiPlant2, humdiPlant3, fanStatus, pumpStatus)
                        //save to file
                        if let Err(e) = file.write_all(csv_row.as_bytes()){
                            eprintln!("Something wrong with save file!")
                        } else {
                            print!(" [Saved] -> {}", csv_row);
                        }
                    } else {
                        eprintln("data is't correct!");
                    }              
                                    
                }                   
            }
        }    
    } 
};
   

