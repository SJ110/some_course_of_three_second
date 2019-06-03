#ifndef FORM_H
#define FORM_H
/*
 * 参考自https://blog.csdn.net/qiufenpeng/article/details/81259344
 *  */

#include <QWidget>
#include<QDateTime>
#include<QMessageBox>
#include"dbconnector.h"
#include"showdingd.h"
#include"mycombobox.h"
#pragma execution_character_set("utf-8")
namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();

private slots:
    void on_retButton_clicked();

    void on_sureButton_clicked();

private:
    Ui::Form *ui;
    showDingD* dingd;
    dbConnect db;
    QString str0;
    QString str1;
private slots:
    void boxid();
    void boxname();
    void reshow();

    void on_lineEdit_editingFinished();


signals:
    void sendsignal3();
    void sendsignal4();
  //  void sendString(QString &s);
};

#endif // FORM_H
