#ifndef CAIGOULOG_H
#define CAIGOULOG_H

#include <QWidget>
#include<QMessageBox>
#include"dbconnector.h"
#include"form.h"
namespace Ui {
class caigoulog;
}

class caigoulog : public QWidget
{
    Q_OBJECT

public:
    explicit caigoulog(QWidget *parent = 0);
    ~caigoulog();
private:
    Ui::caigoulog *ui;
    Form *showCaigou;

private slots:
    void log();
    void backup();
    void reshow();
signals:
    void sendsignal2();  //to show showdata
    void sendsignal3();

};

#endif // CAIGOULOG_H
