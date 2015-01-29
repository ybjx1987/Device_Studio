#include <QApplication>

#include "mainwindow.h"
#include "../libs/platform/propertylist/qpropertylistview.h"

#include <QFont>
#include <QTextCodec>
#include <QTimeEdit>
#include <QUuid>

/**
 * @brief 程序入口函数
 * @param argc--输入产生的个数
 * @param argv--输入产生的数组
 * @return 程序结果
 */
int main(int argc,char *argv[])
{
    //新建的一个application
    QApplication a(argc,argv);
    //设置程序编码
    QTextCodec *gbk = QTextCodec::codecForName("GBK");
    QTextCodec::setCodecForLocale(gbk);
    //设置程序默认字体
    QFont f=a.font();
    f.setFamily("Arial");
    f.setPointSize(9);
    a.setFont(f);
    //新建主窗口
    //MainWindow w;
    //w.show();
    QPropertyListView view;
    view.show();
    //进入主循环
    int ret=a.exec();
    return ret;
}
