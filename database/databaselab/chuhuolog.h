#ifndef CHUHUOLOG_H
#define CHUHUOLOG_H

#include <QWidget>
#include<QMessageBox>
#include"dbconnector.h"
#include"sell.h"
namespace Ui {
class chuhuolog;
}

class chuhuolog : public QWidget
{
    Q_OBJECT

public:
    explicit chuhuolog(QWidget *parent = 0);
    ~chuhuolog();


private:
    Ui::chuhuolog *ui;
    sell* seLL;

signals:
    void sendsignal4();
    void sendsignal5();
private slots:
    void on_retButton_clicked();
    void on_logButton_clicked();
    void reshow();
};

#endif // CHUHUOLOG_H
