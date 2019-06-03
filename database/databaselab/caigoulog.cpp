#include "caigoulog.h"
#include "ui_caigoulog.h"

caigoulog::caigoulog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::caigoulog)
{
    ui->setupUi(this);
    ui->username->setText("");
    ui->pswline->setText("");
    this->setWindowTitle("采购人员登录");
    showCaigou=new Form;
    connect(ui->logButton,SIGNAL(clicked()),this,SLOT(log()));
    connect(ui->retButton,SIGNAL(clicked()),this,SLOT(backup()));
    connect(showCaigou,SIGNAL(sendsignal3()),this,SLOT(reshow()));
}

caigoulog::~caigoulog()
{
    delete ui;
}

void caigoulog::log()
{
    dbConnect dbc;
    ui->username->setFocus();
    if(ui->username->text()==tr("") && ui->pswline->text()==tr("")){
        QMessageBox::warning(this,tr("警告"),tr("输入用户名或密码"),
                             QMessageBox::Yes);
        ui->username->setFocus();
    }
    else if(ui->username->text()==dbc.Username("采购") && ui->pswline->text()==dbc.Psw("采购")){
         this->close();
         showCaigou->show();
         //showData->show();//在widge析构前都有效
     }
        else{
              QMessageBox::warning(this,tr("警告"),tr("用户名或密码错误"),
                                   QMessageBox::Yes);
              ui->username->setFocus();
     }
}

void caigoulog::backup()
{
    emit sendsignal2();
    this->close();
}

void caigoulog::reshow(){
    ui->username->setText("");
    ui->pswline->setText("");
    this->show();
    return ;
}

