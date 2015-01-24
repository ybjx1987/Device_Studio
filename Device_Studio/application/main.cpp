#include <QApplication>

#include "mainwindow.h"

#include <QFont>
#include <QTextCodec>
#include <QTimeEdit>
#include <QUuid>

int main(int argc,char *argv[])
{
    QApplication a(argc,argv);

    QTextCodec *gbk = QTextCodec::codecForName("GBK");
    QTextCodec::setCodecForLocale(gbk);

    QFont f=a.font();
    f.setFamily("Arial");
    f.setPointSize(9);
    a.setFont(f);

    MainWindow w;
    w.show();

    int ret=a.exec();
    return ret;
}
