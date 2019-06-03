#include "showsell.h"
#include "ui_showsell.h"

showSell::showSell(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::showSell)
{
    ui->setupUi(this);
    init();
    this->setWindowTitle("销售信息");

}

showSell::~showSell()
{
    delete ui;
}

void showSell::init(){
    QSqlQueryModel *model=new QSqlQueryModel;
    model->setQuery(db.showCHd());
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
    qDebug()<<ui->tableView->model()->rowCount();
}
void showSell::on_retButton_clicked()
{
    emit sendsignal6();
    this->close();
}

void showSell::on_exitButton_clicked()
{
    QMessageBox::StandardButton ret=QMessageBox::information(this, "提示", "确定直接退出？",
                                               QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if(ret==QMessageBox::Yes){
            std::exit(0);
        }
    return;
}

void showSell::on_search_textChanged(const QString &arg1)
{
    QSqlQueryModel *model=new QSqlQueryModel;
    QString fn=arg1;
    model->setQuery(db.unclearsearch3(fn));
    ui->tableView->setModel(model);
    return;
}

void showSell::on_sureButton_clicked()
{
    QSqlQuery query;
    query.exec(db.searchflag()); //此处查找并按时间排序 //query(0) id 1 GID 2 GNAME  3 JHSL 4 time 5 flag
    if(query.next()==false){
        QMessageBox::information(this, "提示", "已经全部出货，请勿重复操作！",
                             QMessageBox::Yes);
        return;
    }

    int flag=0;
    QSqlQuery queryr;
    do{ //已经运行至第一条语句， 使用 do while
        qDebug()<<query.value(5).toString();
        QString str0= query.value(3).toString();
        QString str1=query.value(1).toString();
        QString str2=query.value(4).toString();
         qDebug()<<str0<<str1<<str2;
        if(db.compare(str1,str0)==false){
            flag=1;
            continue;
        }//运行到此表明可以出货
        queryr.exec(db.updateHWbyCH(str0,str1,str2)); //此处更新数据
        queryr.exec(db.updateflag(query.value(0).toString()));//此处更新flag=1;

    }while(query.next());

    if(flag==1){
        QMessageBox::information(this, "提示", "部分货物数量不足或仓库无存货请之后再试！",
                             QMessageBox::Yes);
        return;
    }
    QMessageBox::information(this, "提示", "货物已经全部出货",
                         QMessageBox::Yes);
    return;
}
