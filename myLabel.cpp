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
//    QMessageBox::information(NULL, QString("����"),
//        QString("QLabel����¼�������"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
//
//}
void MyQLabel::mousePressEvent(QMouseEvent*)
{
    emit clicked();
}
