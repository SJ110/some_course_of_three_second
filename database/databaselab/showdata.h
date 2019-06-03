#ifndef SHOWDATA_H
#define SHOWDATA_H

#include <QWidget>
#include"dbconnector.h"
#include"caigoulog.h"
#include"form.h"
#include"chuhuolog.h"
namespace Ui {
class showdata;
}

class showdata : public QWidget
{
    Q_OBJECT

public:
    explicit showdata(QWidget *parent = 0);
    ~showdata();

private:
    Ui::showdata *ui;
    caigoulog *caigou;
    chuhuolog* chuhuoLog;
    //showcaigou *showCaigou;
public:
    void init();

private slots:
    void jinhuo();
    void chuhuo();
    void backup();
    void sort();
    void find();
    void exit();
    void reshow();
signals:
    void sendsignal(); //to show widget
    void sendsignal2(); //to reshow this
    void sendsignal3();// to reshow this
    void sendsignal4();// to reshow this
};

#endif // SHOWDATA_H
