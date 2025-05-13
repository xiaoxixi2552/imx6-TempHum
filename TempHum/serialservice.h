#ifndef SERIALSERVICE_H
#define SERIALSERVICE_H

#include <QObject>
#include <QByteArray>
#include <QString>
#include <QTimer>
#include <unistd.h>

//#include "posix_qextserialport.h"
#define READTIME 1000

class SerialService : public QObject
{
    Q_OBJECT
public:
    explicit SerialService(QObject *parent = 0);

    qint64 readFromSerial(QByteArray &byte);
    int writeToSerial(const QByteArray &byte);
    bool openCom();
    bool closeCom();
    void releaseSerial();
    QTimer* getTimer();
signals:

public slots:

private:
    //Posix_QextSerialPort *my_com;
    static int fd;
    enum{OPEN, CLOSE};
    int com_state;
    QTimer *read_timer;
};

#endif // SERIALSERVICE_H
