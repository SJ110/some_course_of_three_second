#include "widget.h"
#include "ui_widget.h"
#include"dbconnector.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    showData=new showdata; //important
    connect(showData,SIGNAL(sendsignal()),this,SLOT(reshow()));
    connect(ui->logbutton,SIGNAL(clicked()),this,SLOT(log()));
    connect(ui->exit,SIGNAL(clicked()),this,SLOT(exit()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::reshow() //reshow
{   ui->userlineEdit->setText("");
    ui->pswlineEdit->setText("");
    this->show();
    return ;
}

void Widget::log()
{
//    QDialog* dialog=new QDialog(this);
//    dialog->resize(50,30);
//    QLabel* label =new QLabel(dialog);
//    label->setText(QObject::trUtf8("please enter pass"));
//    const QFont=;
//    label->setFont(QFont);
//    dialog->show();
      dbConnect dbc;
      
      if(ui->userlineEdit->text()==tr("") && ui->pswlineEdit->text()==tr("")){
          QMessageBox::warning(this,tr("警告"),tr("输入用户名或密码"),
                               QMessageBox::Yes);
          ui->userlineEdit->setFocus();
      }
      else if(ui->userlineEdit->text()==dbc.Username("审核") && ui->pswlineEdit->text()==dbc.Psw("审核")){
           this->hide();
           showData->show();//在widge析构前都有效
       }
          else{
                QMessageBox::warning(this,tr("警告"),tr("用户名或密码错误"),
                                     QMessageBox::Yes);
                ui->userlineEdit->setFocus();
       }
}

void Widget::exit()
{
    std::exit(0);
}
