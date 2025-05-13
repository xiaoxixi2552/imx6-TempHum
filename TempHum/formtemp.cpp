#include "formtemp.h"
#include "ui_formtemp.h"

FormTemp::FormTemp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormTemp)
{
    ui->setupUi(this);
    this->init();

}
FormTemp::~FormTemp()
{
    delete ui;
}




void FormTemp::init()
{
    ui->lcd_temp->setDigitCount(3);
    ui->lcd_temp->setStyleSheet("QLCDNumber{background: transparent;}");
    ui->lcd_hum->setDigitCount(3);
    ui->lcd_hum->setStyleSheet("QLCDNumber{background: transparent;}");
    int rc =sqliteDB_open();
	serial_server = new SerialService();
	temphum = new TempHum();
    serial_server->openCom();
    timer = new QTimer;

    tableModel = new QStandardItemModel(this);
     tableModel->setColumnCount(3);
     tableModel->setHeaderData(0, Qt::Horizontal, QStringLiteral("时间"));
     tableModel->setHeaderData(1, Qt::Horizontal, QStringLiteral("温度"));
     tableModel->setHeaderData(2, Qt::Horizontal, QStringLiteral("湿度"));
     ui->tableView->setModel(tableModel);
     ui->tableView->horizontalHeader()->setStretchLastSection(true);
     ui->tableView->verticalHeader()->setVisible(false);
     ui->tableView->setColumnWidth(0, 180);
     ui->tableView->setColumnWidth(1, 110);
     ui->tableView->setColumnWidth(2, 110);
    connect(timer, SIGNAL(timeout()), this, SLOT(displayTempAndHum()));
    timer -> start(6000);
}

void FormTemp::displayTempAndHum()
{
    serial_server->readFromSerial(buff);
    temphum ->setValue(buff);
	int temp1=temphum->getTemperature();
	int temp2=temphum->getHumidity();
    ui->lcd_temp->display(temp1);
    ui->lcd_hum->display(temp2);

    if (temperatureData.size() >= 10) {
            temperatureData.pop_front();
            humidityData.pop_front();
        }
    temperatureData.append(temphum->getTemperature());
    humidityData.append(temphum->getHumidity());

	char timeBuf[20];
    QString timeString = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    strncpy(timeBuf, timeString.toLocal8Bit().data(), sizeof(timeBuf) - 1);
    timeBuf[sizeof(timeBuf) - 1] = '\0';
    sqliteDB_opt_add(timeBuf,temp1,temp2);
    int row = tableModel->rowCount();
    tableModel->insertRow(row);
    tableModel->setData(tableModel->index(row, 0), timeBuf);
    tableModel->setData(tableModel->index(row, 1), temp1);
    tableModel->setData(tableModel->index(row, 2), temp2);

  // 选中并滚动到新插入的行（可选）
    ui->tableView->selectRow(row);
    ui->tableView->scrollTo(tableModel->index(row,0));
}


