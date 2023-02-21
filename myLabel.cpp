#include "myLabel.h"

MyQLabel::MyQLabel( QWidget* parent):QLabel(parent)
{

    connect(this, SIGNAL(clicked()), this, SLOT(slotClicked()));
}

MyQLabel::~MyQLabel()
{

}
//void MyQLabel::slotClicked()
//{
//    QMessageBox::information(NULL, QString("单击"),
//        QString("QLabel点击事件好辣！"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
//
//}
void MyQLabel::mousePressEvent(QMouseEvent*)
{
    emit clicked();
}
