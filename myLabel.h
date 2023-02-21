#pragma once
#include <QObject>
#include <QLabel>
#include <QMessageBox>

class MyQLabel : public QLabel
{
    Q_OBJECT
public:
    MyQLabel(QWidget* parent = 0);
    ~MyQLabel();
signals:
    //����ź�
    void clicked();
public slots:
    //����ź���Ӧ��
 //   void slotClicked();
protected:
    //��갴���¼�
    void mousePressEvent(QMouseEvent*/* event*/);
};