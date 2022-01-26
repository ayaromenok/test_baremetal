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
        serial.setBaudRate(115200); //test autosetup
        if(!serial.open(QIODevice::ReadWrite)){
           qErrnoWarning("Can't open serial port");
           return -1;
        }

        qWarning() << serial.portName() << "open";
        int numRead = 0, numReadTotal = 0;
        char buffer[140];
        for (;;) {
            numRead  = serial.read(buffer, 140);

            qWarning()<<"read:" << &buffer[0];

            numReadTotal += numRead;
            if (numRead == 0 && !serial.waitForReadyRead())
                break;
        }
        serial.close();
    }else{
        qWarning() << "No serial port found";
    }

    return a.exec();
}
