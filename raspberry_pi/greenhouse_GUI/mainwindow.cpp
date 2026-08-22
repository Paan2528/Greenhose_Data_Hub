#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QSerialPort>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){

    ui->setupUi(this);
    setupSerial();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//connect port
void MainWindow::setupSerial(){
    serial = new QSerialPort(this);
    serial -> setPortName("/tmp/ttyV0");
    serial -> setBaudRate(QSerialPort::Baud9600);

    if(!serial -> open(QIODevice::ReadOnly)){
        qWarning() << "can't open port: " << serial -> errorString();
        return;
    }
    connect(serial, &QSerialPort::readyRead, this , &MainWindow::readSerialData);

}
void MainWindow::readSerialData(){
    buffer.append(serial->readAll());

    while (buffer.contains('\n')){
        int idx = buffer.indexOf('\n');
        QByteArray lineBytes = buffer.left(idx).trimmed();
        buffer.remove(0, idx + 1);
        if(!lineBytes.isEmpty()){
            parseLine(QString::fromUtf8(lineBytes));
        }
    }
}
void MainWindow::parseLine(const QString &line){
    QStringList parts = line.split(',');
    if(parts.size() != 8){
        qWarning() << "can't get all data" << line;
        return;
    }


    double tempIn = parts[0].toDouble();
    double tempOut = parts[1].toDouble();
    double humdIn = parts[2].toDouble();
    double soil1 = parts[3].toDouble();
    double soil2 = parts[4].toDouble();
    double soil3 = parts[5].toDouble();
    int fanStatus = parts[6].toInt();
    int pumpStatus = parts[7].toInt();



    ui -> tempIn -> display(tempIn);
    ui -> tempOut -> display(tempOut);
    ui -> humidIn -> display(humdIn);
    ui -> soil1 -> display(soil1);
    ui -> soil2 -> display(soil2);
    ui -> soil3 -> display(soil3);
    ui -> fanStatus -> display(fanStatus);
    ui -> pumpStatus -> display(pumpStatus);




}


