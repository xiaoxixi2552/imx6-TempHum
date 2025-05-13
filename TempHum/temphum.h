#ifndef TEMPHUM_H
#define TEMPHUM_H

#include <QObject>

class TempHum :public QObject
{
    Q_OBJECT
public:
    explicit TempHum();
    void setValue(QByteArray&);
    int getTemperature();
    int getHumidity();

private :
    int temperature;
    int humidity;
    float light;
};

#endif // TEMPHUM_H
