#include "showcaigou.h"
#include "ui_showcaigou.h"

showcaigou::showcaigou(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::showcaigou)
{
    ui->setupUi(this);
    col=5; //6列
    ui->tableWidget->setRowCount(1);  //不知为何，需要先初始化一行
    ui->tableWidget->setColumnCount(col);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"进货编号"<<"货物编号"
                                               <<"货物名称"<<"进货数量"<<"存放地");

    this->id=new QComboBox;
     QSqlQuery query;
    QStringList list3;
    query.exec(db.selectSPID(""));
    list3.append("");
    while(query.next())
        list3.append(query.value(0).toString());
    this->id->addItems(list3);
    Id.push_back(this->id);

    this->name=new QComboBox;
    QStringList list4;
    query.exec(db.selectSPNAME(""));
    list4.append("");
    while(query.next())
        list4.append(query.value(0).toString());
    this->name->addItems(list4);
    Name.push_back(this->name);

    this->cfd=new QComboBox;
    this->num=new QComboBox;
    Cfd.push_back(cfd);
    Num.push_back(num);
   // init();

    QStringList list2;
     QTableWidgetItem *it=new QTableWidgetItem;
     it->setCheckState(Qt::Unchecked);

    list2<<""<<"10"<<"20"<<"40"<<"50"<<"80"<<"100"<<"200";
    Num[0]->addItems(list2);

    QStringList list;
    list.append("");
    query.exec(db.selectCFD());
    while(query.next())
        list.append(query.value(0).toString());
    Cfd[0]->addItems(list);
    ui->label_2->setText("系统提示：请按行输入数据");
    ui->tableWidget->setCellWidget(0,1,Id[0]);
    ui->tableWidget->setCellWidget(0,2,Name[0]);
    ui->tableWidget->setCellWidget(0,3,Num[0]);
    ui->tableWidget->setCellWidget(0,4,Cfd[0]);
//    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);不需要先选中整行
    ui->tableWidget->setAlternatingRowColors(true); //灰色白色

    connect(ui->sureButton,SIGNAL(clicked()),this,SLOT(on_sureButton_clicked()));
 //   connect(combobox, SIGNAL(currentIndexChanged(int)), this, SIGNAL(OnCurrentIndexChanged(int)));

}

void showcaigou::init(){  //初始化combox Cfd 和 Num;

}


showcaigou::~showcaigou()
{
    delete ui;
}

void showcaigou::on_addButton_clicked()
{
     QSqlQuery query;
    ui->label->setText("");
    int currentRow=ui->tableWidget->currentRow();

     //如果未选中任何一行 需要判断
  //  qDebug()<<currentRow;
    if(currentRow==-1)//最最后一行后加上新的一行
        return; //直接return
    ui->tableWidget->insertRow(currentRow+1);
    this->id=new QComboBox;
    QStringList list3;
    query.exec(db.selectSPID(""));
    list3.append("");
    while(query.next())
        list3.append(query.value(0).toString());
    id->addItems(list3);
    Id.insert(Id.begin()+currentRow,id);
    ui->tableWidget->setCellWidget(currentRow+1,1,id);

    this->name=new QComboBox;
    QStringList list4;
    query.exec(db.selectSPNAME(""));
    list4.append("");
    while(query.next())
        list4.append(query.value(0).toString());
    name->addItems(list4);
    Name.insert(Name.begin()+currentRow,name);
    ui->tableWidget->setCellWidget(currentRow+1,2,name);

    this->num=new QComboBox;
    QStringList list2;
    list2<<""<<"10"<<"20"<<"40"<<"50"<<"80"<<"100"<<"200";
    num->addItems(list2);
    Num.insert(Num.begin()+currentRow,num);
    ui->tableWidget->setCellWidget(currentRow+1,3,num);

    this->cfd=new QComboBox;
    QStringList list;
    list.append("");
    query.exec(db.selectCFD());
    while(query.next())
        list.append(query.value(0).toString());
    cfd->addItems(list);
    Cfd.insert(Cfd.begin()+currentRow,cfd);
    qDebug()<<Cfd.size();
    ui->tableWidget->setCellWidget(currentRow+1,4,cfd);
}

void showcaigou::on_deleteButton_clicked()
{

    int currentRow=ui->tableWidget->currentRow();
    if(currentRow==-1)
        return ;
    if(ui->tableWidget->rowCount()==1){
        ui->label->setText("不可删除最后一行");
        return;
    }
    ui->tableWidget->removeCellWidget(currentRow,1);
    ui->tableWidget->removeCellWidget(currentRow,2);
    ui->tableWidget->removeCellWidget(currentRow,3);
    ui->tableWidget->removeCellWidget(currentRow,4);
    Id.erase(Id.begin()+currentRow);
    Num.erase(Num.begin()+currentRow);
    Name.erase(Name.begin()+currentRow);
    Cfd.erase(Cfd.begin()+currentRow);
    ui->tableWidget->removeRow(currentRow);
    return;
}


