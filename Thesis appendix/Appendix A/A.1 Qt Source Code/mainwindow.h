#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QTimer>
#include <QDebug>
#include <QDir>

#include <QFile>
#include <QFileInfo>

#include <QTextStream>

#include <QStandardPaths>

#include <QAccelerometer>
#include <QAccelerometerReading>
#include <QAccelerometerFilter>

#include <QGyroscope>
#include <QGyroscopeReading>
#include <QGyroscopeFilter>

#include <QMagnetometer>
#include <QMagnetometerReading>
#include <QMagnetometerFilter>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QFile *accelLOG;
    QFile *gyroLOG;
    QTextStream accelTS;
    qreal accel_x;
    qreal accel_y;
    qreal accel_z;
    qreal gyro_x;
    qreal gyro_y;
    qreal gyro_z;
    qreal compass_x;
    qreal compass_y;
    qreal compass_z;
    float curtime;
    float timeInterval;

signals:


private slots:
    void on_pushButton_start_clicked();

    void on_pushButton_off_clicked();

    void LogSenorData();

    void LogFileData();

private:
    Ui::MainWindow *ui;
    // Accel Var
    QAccelerometer *accel;
    QAccelerometerReading *accel_reading;
    // Gyro Var
    QGyroscope *gyro;
    QGyroscopeReading *gyro_reading;
    // Compass Var
    QMagnetometer *compass;
    QMagnetometerReading *compass_reading;
    // Timer
    QTimer *sensorTimer;
    // Logging Files
    QString *accelFileName;
    QString *gyroFileName;
};

#endif // MAINWINDOW_H
