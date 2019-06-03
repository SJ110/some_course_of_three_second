#ifndef SHOWDINGD_H
#define SHOWDINGD_H

#include <QWidget>
#include<QSqlQueryModel>
#include<QMessageBox>
#include"dbconnector.h"
namespace Ui {
class showDingD;
}

class showDingD : public QWidget
{
    Q_OBJECT

public:
    explicit showDingD(QWidget *parent = 0);
    ~showDingD();

private:
    Ui::showDingD *ui;
    dbConnect db;
public:
    void init();
signals:
    void sendsignal4();
private slots:
    void on_exitButton_clicked();
    void on_retButton_clicked();
    void on_search_textChanged(const QString &arg1);
    void on_sureButton_clicked();
};

#endif // SHOWDINGD_H
