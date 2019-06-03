#ifndef MYCOMBOBOX_H
#define MYCOMBOBOX_H
#include<QComboBox>
#include<QMouseEvent>
class MycomboBox:public QComboBox
{
    Q_OBJECT
public:
    explicit MycomboBox(QWidget* parent=0);
    ~MycomboBox();
protected:
    virtual void mousePressEvent(QMouseEvent* e);
signals:
    void clicked();
};
#endif // MYCOBOBOX_H
