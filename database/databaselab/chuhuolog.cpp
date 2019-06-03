#include "chuhuolog.h"
#include "ui_chuhuolog.h"

chuhuolog::chuhuolog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chuhuolog)
{
    ui->setupUi(this);
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    this->setWindowTitle("销售人员登录");
    this->seLL=new sell;
     connect(seLL,SIGNAL(sendsignal5()),this,SLOT(reshow()));
}

chuhuolog::~chuhuolog()
{
    delete ui;
}

void chuhuolog::on_retButton_clicked()
{
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    emit sendsignal4();
    this->close();

}

void chuhuolog::on_logButton_clicked()
{
    dbConnect dbc;
    ui->lineEdit->setFocus();
    if(ui->lineEdit->text()==tr("") && ui->lineEdit_2->text()==tr("")){
        QMessageBox::warning(this,tr("警告"),tr("输入用户名或密码"),
                             QMessageBox::Yes);
        ui->lineEdit->setFocus();
    }
    else if(ui->lineEdit->text()==dbc.Username("销售") && ui->lineEdit_2->text()==dbc.Psw("销售")){
         this->close();
         this->seLL->show();
         //showData->show();//在widge析构前都有效
     }
        else{
              QMessageBox::warning(this,tr("警告"),tr("用户名或密码错误"),
                                   QMessageBox::Yes);
              ui->lineEdit->setFocus();
     }
}

void chuhuolog::reshow(){
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    this->show();
    return ;
}
