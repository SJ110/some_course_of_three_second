#include"mycombobox.h"
//为comboBox增加鼠标点击事件
MycomboBox::MycomboBox(QWidget *parent):QComboBox(parent){

}

MycomboBox::~MycomboBox(){

}

void MycomboBox::mousePressEvent(QMouseEvent *e){
    if(e->button()==Qt::LeftButton)
        emit clicked();
    QComboBox::mousePressEvent(e);
}
