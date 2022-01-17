#include <QCoreApplication>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qWarning() << "USB to serial ports(to ESP32)";
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {
         qWarning() << info.systemLocation();
    }
    if (infos.length() > 0){
        QSerialPort serial(infos.at(0));
        serial.setBaudRate(115200);
        if(!serial.open(QIODevice::ReadWrite)){
           qErrnoWarning("Can't open serial port");
           return -1;
        }
        qWarning() << serial.portName() << "open";
    }else{
        qWarning() << "No serial port found";
    }

    return a.exec();
}
