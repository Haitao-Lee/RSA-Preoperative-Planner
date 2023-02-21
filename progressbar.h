#pragma once

#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H
#include <QtGui>
#include <QWidget.h>
#include <qprogressbar.h>
#include <qlabel.h>
#include <qslider.h>

class ProgressBar : public QWidget
{
    Q_OBJECT

    QProgressBar m_bar;
    QLabel       m_value;
    QSlider      m_slider;
    QImage       m_image;

protected slots:
    void  onvalueChanged(int value);
public:
    explicit ProgressBar(const QString& fileName, QWidget* parent = 0);
};

#endif // PROGRESSBAR_H