void showcaigou::on_sureButton_clicked()
{
//    QMessageBox box;
//    box.setWindowTitle("提示");
//    box.setIcon(QMessageBox::Question);
//    box.setText("确定提交？？？");
//    box.setStandardButtons(QMessageBox::Yes|QMessageBox::No);

//    switch(box.exec()){
//        case QMessageBox::Yes:
//             box.close();
//             this->close();emit sendsignal3();
//             break;
//        case QMessageBox::No:

//        default:  break;
//    }  //sorry  有个小bug 无法实现  放弃了

    int row=ui->tableWidget->rowCount();
    int col=ui->tableWidget->columnCount();
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            QString str0;
          //  ui->tableWidget->item()
            if(ui->tableWidget->item(i,0)->text()==""){
                 ui->label->setText("请添加文本");
                 return ; //此处有一个bug，第一次到show采购界面ID空时确定会报exception
            }
            str0=ui->tableWidget->item(i,0)->text();
            QString tmp=QString("%1%2%3").arg("第").arg(i+1).arg("行数据有错");
            QWidget *widget=ui->tableWidget->cellWidget(i,j);
            QComboBox *sex=(QComboBox*)widget;
            switch (j) {
            case 0:
                if(str0.size()!=4){
                    ui->label->setText(tmp);
                    return;
                }
                for(int i=0;i<str0.size();i++){
                    if(str0[i]<'0' || str0[i]>'9'){
                        ui->label->setText(tmp);
                        return;
                    }
                }
                this->Jid.append(str0);
                break;
            case 1:
                if(str0.size()==0){
                    ui->label->setText(tmp);
                    return;
                }
                 this->Iid.append(sex->currentText());
                break;
            case 2:
                if(str0.size()==0){
                    ui->label->setText(tmp);
                    return;
                }
                this->Gname.append(sex->currentText());
                break;
             case 3:
                if(str0.size()==0){
                    ui->label->setText(tmp);
                    return;
                }
                this->Jnum.append(sex->currentText());
                break;
             case 4:
                if(str0.size()==0){
                    ui->label->setText(tmp);
                    return;
                }
                this->CCfd.append(sex->currentText());
                break;
            }

        }
        qDebug()<<Jid[i]<<Iid[i]<<Gname[i]<<Jnum[i]<<CCfd[i];
    }


    emit sendsignal3();
    for(int i=0;i<ui->tableWidget->rowCount()-1;i++){
        ui->tableWidget->removeCellWidget(i,1);
        ui->tableWidget->removeCellWidget(i,2);
        ui->tableWidget->removeCellWidget(i,3);
        ui->tableWidget->removeCellWidget(i,4);
        Id.erase(Id.begin()+i);
        Num.erase(Num.begin()+i);
        Name.erase(Name.begin()+i);
        Cfd.erase(Cfd.begin()+i);
        ui->tableWidget->removeRow(i);
    }
    ui->label->setText("");
    ui->tableWidget->item(0,0)->setText("");
  //  ui->tableWidget->item(0,11)->setText(""); //设置为空
    this->close();
    return;
}

void showcaigou::on_retButton_clicked()
{
    QMessageBox::StandardButton ret=QMessageBox::information(this, "提示", "确定直接退出？",
                                           QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if(ret==QMessageBox::Yes){
        std::exit(0);
    }
    return;
}
//down

void showcaigou::on_tableWidget_itemClicked(QTableWidgetItem *item)
{
    //出现了bug  所以此处简化， 所有col都为0
    ui->label->setText("");
    int row=item->row();
    int col=item->column();
  //  qDebug()<<ui->tableWidget->cellClicked(0,1);
    if(col==0){
         QString str0=ui->tableWidget->item(row,0)->text();
         if(str0.size()!=4){
             ui->label->setText("请在第一列输入四位的数字");
           }
         for(int i=0;i<str0.size();i++){
             if(str0[i]<'0' || str0[i]>'9'){
                 ui->label->setText("第一列输入必须为数字");
             }
         }
    }
    //clo+1
    QWidget *widget1=ui->tableWidget->cellWidget(row,col+2);
    QComboBox *s1=(QComboBox*)widget1;
    QWidget *widget2=ui->tableWidget->cellWidget(row,col+1);
    QComboBox *s2=(QComboBox*)widget2;
    QSqlQuery query;
        if(s1->currentText()!=""){
            QStringList list;
            query.exec(db.selectSPID(s1->currentText()));
            while(query.next())
                list.append(query.value(0).toString());
            id=new QComboBox;
            this->id->addItems(list);
            for(int i=0;i<list.size();i++)
                qDebug()<<list[i];
            ui->tableWidget->removeCellWidget(row,col+1);
            ui->tableWidget->setCellWidget(row,col+1,this->id);
            for(int i=0;i<list.size();i++)
                qDebug()<<list[i];
            Id[row]=s2;
        }

        if(s2->currentText()!=""){
            QStringList list2;
            query.exec(db.selectSPNAME(s2->currentText()));
            while(query.next())
                list2.append(query.value(0).toString());
            name=new QComboBox;
            this->name->addItems(list2);
            ui->tableWidget->removeCellWidget(row,col+2);
            ui->tableWidget->setCellWidget(row,col+2,name);
        }

}


