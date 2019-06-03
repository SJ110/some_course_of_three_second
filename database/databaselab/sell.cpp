#include "sell.h"
#include "ui_sell.h"

sell::sell(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sell)
{
    ui->setupUi(this);
    this->setWindowTitle("销售界面");
    this->Sell =new showSell;
    QSqlQuery query;
    QStringList list;
     list.append("");
     query.exec(db.selectHWID(ui->comname->currentText()));
     while(query.next())
         list.append(query.value(0).toString());
     ui->comid->addItems(list);
     QStringList list2;
         list2.append("");
         query.exec(db.selectHWNAME(ui->comid->currentText()));
         while(query.next())
             list2.append(query.value(0).toString());
         ui->comname->addItems(list2);
         QStringList list4;
         list4.append("");
         list4<<"10"<<"20"<<"30"<<"40"<<"50"<<"80"<<"100"<<"150"<<"200";
         ui->comnum->addItems(list4);
         connect(Sell,SIGNAL(sendsignal6()),this,SLOT(reshow()));
         connect(ui->comid,SIGNAL(clicked()),this,SLOT(boxid()));
         connect(ui->comname,SIGNAL(clicked()),this,SLOT(boxname()));
}

sell::~sell()
{
    delete ui;
}

void sell:: boxid(){
    this->str0=ui->comname->currentText();
    qDebug()<<str0;
    QStringList list;
    QSqlQuery query;
        query.exec(db.selectHWID(this->str0));
        while (query.next()) {
            list.append(query.value(0).toString());
        }
        for(int i=0;i<list.size();i++)
        qDebug()<<list[i];
        if(!list.empty())
        {
            list.append("");
            ui->comid->clear();
            ui->comid->addItems(list);
   }
        return;
}

void sell::boxname(){
    this->str1=ui->comid->currentText();
    QStringList list;
    QSqlQuery query;
        query.exec(db.selectHWNAME(this->str1));
        while(query.next())
            list.append(query.value(0).toString());
        for(int i=0;i<list.size();i++)
        qDebug()<<list[i];
        if(!list.empty()){
            list.append("");
            ui->comname->clear();
            ui->comname->addItems(list);
        }
    return;
}


void sell::on_retButton_clicked()
{
    emit sendsignal5();
    this->close();
    return;
}

void sell::on_sureButton_clicked()
{
    ui->info->setText("");
    if(ui->lineid->text()=="" &&ui->comid->currentText()==""&&ui->comname->currentText()==""
            &&ui->comnum->currentText()=="")
    {
        emit sendsignal6();
        this->Sell->show();
        this->Sell->init();
        this->close();
        return;
    }
    if(ui->comid->currentText()=="" || ui->comname->currentText()==""||ui->comnum->currentText()=="")
    {
        QMessageBox::warning(this,tr("警告"),tr("无效的输入格式"),
                             QMessageBox::Yes);
        return;
    }
    //运行至此处获取信息
    QString help0;
    help0=ui->lineid->text();
    if(help0.size()!=4){
        ui->info->setText("请输入有效格式");
        ui->lineid->setFocus();
        return;
    }
    for(int i=0;i<help0.size();i++){
        if(help0[i]<'0' || help0[i]>'9'){
            ui->info->setText("请输入有效格式");
            ui->lineid->setFocus();
            return;
        }
    }
    QString help1;
    help1=ui->comid->currentText();
    QString help2;
    help2=ui->comname->currentText();
    QString help3;
    help3=ui->comnum->currentText();
//    QString help4;
//    help4=ui->cfdBox->currentText();
    QDateTime now =QDateTime::currentDateTime();
    QString s=now.toString("yyyy-MM-dd hh:mm:ss");
        qDebug()<<help0<<help1<<help2<<help3<<s;
    QSqlQuery query;
   if(query.exec(db.insertCH(help0,help1,help2,help3,s))==false)
   {
       QMessageBox::warning(this,tr("警告"),tr("数据库中已存在的数据！！"),
                            QMessageBox::Yes);
       ui->lineid->setFocus();
       return;
   }

    emit sendsignal6();
    this->Sell->show();
    this->Sell->init();
    this->close();
    return;
}

void sell::on_lineid_editingFinished()
{
    ui->info->setText("");
    QString str=ui->lineid->text();
    if(str.size()!=4){
        ui->info->setText("请输入4位数字");
        ui->lineid->setFocus();
        return;
    }
    for(int i=0;i<str.size();i++)
        if(str[i]<'0' ||str[0]>'9')
        {
            ui->info->setText("输入必须为数字");
            ui->lineid->setFocus();
            return;
        }
    return;
}

void sell::reshow(){
    ui->info->setText("");
    ui->lineid->setText("") ;
    ui->comid->setCurrentText("");
    ui->comname->setCurrentText("");
    ui->comnum->setCurrentText("");
    this->show();
}
