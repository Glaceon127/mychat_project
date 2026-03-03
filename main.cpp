#include "mainwindow.h"
#include <QFile>
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile qss(":/style/stylesheet.qss");
    if(qss.open(QFile::ReadOnly)){
        qDebug("open success");
        QString style = QString::fromUtf8(qss.readAll());
        qDebug() << style;
        a.setStyleSheet(style);
        qss.close();
    }else{
        qDebug("open failed");
    }
    MainWindow w;
    w.show();
    return a.exec();
}
