#include "showdingd.h"
#include "ui_showdingd.h"

showDingD::showDingD(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::showDingD)
{
    ui->setupUi(this);
    this->setWindowTitle("进货数据");
    // connect(ui->search,SIGNAL(textChanged(QString)),this,SLOT(find()));
    init();
}

showDingD::~showDingD()
{
    delete ui;
}


void showDingD:: init(){
    QSqlQueryModel *model=new QSqlQueryModel;
    model->setQuery(db.showDind());
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
    qDebug()<<ui->tableView->model()->rowCount();
   // ui->tableView->setColumnWidth(5,150);
}



void showDingD::on_exitButton_clicked()
{
    QMessageBox::StandardButton ret=QMessageBox::information(this, "提示", "确定直接退出？",
                                               QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if(ret==QMessageBox::Yes){
            std::exit(0);
        }
    return;
}

void showDingD::on_retButton_clicked()
{
    emit sendsignal4();
    this->close();
    return;
}

void showDingD::on_search_textChanged(const QString &arg1)
{
    QSqlQueryModel *model=new QSqlQueryModel;
    QString fn=arg1;
    model->setQuery(db.unclearsearch2(fn));
    ui->tableView->setModel(model);
    return;
}

void showDingD::on_sureButton_clicked()
{
    QStringList list;
    QString tmp;

    QModelIndex myindex;
    QSqlQuery queryt;
    int flag=0;
    for(int i=0;i<ui->tableView->model()->rowCount();i++){
        queryt.exec("select flag from JH_XX");
        while(queryt.next())
            if(queryt.value(0).toInt()==1) flag=1;
            else {
                flag=0;
                break;
            }
    }
    if(flag==1) {
        QMessageBox::information(this, "提示", "请勿重复提交",
                                                  QMessageBox::Yes);
        return;
    }
    for(int i=0;i<ui->tableView->model()->rowCount();i++){
        for(int count=1;count<ui->tableView->model()->columnCount();count++){

            myindex=ui->tableView->model()->index(i,count);
            tmp=ui->tableView->model()->data(myindex).toString();
            list.append(tmp);
        }
        queryt.exec("select flag from JH_XX where GID"+list[0]); //最好放到dbconnetcor
        queryt.next();
        if(queryt.value(0).toInt()==1){
            list.clear();
            continue;
        }
        QSqlQuery query;
        query.exec(db.selectCFDid(list[3]));
        qDebug()<<list[3];qDebug()<<list[0]<<list[2]<<list[4];
        query.next();
        QString tmp1=query.value(0).toString();
    //   if(QSqlDatabase::database().transaction())    //开启事务
   //    {
            if(query.exec(db.insertHW(list[0],tmp1,list[2],list[4]))==false){
                if(query.exec(db.updateHW(list[2],list[4],list[0]))==false)
                {
                    QMessageBox::information(this, "警告", "数据库错误，请重启！",
                                                               QMessageBox::Yes);
                    std::exit(0);
                }
            }
            query.exec("update JH_XX set flag=1 where GID="+list[0]); //最好放到dbconnector
//           if(!QSqlDatabase::database().commit()) //提交
//           {
//              QSqlDatabase::database().rollback();

//           }
//        }
        list.clear();
    }
     QMessageBox::information(this, "提示", "数据已经提交仓库",
                                               QMessageBox::Yes);
    return;
}
