#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDialog>
#include<QMessageBox>
#include"dbconnector.h"
#include"showdata.h"
#pragma execution_character_set("utf-8")
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    showdata *showData;
public slots:
     void reshow();
     void log();
     void exit();
signals:
     void sendsignal(); //to reshow this

};

#endif // WIDGET_H
