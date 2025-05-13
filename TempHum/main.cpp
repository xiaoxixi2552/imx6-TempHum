#include <QApplication>
#include "formtemp.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FormTemp w;
    QPalette palette;
    QPixmap pixmap(":/image/background.jpg");
    palette.setBrush(QPalette::Window, QBrush(pixmap));
    w.setPalette(palette);
    w.show();
   
    return a.exec();
}
