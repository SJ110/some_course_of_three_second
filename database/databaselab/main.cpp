#include "widget.h"
#include <QApplication>
#include<QTextCodec>
#include"dbconnector.cpp"
#pragma execution_character_set("utf-8")
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if(!connectDB()){
        system("pause");
        return 0;
    }
//    QSqlQuery query;
//    query.exec("select * from ADMIN where ROOT='审核'");
//    query.next();
//        qDebug()<<query.value(0).toString()<<query.value(1).toString(); //it's ok

    Widget w;
    w.setWindowTitle("仓库管理系统");
    w.show();
    return a.exec();
}
