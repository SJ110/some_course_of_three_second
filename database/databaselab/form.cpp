#include "form.h"
#include "ui_form.h"
#pragma execution_character_set("utf-8")
Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    this->setWindowTitle("采购界面");
    this->str0="";
    this->str1="";
    this->dingd=new showDingD;
    QSqlQuery query;
    QStringList list;
    list.append("");
    query.exec(db.selectSPID(ui->nameBox->currentText()));
    while(query.next())
        list.append(query.value(0).toString());
    ui->idBox->addItems(list);
    QStringList list2;
    list2.append("");
    query.exec(db.selectSPNAME(ui->idBox->currentText()));
    while(query.next())
        list2.append(query.value(0).toString());
    ui->nameBox->addItems(list2);
    query.exec(db.selectCFD());
    QStringList list3;
    list3.append("");
    while (query.next()) {
       list3.append(query.value(0).toString());
    }
    ui->cfdBox->addItems(list3);
    QStringList list4;
    list4.append("");
    list4<<"10"<<"20"<<"30"<<"40"<<"50"<<"80"<<"100"<<"150"<<"200";
    ui->numBox->addItems(list4);
    connect(dingd,SIGNAL(sendsignal4()),this,SLOT(reshow()));
    connect(ui->idBox,SIGNAL(clicked()),this,SLOT(boxid()));
    connect(ui->nameBox,SIGNAL(clicked()),this,SLOT(boxname()));
    //   connect(ui->idBox,SIGNAL(sendString(QString &s)),this,SLOT(addId()));

}

Form::~Form()
{
    delete ui;
}

void Form::on_retButton_clicked()
{
    emit sendsignal3();
    this->close();
    return;
}

void Form::on_sureButton_clicked()
{
    ui->label_6->setText("");
    if(ui->lineEdit->text()=="" &&ui->cfdBox->currentText()==""&&ui->idBox->currentText()==""
            &&ui->numBox->currentText()==""&&ui->nameBox->currentText()=="")
    {
  //      emit sendsignal4();
        this->dingd->show();
        this->dingd->init();
        this->close();
        return;
    }
    if(ui->idBox->currentText()=="" || ui->nameBox->currentText()==""||ui->numBox->currentText()==""
                ||ui->cfdBox->currentText()=="")
    {
        QMessageBox::warning(this,tr("警告"),tr("无效的输入格式"),
                             QMessageBox::Yes);
        return;
    }
    //运行至此处可以插入数据
    QString help0;
    help0=ui->lineEdit->text();
    if(help0.size()!=4){
        ui->label_6->setText("请输入有效格式");
        ui->lineEdit->setFocus();
        return;
    }
    for(int i=0;i<help0.size();i++){
        if(help0[i]<'0' || help0[i]>'9'){
            ui->label_6->setText("请输入有效格式");
            ui->lineEdit->setFocus();
            return;
        }
    }
    QString help1;
    help1=ui->idBox->currentText();
    QString help2;
    help2=ui->nameBox->currentText();
    QString help3;
    help3=ui->numBox->currentText();
    QString help4;
    help4=ui->cfdBox->currentText();
    QDateTime now =QDateTime::currentDateTime();
    QString s=now.toString("yyyy-MM-dd hh:mm:ss");
        qDebug()<<help0<<help1<<help2<<help3<<help4<<s;
    QSqlQuery query;
   if(query.exec(db.insertjinhuo(help0,help1,help2,help3,help4,s))==false)
   {
       QMessageBox::warning(this,tr("警告"),tr("数据库中已存在的数据！！"),
                            QMessageBox::Yes);
       ui->lineEdit->setFocus();
       return;
   }

    emit sendsignal4();
    this->dingd->show();
    this->dingd->init();
    this->close();
    return;
}

void Form::boxid()
{
    this->str0=ui->nameBox->currentText();
    qDebug()<<str0;
    QStringList list;
    QSqlQuery query;
        query.exec(db.selectSPID(this->str0));
        while (query.next()) {
            list.append(query.value(0).toString());
        }
        for(int i=0;i<list.size();i++)
        qDebug()<<list[i];
        if(!list.empty())
        {
            list.append("");
            ui->idBox->clear();
            ui->idBox->addItems(list);
   }
        return;
}

void Form::boxname()
{
    this->str1=ui->idBox->currentText();
    QStringList list;
    QSqlQuery query;
        query.exec(db.selectSPNAME(this->str1));
        while(query.next())
            list.append(query.value(0).toString());
        for(int i=0;i<list.size();i++)
        qDebug()<<list[i];
        if(!list.empty()){
            list.append("");
            ui->nameBox->clear();
            ui->nameBox->addItems(list);
        }
    return;
}

void Form::reshow(){
    ui->label_6->setText("");
    ui->lineEdit->setText("") ;
    ui->cfdBox->setCurrentText("");
    ui->idBox->setCurrentText("");
    ui->numBox->setCurrentText("");
    ui->nameBox->setCurrentText("");
    this->show();
}

void Form::on_lineEdit_editingFinished()
{
    ui->label_6->setText("");
    QString str=ui->lineEdit->text();
    if(str.size()!=4){
        ui->label_6->setText("请输入4位数字");
        ui->lineEdit->setFocus();
        return;
    }
    for(int i=0;i<str.size();i++)
        if(str[i]<'0' ||str[0]>'9')
        {
            ui->label_6->setText("输入必须为数字");
            ui->lineEdit->setFocus();
            return;
        }
    return;
}

