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
    //点击信号
    void clicked();
public slots:
    //点击信号响应槽
 //   void slotClicked();
protected:
    //鼠标按下事件
    void mousePressEvent(QMouseEvent*/* event*/);
};