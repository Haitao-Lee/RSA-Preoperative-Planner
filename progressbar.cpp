#include "ProgressBar.h"
#include <qLayout.h>

ProgressBar::ProgressBar(const QString& fileName, QWidget* parent) :
    QWidget(parent),
    m_bar(this),
    m_value(this),
    m_slider(this),
    m_image(fileName)
{

    m_bar.setMaximum(100);
    m_bar.setMinimum(0);
    m_bar.setValue(0);
    m_bar.setTextVisible(false);
    m_bar.setFixedHeight(20);

    m_slider.setMaximum(100);
    m_slider.setMinimum(0);
    m_slider.setValue(0);
    m_slider.setOrientation(Qt::Horizontal);

    m_value.setText(QString("%1%").arg(m_bar.value()));
    m_value.setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    m_value.setMinimumWidth(40);

    /*设置布局*/
    QHBoxLayout* hlayout = new QHBoxLayout();
    hlayout->addWidget(&m_slider);
    hlayout->addWidget(&m_value, 0, Qt::AlignRight);

    QVBoxLayout* vlayout = new QVBoxLayout();

    vlayout->addWidget(&m_bar);
    vlayout->addLayout(hlayout);
    setLayout(vlayout);

    connect(&m_slider, SIGNAL(valueChanged(int)), &m_bar, SLOT(setValue(int)));
    connect(&m_bar, SIGNAL(valueChanged(int)), this, SLOT(onvalueChanged(int)));

    onvalueChanged(m_bar.value());
}
void ProgressBar::onvalueChanged(int value)
{
    QString qss = "QProgressBar{"
        "border: 1px solid rgb(16, 135, 209);"
        "background: rgba(248,248,255,180);"
        "border-radius: 6px; }"
        "QProgressBar::chunk:enabled {"
        "border-radius: 4px; "
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:0";

    double v = m_bar.maximum();
    double EndColor = static_cast<double>(value) / v;    //获取比例

    for (int i = 0;i < 100;i++)
    {
        double Current = EndColor * i / 100;
        QRgb rgb = m_image.pixel((m_image.width() - 1) * Current, m_image.height() / 2);
        QColor c(rgb);
        qss.append(QString(",stop:%1  rgb(%2,%3,%4)").arg(i / 100.0).arg(c.red()).arg(c.green()).arg(c.blue()));
    }

    qss.append(");}");
    m_bar.setStyleSheet(qss);
    m_value.setText(QString("%1%").arg(m_bar.value()));
}