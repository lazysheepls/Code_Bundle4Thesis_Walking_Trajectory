#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Accel
    accel = new QAccelerometer(this);               // Create a accelerometer
    accel->setAccelerationMode(QAccelerometer::Combined);    // Set acceleration mode: User
    accel->setActive(true);
    accel_reading = new QAccelerometerReading(this);        // Create a accelerometer reading
    // Gyro
    gyro = new QGyroscope(this);                    // Create a gyroscope
    gyro_reading = new QGyroscopeReading(this);         // Create a gyroscope reading
    // Compass
    compass = new QMagnetometer(this);  // Create a compass
    compass_reading = new QMagnetometerReading(this);
    // Timer
    sensorTimer = new QTimer(this);
    const int SdataRate = 50;   // unit: ms
    sensorTimer->setInterval(SdataRate);        // set timer interval
    // Timer LOG
    float curtime = 0;
    //float timeInterval = 0.01;
    // GlobalPath
    // Create Log File: Step 1: Find directry
    QString path = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).value(0);
    QDir dir(path);
    if(!dir.exists())
        dir.mkpath(path);
    if(!path.isEmpty()&&!path.endsWith("/"))
        path +="/";
    // Create Log File: Step 2: Create directry
    QString accelFileName = path + "accelLOG.txt";
    QString gyroFileName = path + "gyroLOG.txt";
    // Create Log File: Step 3: Create file
    QFile accelLOG(accelFileName);
    QFile gyroLOG(gyroFileName);
    // Create Log File: Step 4: File Acticate
    accelLOG.open(QIODevice::WriteOnly);
    accelLOG.close();
    gyroLOG.open(QIODevice::WriteOnly);
    gyroLOG.close();
    // Create Log File: Step 5: Set up textstrem
