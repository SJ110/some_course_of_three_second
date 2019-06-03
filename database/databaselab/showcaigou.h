#ifndef SHOWCAIGOU_H
#define SHOWCAIGOU_H

#include <QWidget>
#include<QMessageBox>
#include<QComboBox>
#include<QTableWidgetItem>
#include<QVector>
#include"dbconnector.h"
#pragma execution_character_set("utf-8")
namespace Ui {
class showcaigou;
}

class showcaigou : public QWidget
{
    Q_OBJECT

public:
    explicit showcaigou(QWidget *parent = 0);
    ~showcaigou();

private slots:
    void on_addButton_clicked();

    void on_deleteButton_clicked();

    void on_sureButton_clicked();
    
    void on_retButton_clicked();

    void on_tableWidget_itemClicked(QTableWidgetItem *item);

   // void on_tableWidget_pressed(const QModelIndex &index);

signals:
    void sendsignal3(); //to show showdata

private:
    Ui::showcaigou *ui;
    dbConnect db;
    QComboBox* id;
    QComboBox* name;
    QComboBox* cfd;
    QComboBox* num;
    QVector<QComboBox*> Id;
    QVector<QComboBox*> Name;
    QVector<QComboBox*> Cfd;
    QVector<QComboBox*> Num;
    QStringList Jid;
    QStringList Iid;
    QStringList Gname;
    QStringList Jnum;
    QStringList CCfd;
    int col;
private:
    void init();
 //   showdata  *showDt;
};

#endif // SHOWCAIGOU_H
