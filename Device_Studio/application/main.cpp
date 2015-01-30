#include <QApplication>

#include "mainwindow.h"
#include "../libs/platform/propertylist/qpropertylistview.h"
#include "../libs/kernel/property/qfloatproperty.h"

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
    f.setPointSize(12);
    a.setFont(f);
    //新建主窗口
    //MainWindow w;
    //w.show();
    QPropertyListView view;

    QList<QAbstractProperty*>       list;

    QAbstractProperty *pro;

    for(int i= 0;i<10;i++)
    {
        pro = new QFloatProperty();
        pro->setName("abcd");
        pro->setShowName("Name");
        pro->setDefaultValue(i/2.0);
        pro->reset();
        list.append(pro);
    }


    view.setPropertys(list);

    view.show();
    //进入主循环
    int ret=a.exec();
    return ret;
}