//    QTextStream accelTS(&accelLOG);
     //SIGNALS & SLOTS CONNECT
    QObject::connect(sensorTimer,SIGNAL(timeout()),this,SLOT(LogSenorData()));
    QObject::connect(sensorTimer,SIGNAL(timeout()),this,SLOT(LogFileData()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete accel;
    delete gyro;
    accelLOG->close();
}

// SLOTS FUNCTIONS
void MainWindow::on_pushButton_start_clicked()
{
    // Start all sensors
    accel->start();
    gyro->start();
    compass->start();
    qDebug()<< accel->accelerationMode()<<endl;
    // Build up all readings
    accel_reading = accel->reading();
    gyro_reading = gyro->reading();
    compass_reading = compass->reading();
    // Display status on screen
    if(accel->isActive())
    {
        ui->label_status_accel->setText("ON");
    }
    if(gyro->isActive())
    {
        ui->label_status_gyro->setText("ON");
    }
    if(compass->isActive())
    {
        ui->label_status_compass->setText("ON");
    }
    // Start Timer
    sensorTimer->start();
    // Clear Timer log
    curtime=0;

//    // Create Logging File: Step 1: Find directry
//    QString path = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).value(0);
//    QDir dir(path);
//    if(!dir.exists())
//        dir.mkpath(path);
//    if(!path.isEmpty()&&!path.endsWith("/"))
//        path +="/";
//    // Create Logging File: Step 2: Make new File
//    qDebug()<<path;
//    QFile accelLOG(path+"accelLOG.txt");
//    accelLOG.open(QIODevice::ReadWrite);
//    accelLOG.write("TEST_ACCEL");
//    accelLOG.close();
//    QFile gyroLOG(path+"gyroLOG.txt");
//    gyroLOG.open(QIODevice::ReadWrite);
//    gyroLOG.write("TEST_GYRO");
//    gyroLOG.close();
//    QString accelFileName = path + "accelLOG.txt";
//    QString gyroFileName = path + "gyroLOG.txt";
//    // Create Logging File: Step 3: Check if it is done
//    if(QFile::exists(accelFileName)&&QFile::exists(gyroFileName))
//        qDebug()<<"DONE";
//    else
//        qDebug()<<"FAIL";
    qDebug()<<qSetRealNumberPrecision(7)<<"accel_x"<<"\t"
            <<qSetRealNumberPrecision(7)<<"accel_y"<<"\t"
            <<qSetRealNumberPrecision(7)<<"accel_z"<<"\t"
            <<qSetRealNumberPrecision(7)<<"gyro_x"<<"\t"
            <<qSetRealNumberPrecision(7)<<"gyro_y"<<"\t"
            <<qSetRealNumberPrecision(7)<<"gyro_z"<<"\t"
            <<qSetRealNumberPrecision(7)<<"compass_x"<<"\t"
            <<qSetRealNumberPrecision(7)<<"compass_y"<<"\t"
            <<qSetRealNumberPrecision(7)<<"compass_z"<<"\t"
            <<qSetRealNumberPrecision(5)<<"time"<<endl;
}

void MainWindow::on_pushButton_off_clicked()
{
    // Stop all sensor
    accel->stop();
    gyro->stop();
    compass->stop();
    // Stop timer
    sensorTimer->stop();
    // Clear timer log
    curtime = 0;
    // Display Status on screen
    if(!(accel->isActive()))
    {
        ui->label_status_accel->setText("OFF");
    }
    if(!(gyro->isActive()))
    {
        ui->label_status_gyro->setText("OFF");
    }
    if(!(compass->isActive()))
    {
        ui->label_status_compass->setText("OFF");
    }
    // Clear all data
    ui->label_data_accelX->setText("N/A");
    ui->label_data_accelY->setText("N/A");
    ui->label_data_accelZ->setText("N/A");

    ui->label_data_gyroX->setText("N/A");
    ui->label_data_gyroY->setText("N/A");
    ui->label_data_gyroZ->setText("N/A");

    ui->label_data_compassX->setText("N/A");
    ui->label_data_compassY->setText("N/A");
    ui->label_data_compassZ->setText("N/A");
    qDebug() << "STOP" << endl;
}

void MainWindow::LogSenorData()
{

    float timeInterval = 0.05;
    sensorTimer->start();
    // Save real time data to variables
    accel_x = accel_reading->x();
    accel_y = accel_reading->y();
    accel_z = accel_reading->z();

    gyro_x = gyro_reading->x();
    gyro_y = gyro_reading->y();
    gyro_z = gyro_reading->z();

    compass_x = compass_reading->x();
    compass_y = compass_reading->y();
    compass_z = compass_reading->z();

    curtime = curtime + timeInterval;
    // Display real time data
    ui->label_data_accelX->setText(QString::number(accel_x));
    ui->label_data_accelY->setText(QString::number(accel_y));
    ui->label_data_accelZ->setText(QString::number(accel_z));

    ui->label_data_gyroX->setText(QString::number(gyro_x));
    ui->label_data_gyroY->setText(QString::number(gyro_y));
    ui->label_data_gyroZ->setText(QString::number(gyro_z));

    ui->label_data_compassX->setText(QString::number(compass_x));
    ui->label_data_compassY->setText(QString::number(compass_y));
    ui->label_data_compassZ->setText(QString::number(compass_z));


    qDebug()<<qSetRealNumberPrecision(7)<<accel_x<<"\t"
            <<qSetRealNumberPrecision(7)<<accel_y<<"\t"
            <<qSetRealNumberPrecision(7)<<accel_z<<"\t"
            <<qSetRealNumberPrecision(7)<<gyro_x<<"\t"
            <<qSetRealNumberPrecision(7)<<gyro_y<<"\t"
            <<qSetRealNumberPrecision(7)<<gyro_z<<"\t"
            <<qSetRealNumberPrecision(7)<<compass_x<<"\t"
            <<qSetRealNumberPrecision(7)<<compass_y<<"\t"
            <<qSetRealNumberPrecision(7)<<compass_z<<"\t"
            <<qSetRealNumberPrecision(5)<<curtime<<endl;
}

void MainWindow::LogFileData()
{
    //Log into File
//    accelLOG->open(QIODevice::WriteOnly);
//    accelTS << QString("%1").arg(accel_x)
//            << QString("%1").arg(accel_y)
//            << QString("%1").arg(accel_z)
//            << endl;
//    accelTS.flush();
//    accelLOG->close();
}
