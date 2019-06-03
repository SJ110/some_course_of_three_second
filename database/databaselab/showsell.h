#ifndef SHOWSELL_H
#define SHOWSELL_H

#include <QWidget>
#include"dbconnector.h"
#include<QMessageBox>
#include"QSqlQueryModel"
namespace Ui {
class showSell;
}

class showSell : public QWidget
{
    Q_OBJECT

public:
    explicit showSell(QWidget *parent = 0);
    ~showSell();
    void init();

private:
    Ui::showSell *ui;
    dbConnect db;

signals:
    void sendsignal6();
private slots:
    void on_retButton_clicked();
    void on_exitButton_clicked();
    void on_search_textChanged(const QString &arg1);
    void on_sureButton_clicked();
};

#endif // SHOWSELL_H
