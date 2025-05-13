#ifndef FORMTEMP_H
#define FORMTEMP_H

#include <QWidget>
#include <QByteArray>
#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtCore/QCoreApplication>
#include <QDebug>
#include <QVariantList>
#include <QTimer>
#include <QDateTime>
#include <stdio.h>
#include <QStandardItemModel> 
#include <QVector>
#include "serialservice.h"
#include "temphum.h"
extern "C" {
    #include "SQLite.h"    
}

namespace Ui {
class FormTemp;
}

class FormTemp : public QWidget
{
    Q_OBJECT

public:
    explicit FormTemp(QWidget *parent = 0);
    ~FormTemp();
public slots:
    void displayTempAndHum();
    void init();


private:
    Ui::FormTemp *ui;
    SerialService *serial_server;
    QTimer *timer;
    TempHum *temphum;
    QByteArray buff;
    sqlite3 *db;
    QVector<int> temperatureData, humidityData;
    QStandardItemModel *tableModel;
 
};

#endif // FORMTEMP_H
