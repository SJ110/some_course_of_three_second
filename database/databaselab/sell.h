#ifndef SELL_H
#define SELL_H

#include <QWidget>
#include<QMessageBox>
#include<QSqlQuery>
#include<QDateTime>
#include"dbconnector.h"
#include"mycombobox.h"
#include"showsell.h"
namespace Ui {
class sell;
}

class sell : public QWidget
{
    Q_OBJECT

public:
    explicit sell(QWidget *parent = 0);
    ~sell();

public slots:
    void boxname();
private:
    Ui::sell *ui;
    showSell* Sell;
    dbConnect db;
    QString str0;
    QString str1;
signals:
    void sendsignal5();
    void sendsignal6();
protected slots:
    void boxid();
private slots:
    void on_retButton_clicked();
    void on_sureButton_clicked();
    void on_lineid_editingFinished();
    void reshow();
};

#endif // SELL_H
