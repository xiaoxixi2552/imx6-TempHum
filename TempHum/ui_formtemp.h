/********************************************************************************
** Form generated from reading UI file 'formtemp.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMTEMP_H
#define UI_FORMTEMP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormTemp
{
public:
    QLCDNumber *lcd_temp;
    QLCDNumber *lcd_hum;
    QLabel *C;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_5;
    QLabel *label_6;
    QTableView *tableView;

    void setupUi(QWidget *FormTemp)
    {
        if (FormTemp->objectName().isEmpty())
            FormTemp->setObjectName(QStringLiteral("FormTemp"));
        FormTemp->resize(800, 480);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(FormTemp->sizePolicy().hasHeightForWidth());
        FormTemp->setSizePolicy(sizePolicy);
        FormTemp->setAutoFillBackground(true);
        FormTemp->setStyleSheet(QStringLiteral(""));
        lcd_temp = new QLCDNumber(FormTemp);
        lcd_temp->setObjectName(QStringLiteral("lcd_temp"));
        lcd_temp->setEnabled(true);
        lcd_temp->setGeometry(QRect(610, 160, 71, 31));
        QFont font;
        font.setPointSize(9);
        font.setBold(true);
        font.setWeight(75);
        lcd_temp->setFont(font);
        lcd_temp->setFocusPolicy(Qt::NoFocus);
        lcd_temp->setContextMenuPolicy(Qt::DefaultContextMenu);
        lcd_temp->setStyleSheet(QStringLiteral("background-color:transparent;"));
        lcd_temp->setFrameShape(QFrame::NoFrame);
        lcd_temp->setMode(QLCDNumber::Dec);
        lcd_temp->setSegmentStyle(QLCDNumber::Flat);
        lcd_hum = new QLCDNumber(FormTemp);
        lcd_hum->setObjectName(QStringLiteral("lcd_hum"));
        lcd_hum->setEnabled(true);
        lcd_hum->setGeometry(QRect(610, 240, 71, 31));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lcd_hum->sizePolicy().hasHeightForWidth());
        lcd_hum->setSizePolicy(sizePolicy1);
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        lcd_hum->setFont(font1);
        lcd_hum->setContextMenuPolicy(Qt::DefaultContextMenu);
        lcd_hum->setAutoFillBackground(false);
        lcd_hum->setStyleSheet(QStringLiteral("background-color: transparent;"));
        lcd_hum->setFrameShape(QFrame::NoFrame);
        lcd_hum->setFrameShadow(QFrame::Raised);
        lcd_hum->setSegmentStyle(QLCDNumber::Flat);
        C = new QLabel(FormTemp);
        C->setObjectName(QStringLiteral("C"));
        C->setGeometry(QRect(690, 160, 61, 31));
        QFont font2;
        font2.setPointSize(25);
        C->setFont(font2);
        label = new QLabel(FormTemp);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(700, 230, 51, 41));
        label->setFont(font2);
        label_2 = new QLabel(FormTemp);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(130, 40, 501, 61));
        label_2->setFont(font2);
        label_5 = new QLabel(FormTemp);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(560, 160, 61, 31));
        QFont font3;
        font3.setPointSize(20);
        label_5->setFont(font3);
        label_6 = new QLabel(FormTemp);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(560, 240, 61, 31));
        label_6->setFont(font3);
        tableView = new QTableView(FormTemp);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(40, 130, 400, 250));

        retranslateUi(FormTemp);

        QMetaObject::connectSlotsByName(FormTemp);
    } // setupUi

    void retranslateUi(QWidget *FormTemp)
    {
        FormTemp->setWindowTitle(QApplication::translate("FormTemp", "TempHum", 0));
        C->setText(QApplication::translate("FormTemp", "\302\260C", 0));
        label->setText(QApplication::translate("FormTemp", "%", 0));
        label_2->setText(QApplication::translate("FormTemp", "\345\237\272\344\272\216imx6\347\232\204\346\270\251\346\271\277\345\272\246\345\256\236\346\227\266\347\233\221\346\216\247\347\263\273\347\273\237", 0));
        label_5->setText(QApplication::translate("FormTemp", "\346\270\251\345\272\246", 0));
        label_6->setText(QApplication::translate("FormTemp", "\346\271\277\345\272\246", 0));
    } // retranslateUi

};

namespace Ui {
    class FormTemp: public Ui_FormTemp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMTEMP_H
