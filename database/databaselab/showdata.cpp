#include "showdata.h"
#include "ui_showdata.h"
#include<QSqlQueryModel>
#pragma execution_character_set("utf-8")
showdata::showdata(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::showdata)
{
    ui->setupUi(this);
    this->setWindowTitle("仓库数据查询");
    this->caigou =new caigoulog;
    this->chuhuoLog=new chuhuolog;
  //  this->showCaigou=new showcaigou;
    init();
    connect(ui->chuhuoButton,SIGNAL(clicked()),this,SLOT(chuhuo()));
    connect(ui->jinhuoButton,SIGNAL(clicked()),this,SLOT(jinhuo()));
    connect(ui->exitButton,SIGNAL(clicked()),this,SLOT(exit()));
    connect(ui->backupButton,SIGNAL(clicked()),this,SLOT(backup()));
    connect(ui->sortButton,SIGNAL(clicked()),this,SLOT(sort()));
    connect(ui->search,SIGNAL(textChanged(QString)),this,SLOT(find()));
    connect(caigou,SIGNAL(sendsignal2()),this,SLOT(reshow()));
    connect(chuhuoLog,SIGNAL(sendsignal4()),this,SLOT(reshow()));
}

showdata::~showdata()
{
    delete ui;
}

void showdata::init(){
    dbConnect dbc;
    QSqlQueryModel *model=new QSqlQueryModel;
    model->setQuery(dbc.initshowdata());
    ui->tableView->setModel(model);
    ui->tableView->setColumnWidth(5,150);

   // ui->tableView->resizeColumnsToContents();  //根据数据改变
   // delete model;
}

void showdata::jinhuo(){
    this->close();
    caigou->show();
    return;
}

void showdata::chuhuo(){
    this->close();
    chuhuoLog->show();
    return;
}

void showdata::backup(){
    emit sendsignal();
    this->close();
}

void showdata::exit(){
    std::exit(0);
}

void showdata::reshow()
{
    init();
    this->show();
    return ;
}


void showdata::sort(){
    dbConnect dbc;
    QSqlQueryModel *model=new QSqlQueryModel;
    //model->setQuery(dbc.sortbyGID());

        if(ui->comboBox->currentText()=="编号"){
            model->setQuery(dbc.sortbyGID());
        }
        if(ui->comboBox->currentText()=="时间"){
            model->setQuery(dbc.sortbytime());
        }
        else if(ui->comboBox->currentText()=="库存量")
                model->setQuery((dbc.sortbyKUL()));

        ui->tableView->setModel(model);
        ui->tableView->setColumnWidth(5,150);
        return;
}

void showdata::find(){
    dbConnect dbc;
    QSqlQueryModel *model=new QSqlQueryModel;
    QString fn=ui->search->text();
    model->setQuery(dbc.unclearsearch(fn));
    ui->tableView->setModel(model);
    ui->tableView->setColumnWidth(5,150);
    //model->setQuery("drop view "+ showview);
    return;
}

