use rusqlite::{Connection, Result, params};
use std::fs::OpenOptions;
use std::io::{BufRead, BufReader, Write};
use std::time::Duration;

fn main() {
    
    let port_name = "  "; //check when connect with port
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
    let mut line = String::new();
    

    loop{
        line.clear();
        if let Ok(bytes_read) = reader.read_line(&mut line){
            if bytes_read > 0 {
                let trimmed = line.trim();
                let parts: Vec<&str> = trimmed.split(",").collect();

                //check that get data 8 column
                if parts.len() == 3 {
                    let tempIn_parsed = parts[0].parse::<f64>();
                    let tempOut_parsed = parts[0].parse::<f64>();
                    let humdiIn_parsed = parts[0].parse::<f64>();
                    let humdiPlant1_parsed = parts[0].parse::<i32>();
                    let humdiPlant2_parsed = parts[0].parse::<i32>();
                    let humdiPlant3_parsed = parts[0].parse::<i32>();
                    let fanStatus_parsed = parts[0].parse::<i32>();
                    let pumpStatus_parsed = parts[0].parse::<i32>();

                    if let (Ok(tempIn),Ok(tempOut), Ok(humdiIn), Ok(humdiPlant1), Ok(humdiPlant2), Ok(humdiPlant3), Ok(fanStatus), Ok(pumpStatus)){
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
   

