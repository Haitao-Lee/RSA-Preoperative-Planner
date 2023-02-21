/********************************************************************************
** Form generated from reading UI file 'ProjectMainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROJECTMAINWINDOW_H
#define UI_PROJECTMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QVTKWidget.h"

QT_BEGIN_NAMESPACE

class Ui_ProjectMainWindow
{
public:
    QAction* actionLoadImage;
    QAction* m_OpenAction;
    QAction* actionclose;
    QAction* actionquit;
    QAction* actionreadme;
    QAction* actionrevision;
    QWidget* m_CentralWidget;
    QGridLayout* gridLayout_7;
    QGroupBox* widget;
    QVBoxLayout* verticalLayout_6;
    QGroupBox* groupBox_11;
    QVBoxLayout* verticalLayout_11;
    QGroupBox* groupBox_13;
    QHBoxLayout* horizontalLayout_6;
    QWidget* window_widget;
    QHBoxLayout* horizontalLayout_3;
    QGroupBox* groupBox_14;
    QHBoxLayout* horizontalLayout_4;
    QWidget* widget_15;
    QHBoxLayout* horizontalLayout_7;
    QGroupBox* groupBox_2;
    QHBoxLayout* horizontalLayout_5;
    QVBoxLayout* verticalLayout_13;
    QPlainTextEdit* output_pte;
    QVTKWidget* operate_window;
    QSlider* opacity_slider;
    QGroupBox* groupBox_12;
    QVBoxLayout* verticalLayout_15;
    QWidget* slicer_widget;
    QVBoxLayout* verticalLayout_16;
    QGroupBox* groupBox_8;
    QVBoxLayout* verticalLayout_17;
    QSlider* horizontalSlider_1;
    QVTKWidget* qvtkWidget_1;
    QGroupBox* groupBox_9;
    QVBoxLayout* verticalLayout_18;
    QSlider* horizontalSlider_2;
    QVTKWidget* qvtkWidget_2;
    QGroupBox* groupBox_10;
    QVBoxLayout* verticalLayout_19;
    QSlider* horizontalSlider_3;
    QVTKWidget* qvtkWidget_3;
    QGroupBox* groupBox;
    QVBoxLayout* verticalLayout_3;
    QGroupBox* groupBox_7;
    QGridLayout* gridLayout_3;
    QHBoxLayout* _2;
    QCheckBox* checkBox_r;
    QCheckBox* checkBox_l;
    QGroupBox* groupBox_6;
    QGridLayout* gridLayout_2;
    QLabel* label;
    QLabel* threshold_lb;
    QSpinBox* marchingCubes_sb;
    QSpinBox* threshold1_sb;
    QGroupBox* groupBox_18;
    QVBoxLayout* verticalLayout;
    QGroupBox* groupBox_16;
    QGridLayout* gridLayout_8;
    QPushButton* seg_button;
    QPushButton* clip_button;
    QCheckBox* clip_first_on;
    QCheckBox* seg_cbox;
    QGroupBox* groupBox_19;
    QGridLayout* gridLayout_4;
    QPushButton* path_button;
    QPushButton* undo_button;
    QPushButton* change_button;
    QGroupBox* groupBox_21;
    QGridLayout* gridLayout_5;
    QPushButton* left_button;
    QPushButton* down_button;
    QPushButton* out_button;
    QPushButton* in_button;
    QPushButton* up_button;
    QPushButton* right_button;
    QGroupBox* groupBox_17;
    QGridLayout* gridLayout;
    QSpinBox* u_d_box;
    QLabel* label_4;
    QSpinBox* spin_box;
    QScrollBar* l_r_scrollbar;
    QLabel* label_3;
    QSpinBox* l_r_box;
    QScrollBar* spin_scrollbar;
    QScrollBar* u_d_scrollbar;
    QLabel* label_2;
    QGroupBox* groupBox_20;
    QVBoxLayout* verticalLayout_14;
    QGroupBox* groupBox_3;
    QHBoxLayout* horizontalLayout;
    QSlider* maxWinWid;
    QSpinBox* window_max_width;
    QGroupBox* groupBox_5;
    QHBoxLayout* horizontalLayout_2;
    QSlider* minWinWid;
    QSpinBox* window_min_width;
    QProgressBar* progressBar;
    QMenuBar* menubar;
    QMenu* m_MenuFile;
    QMenu* menuhelp;
    QStatusBar* m_StatusBar;

    void setupUi(QMainWindow* ProjectMainWindow)
    {
        if (ProjectMainWindow->objectName().isEmpty())
            ProjectMainWindow->setObjectName(QStringLiteral("ProjectMainWindow"));
        ProjectMainWindow->setEnabled(true);
        ProjectMainWindow->resize(2275, 1601);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ProjectMainWindow->sizePolicy().hasHeightForWidth());
        ProjectMainWindow->setSizePolicy(sizePolicy);
        ProjectMainWindow->setMaximumSize(QSize(16777215, 16777215));
        QFont font;
        font.setBold(true);
        font.setItalic(false);
        font.setWeight(75);
        ProjectMainWindow->setFont(font);
        ProjectMainWindow->setFocusPolicy(Qt::WheelFocus);
        ProjectMainWindow->setAutoFillBackground(false);
        ProjectMainWindow->setStyleSheet(QLatin1String("\n"
            "QMainWindow::separator {\n"
            "width: 0px;\n"
            "height: 0px;\n"
            "margin: 0px;\n"
            "padding: 0px;\n"
            "} "));
        ProjectMainWindow->setToolButtonStyle(Qt::ToolButtonTextOnly);
        ProjectMainWindow->setAnimated(true);
        ProjectMainWindow->setDocumentMode(false);
        ProjectMainWindow->setTabShape(QTabWidget::Rounded);
        ProjectMainWindow->setDockNestingEnabled(false);
        actionLoadImage = new QAction(ProjectMainWindow);
        actionLoadImage->setObjectName(QStringLiteral("actionLoadImage"));
        m_OpenAction = new QAction(ProjectMainWindow);
        m_OpenAction->setObjectName(QStringLiteral("m_OpenAction"));
        actionclose = new QAction(ProjectMainWindow);
        actionclose->setObjectName(QStringLiteral("actionclose"));
        actionquit = new QAction(ProjectMainWindow);
        actionquit->setObjectName(QStringLiteral("actionquit"));
        actionreadme = new QAction(ProjectMainWindow);
        actionreadme->setObjectName(QStringLiteral("actionreadme"));
        actionreadme->setIconVisibleInMenu(true);
        actionrevision = new QAction(ProjectMainWindow);
        actionrevision->setObjectName(QStringLiteral("actionrevision"));
        m_CentralWidget = new QWidget(ProjectMainWindow);
        m_CentralWidget->setObjectName(QStringLiteral("m_CentralWidget"));
        m_CentralWidget->setFocusPolicy(Qt::StrongFocus);
        m_CentralWidget->setAutoFillBackground(false);
        m_CentralWidget->setStyleSheet(QStringLiteral(""));
        gridLayout_7 = new QGridLayout(m_CentralWidget);
        gridLayout_7->setSpacing(0);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        gridLayout_7->setContentsMargins(0, 0, 0, 0);
        widget = new QGroupBox(m_CentralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        widget->setLayoutDirection(Qt::LeftToRight);
        widget->setAutoFillBackground(false);
        widget->setStyleSheet(QLatin1String("QGroupBox\n"
            "{\n"
            "background-color:rgb(59, 59, 59)\n"
            "}"));
        verticalLayout_6 = new QVBoxLayout(widget);
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        groupBox_11 = new QGroupBox(widget);
        groupBox_11->setObjectName(QStringLiteral("groupBox_11"));
        groupBox_11->setStyleSheet(QLatin1String("QGroupBox\n"
            "{\n"
            "background-color:rgb(59, 59, 59)\n"
            "}"));
        verticalLayout_11 = new QVBoxLayout(groupBox_11);
        verticalLayout_11->setSpacing(0);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        verticalLayout_11->setContentsMargins(0, 0, 0, 0);
        groupBox_13 = new QGroupBox(groupBox_11);
        groupBox_13->setObjectName(QStringLiteral("groupBox_13"));
        sizePolicy.setHeightForWidth(groupBox_13->sizePolicy().hasHeightForWidth());
        groupBox_13->setSizePolicy(sizePolicy);
        groupBox_13->setStyleSheet(QLatin1String("QGroupBox\n"
            "{\n"
            "background-color:rgb(59, 59, 59)\n"
            "}"));
        horizontalLayout_6 = new QHBoxLayout(groupBox_13);
        horizontalLayout_6->setSpacing(0);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        window_widget = new QWidget(groupBox_13);
        window_widget->setObjectName(QStringLiteral("window_widget"));
        sizePolicy.setHeightForWidth(window_widget->sizePolicy().hasHeightForWidth());
        window_widget->setSizePolicy(sizePolicy);
        horizontalLayout_3 = new QHBoxLayout(window_widget);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        groupBox_14 = new QGroupBox(window_widget);
        groupBox_14->setObjectName(QStringLiteral("groupBox_14"));
        sizePolicy.setHeightForWidth(groupBox_14->sizePolicy().hasHeightForWidth());
        groupBox_14->setSizePolicy(sizePolicy);
        groupBox_14->setMaximumSize(QSize(600, 16777215));
        groupBox_14->setStyleSheet(QLatin1String("QGroupBox\n"
            "{\n"
            "background-color:rgb(59, 59, 59)\n"
            "}"));
        horizontalLayout_4 = new QHBoxLayout(groupBox_14);
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        widget_15 = new QWidget(groupBox_14);
        widget_15->setObjectName(QStringLiteral("widget_15"));
        sizePolicy.setHeightForWidth(widget_15->sizePolicy().hasHeightForWidth());
        widget_15->setSizePolicy(sizePolicy);
        widget_15->setStyleSheet(QLatin1String("QGroupBox\n"
            "{\n"
            "background-color:rgb(59, 59, 59)\n"
            "}"));
        horizontalLayout_7 = new QHBoxLayout(widget_15);
        horizontalLayout_7->setSpacing(0);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        groupBox_2 = new QGroupBox(widget_15);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setEnabled(true);
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        groupBox_2->setMaximumSize(QSize(16777215, 16777215));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial Black"));
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        groupBox_2->setFont(font1);
        groupBox_2->setLayoutDirection(Qt::LeftToRight);
        groupBox_2->setAutoFillBackground(false);
        groupBox_2->setStyleSheet(QLatin1String("QGroupBox\n"
            "{\n"
            "background-color:rgb(59, 59, 59)\n"
            "}"));
        horizontalLayout_5 = new QHBoxLayout(groupBox_2);
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setSizeConstraint(QLayout::SetNoConstraint);
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        verticalLayout_13 = new QVBoxLayout();
        verticalLayout_13->setSpacing(0);
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));
        output_pte = new QPlainTextEdit(groupBox_2);
        output_pte->setObjectName(QStringLiteral("output_pte"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Adobe \346\230\216\351\253\224 Std L"));
        font2.setPointSize(10);
        font2.setBold(true);
        font2.setWeight(75);
        output_pte->setFont(font2);
        output_pte->setStyleSheet(QLatin1String("QPlainTextEdit\n"
            "{\n"
            "  background-color:rgb(59 59, 59)\n"
            "}"));
        output_pte->setFrameShape(QFrame::Box);
        output_pte->setFrameShadow(QFrame::Sunken);
        output_pte->setLineWidth(1);

        verticalLayout_13->addWidget(output_pte);


        horizontalLayout_5->addLayout(verticalLayout_13);


        horizontalLayout_7->addWidget(groupBox_2);


        horizontalLayout_4->addWidget(widget_15);


        horizontalLayout_3->addWidget(groupBox_14);

        operate_window = new QVTKWidget(window_widget);
        operate_window->setObjectName(QStringLiteral("operate_window"));
        operate_window->setEnabled(true);
        sizePolicy.setHeightForWidth(operate_window->sizePolicy().hasHeightForWidth());
        operate_window->setSizePolicy(sizePolicy);
        operate_window->setMinimumSize(QSize(0, 0));
        operate_window->setMaximumSize(QSize(160000, 1600000));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font3.setPointSize(15);
        operate_window->setFont(font3);
        operate_window->setFocusPolicy(Qt::ClickFocus);
        operate_window->setLayoutDirection(Qt::LeftToRight);
        operate_window->setAutoFillBackground(true);
        operate_window->setStyleSheet(QLatin1String("QGroupBox\n"
            "{\n"
            "background-color:rgb(0, 105, 255)\n"
            "}"));

        horizontalLayout_3->addWidget(operate_window);

        opacity_slider = new QSlider(window_widget);
        opacity_slider->setObjectName(QStringLiteral("opacity_slider"));
        opacity_slider->setMinimumSize(QSize(20, 0));
        opacity_slider->setMaximumSize(QSize(30, 16777215));
        opacity_slider->setLayoutDirection(Qt::LeftToRight);
        opacity_slider->setOrientation(Qt::Vertical);

        horizontalLayout_3->addWidget(opacity_slider);

        groupBox_12 = new QGroupBox(window_widget);
        groupBox_12->setObjectName(QStringLiteral("groupBox_12"));
        sizePolicy.setHeightForWidth(groupBox_12->sizePolicy().hasHeightForWidth());
        groupBox_12->setSizePolicy(sizePolicy);
        groupBox_12->setMaximumSize(QSize(500, 1600000));
        groupBox_12->setStyleSheet(QLatin1String("QGroupBox\n"
            "{\n"
            "background-color:rgb(59, 59, 59)\n"
            "}"));
        verticalLayout_15 = new QVBoxLayout(groupBox_12);
        verticalLayout_15->setSpacing(0);
        verticalLayout_15->setObjectName(QStringLiteral("verticalLayout_15"));
        verticalLayout_15->setContentsMargins(0, 0, 0, 0);
        slicer_widget = new QWidget(groupBox_12);
        slicer_widget->setObjectName(QStringLiteral("slicer_widget"));
        sizePolicy.setHeightForWidth(slicer_widget->sizePolicy().hasHeightForWidth());
        slicer_widget->setSizePolicy(sizePolicy);
        slicer_widget->setMaximumSize(QSize(1677777, 16777215));
        verticalLayout_16 = new QVBoxLayout(slicer_widget);
        verticalLayout_16->setSpacing(0);
        verticalLayout_16->setObjectName(QStringLiteral("verticalLayout_16"));
        verticalLayout_16->setContentsMargins(0, 0, 0, 0);
        groupBox_8 = new QGroupBox(slicer_widget);
        groupBox_8->setObjectName(QStringLiteral("groupBox_8"));
        sizePolicy.setHeightForWidth(groupBox_8->sizePolicy().hasHeightForWidth());
        groupBox_8->setSizePolicy(sizePolicy);
        groupBox_8->setStyleSheet(QLatin1String("QGroupBox\n"
            "{\n"
            "background-color:rgb(59, 59, 59)\n"
            "}"));
        verticalLayout_17 = new QVBoxLayout(groupBox_8);
        verticalLayout_17->setSpacing(0);
        verticalLayout_17->setObjectName(QStringLiteral("verticalLayout_17"));
        verticalLayout_17->setContentsMargins(0, 0, 0, 0);
        horizontalSlider_1 = new QSlider(groupBox_8);
        horizontalSlider_1->setObjectName(QStringLiteral("horizontalSlider_1"));
        sizePolicy.setHeightForWidth(horizontalSlider_1->sizePolicy().hasHeightForWidth());
        horizontalSlider_1->setSizePolicy(sizePolicy);
        horizontalSlider_1->setMaximumSize(QSize(160000, 20));
        horizontalSlider_1->setContextMenuPolicy(Qt::ActionsContextMenu);
        horizontalSlider_1->setLayoutDirection(Qt::RightToLeft);
        horizontalSlider_1->setOrientation(Qt::Horizontal);

        verticalLayout_17->addWidget(horizontalSlider_1);

        qvtkWidget_1 = new QVTKWidget(groupBox_8);
        qvtkWidget_1->setObjectName(QStringLiteral("qvtkWidget_1"));
        sizePolicy.setHeightForWidth(qvtkWidget_1->sizePolicy().hasHeightForWidth());
        qvtkWidget_1->setSizePolicy(sizePolicy);
        qvtkWidget_1->setMaximumSize(QSize(160000, 1600000));
        qvtkWidget_1->setStyleSheet(QLatin1String("QGroupBox\n"
            "{\n"
            "background-color:rgb(0, 0, 0)\n"
            "}"));

        verticalLayout_17->addWidget(qvtkWidget_1);


        verticalLayout_16->addWidget(groupBox_8);

        groupBox_9 = new QGroupBox(slicer_widget);
        groupBox_9->setObjectName(QStringLiteral("groupBox_9"));
        sizePolicy.setHeightForWidth(groupBox_9->sizePolicy().hasHeightForWidth());
        groupBox_9->setSizePolicy(sizePolicy);
        groupBox_9->setStyleSheet(QLatin1String("QGroupBox\n"
            "{\n"
            "background-color:rgb(59, 59, 59)\n"
            "}"));
        verticalLayout_18 = new QVBoxLayout(groupBox_9);
        verticalLayout_18->setSpacing(0);
        verticalLayout_18->setObjectName(QStringLiteral("verticalLayout_18"));
        verticalLayout_18->setContentsMargins(0, 0, 0, 0);
        horizontalSlider_2 = new QSlider(groupBox_9);
        horizontalSlider_2->setObjectName(QStringLiteral("horizontalSlider_2"));
        sizePolicy.setHeightForWidth(horizontalSlider_2->sizePolicy().hasHeightForWidth());
        horizontalSlider_2->setSizePolicy(sizePolicy);
        horizontalSlider_2->setMaximumSize(QSize(160000, 20));
        horizontalSlider_2->setLayoutDirection(Qt::RightToLeft);
        horizontalSlider_2->setStyleSheet(QLatin1String("QSlicer\n"
            "{\n"
            "background-color:rgb(0, 255, 0)\n"
            "}"));
        horizontalSlider_2->setOrientation(Qt::Horizontal);

        verticalLayout_18->addWidget(horizontalSlider_2);

        qvtkWidget_2 = new QVTKWidget(groupBox_9);
        qvtkWidget_2->setObjectName(QStringLiteral("qvtkWidget_2"));
        sizePolicy.setHeightForWidth(qvtkWidget_2->sizePolicy().hasHeightForWidth());
        qvtkWidget_2->setSizePolicy(sizePolicy);
        qvtkWidget_2->setMaximumSize(QSize(160000, 16777215));
        qvtkWidget_2->setStyleSheet(QLatin1String("QGroupBox\n"
            "{\n"
            "background-color:rgb(0, 0, 0)\n"
            "}"));

        verticalLayout_18->addWidget(qvtkWidget_2);


        verticalLayout_16->addWidget(groupBox_9);

        groupBox_10 = new QGroupBox(slicer_widget);
        groupBox_10->setObjectName(QStringLiteral("groupBox_10"));
        sizePolicy.setHeightForWidth(groupBox_10->sizePolicy().hasHeightForWidth());
        groupBox_10->setSizePolicy(sizePolicy);
        groupBox_10->setStyleSheet(QLatin1String("QGroupBox\n"
            "{\n"
            "background-color:rgb(59, 59, 59)\n"
            "}"));
        verticalLayout_19 = new QVBoxLayout(groupBox_10);
        verticalLayout_19->setSpacing(0);
        verticalLayout_19->setObjectName(QStringLiteral("verticalLayout_19"));
        verticalLayout_19->setContentsMargins(0, 0, 0, 0);
        horizontalSlider_3 = new QSlider(groupBox_10);
        horizontalSlider_3->setObjectName(QStringLiteral("horizontalSlider_3"));
        sizePolicy.setHeightForWidth(horizontalSlider_3->sizePolicy().hasHeightForWidth());
        horizontalSlider_3->setSizePolicy(sizePolicy);
        horizontalSlider_3->setMaximumSize(QSize(16000, 20));
        horizontalSlider_3->setLayoutDirection(Qt::RightToLeft);
        horizontalSlider_3->setOrientation(Qt::Horizontal);

        verticalLayout_19->addWidget(horizontalSlider_3);

        qvtkWidget_3 = new QVTKWidget(groupBox_10);
        qvtkWidget_3->setObjectName(QStringLiteral("qvtkWidget_3"));
        sizePolicy.setHeightForWidth(qvtkWidget_3->sizePolicy().hasHeightForWidth());
        qvtkWidget_3->setSizePolicy(sizePolicy);
        qvtkWidget_3->setMaximumSize(QSize(160000, 16777215));
        qvtkWidget_3->setStyleSheet(QLatin1String("QGroupBox\n"
            "{\n"
            "background-color:rgb(0, 0, 0)\n"
            "}"));

        verticalLayout_19->addWidget(qvtkWidget_3);


        verticalLayout_16->addWidget(groupBox_10);


        verticalLayout_15->addWidget(slicer_widget);


        horizontalLayout_3->addWidget(groupBox_12);


        horizontalLayout_6->addWidget(window_widget);


        verticalLayout_11->addWidget(groupBox_13);


        verticalLayout_6->addWidget(groupBox_11);


        gridLayout_7->addWidget(widget, 0, 1, 1, 1);

        groupBox = new QGroupBox(m_CentralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        groupBox->setMaximumSize(QSize(600, 16777215));
        groupBox->setStyleSheet(QLatin1String("QGroupBox\n"
            "{\n"
            "background-color:rgb(59, 59, 59)\n"
            "}"));
        groupBox->setFlat(false);
        verticalLayout_3 = new QVBoxLayout(groupBox);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        groupBox_7 = new QGroupBox(groupBox);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox_7->sizePolicy().hasHeightForWidth());
        groupBox_7->setSizePolicy(sizePolicy1);
        groupBox_7->setStyleSheet(QLatin1String("QGroupBox\n"
            "{\n"
            "background-color:rgb(59, 59, 59)\n"
            "}"));
        gridLayout_3 = new QGridLayout(groupBox_7);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setVerticalSpacing(0);
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        _2 = new QHBoxLayout();
        _2->setSpacing(0);
        _2->setObjectName(QStringLiteral("_2"));
        _2->setContentsMargins(18, 12, 18, 0);
        checkBox_r = new QCheckBox(groupBox_7);
        checkBox_r->setObjectName(QStringLiteral("checkBox_r"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(checkBox_r->sizePolicy().hasHeightForWidth());
        checkBox_r->setSizePolicy(sizePolicy2);
        QFont font4;
        font4.setFamily(QStringLiteral("Consolas"));
        font4.setPointSize(18);
        font4.setBold(true);
        font4.setUnderline(true);
        font4.setWeight(75);
        checkBox_r->setFont(font4);
        checkBox_r->setLayoutDirection(Qt::RightToLeft);
        checkBox_r->setStyleSheet(QLatin1String("\n"
            "QCheckBox::indicator {\n"
            "width: 60px;\n"
            "height: 60px;\n"
            "};\n"
            ""));

        _2->addWidget(checkBox_r);

        checkBox_l = new QCheckBox(groupBox_7);
        checkBox_l->setObjectName(QStringLiteral("checkBox_l"));
        sizePolicy2.setHeightForWidth(checkBox_l->sizePolicy().hasHeightForWidth());
        checkBox_l->setSizePolicy(sizePolicy2);
        checkBox_l->setFont(font4);
        checkBox_l->setLayoutDirection(Qt::RightToLeft);
        checkBox_l->setStyleSheet(QLatin1String("\n"
            "QCheckBox::indicator {\n"
            "width: 60px;\n"
            "height: 60px;\n"
            "};"));

        _2->addWidget(checkBox_l);


        gridLayout_3->addLayout(_2, 0, 0, 1, 1);

        groupBox_6 = new QGroupBox(groupBox_7);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        sizePolicy.setHeightForWidth(groupBox_6->sizePolicy().hasHeightForWidth());
        groupBox_6->setSizePolicy(sizePolicy);
        QFont font5;
        font5.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font5.setPointSize(18);
        font5.setBold(true);
        font5.setWeight(75);
        groupBox_6->setFont(font5);
        groupBox_6->setStyleSheet(QLatin1String("QGroupBox\n"
            "{\n"
            "background-color:rgb(59, 59, 59)\n"
            "}"));
        gridLayout_2 = new QGridLayout(groupBox_6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(-1, 18, 18, 18);
        label = new QLabel(groupBox_6);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy3);
        label->setMaximumSize(QSize(16777215, 120));
        QFont font6;
        font6.setFamily(QStringLiteral("Consolas"));
        font6.setPointSize(18);
        font6.setBold(true);
        font6.setWeight(75);
        label->setFont(font6);
        label->setStyleSheet(QLatin1String("QLabel\n"
            "{\n"
            "  background-color:rgb(100, 100, 93)\n"
            "}"));
        label->setFrameShape(QFrame::WinPanel);
        label->setFrameShadow(QFrame::Raised);

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        threshold_lb = new QLabel(groupBox_6);
        threshold_lb->setObjectName(QStringLiteral("threshold_lb"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(threshold_lb->sizePolicy().hasHeightForWidth());
        threshold_lb->setSizePolicy(sizePolicy4);
        QFont font7;
        font7.setFamily(QStringLiteral("Consolas"));
        font7.setPointSize(18);
        font7.setBold(true);
        font7.setUnderline(false);
        font7.setWeight(75);
        font7.setStrikeOut(false);
        threshold_lb->setFont(font7);
        threshold_lb->setTabletTracking(false);
        threshold_lb->setStyleSheet(QLatin1String("QLabel\n"
            "{\n"
            "  background-color:rgb(100, 100, 93)\n"
            "}"));
        threshold_lb->setFrameShape(QFrame::WinPanel);
        threshold_lb->setFrameShadow(QFrame::Raised);
        threshold_lb->setLineWidth(15);
        threshold_lb->setMidLineWidth(-3);

        gridLayout_2->addWidget(threshold_lb, 1, 0, 1, 1);

        marchingCubes_sb = new QSpinBox(groupBox_6);
        marchingCubes_sb->setObjectName(QStringLiteral("matchingCubes_sb"));
        sizePolicy1.setHeightForWidth(marchingCubes_sb->sizePolicy().hasHeightForWidth());
        marchingCubes_sb->setSizePolicy(sizePolicy1);
        marchingCubes_sb->setMinimumSize(QSize(120, 60));
        marchingCubes_sb->setMaximumSize(QSize(120, 16777215));
        QFont font8;
        font8.setFamily(QStringLiteral("Arial"));
        font8.setPointSize(18);
        font8.setBold(true);
        font8.setWeight(75);
        marchingCubes_sb->setFont(font8);

        gridLayout_2->addWidget(marchingCubes_sb, 0, 1, 1, 1);

        threshold1_sb = new QSpinBox(groupBox_6);
        threshold1_sb->setObjectName(QStringLiteral("threshold_sb"));
        threshold1_sb->setMinimumSize(QSize(120, 60));
        threshold1_sb->setMaximumSize(QSize(120, 16777215));
        threshold1_sb->setFont(font8);

        gridLayout_2->addWidget(threshold1_sb, 1, 1, 1, 1);


        gridLayout_3->addWidget(groupBox_6, 1, 0, 1, 1);


        verticalLayout_3->addWidget(groupBox_7);

        groupBox_18 = new QGroupBox(groupBox);
        groupBox_18->setObjectName(QStringLiteral("groupBox_18"));
        sizePolicy.setHeightForWidth(groupBox_18->sizePolicy().hasHeightForWidth());
        groupBox_18->setSizePolicy(sizePolicy);
        groupBox_18->setMaximumSize(QSize(16777215, 340));
        QFont font9;
        font9.setFamily(QStringLiteral("Arial Black"));
        font9.setPointSize(18);
        font9.setBold(true);
        font9.setItalic(false);
        font9.setUnderline(false);
        font9.setWeight(75);
        groupBox_18->setFont(font9);
        groupBox_18->setStyleSheet(QLatin1String("QGroupBox\n"
            "{\n"
            "background-color:rgb(59, 59, 59)\n"
            "}"));
        groupBox_18->setFlat(false);
        verticalLayout = new QVBoxLayout(groupBox_18);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        groupBox_16 = new QGroupBox(groupBox_18);
        groupBox_16->setObjectName(QStringLiteral("groupBox_16"));
        sizePolicy.setHeightForWidth(groupBox_16->sizePolicy().hasHeightForWidth());
        groupBox_16->setSizePolicy(sizePolicy);
        groupBox_16->setMinimumSize(QSize(0, 180));
        groupBox_16->setMaximumSize(QSize(16777215, 200));
        gridLayout_8 = new QGridLayout(groupBox_16);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        seg_button = new QPushButton(groupBox_16);
        seg_button->setObjectName(QStringLiteral("seg_button"));
        sizePolicy2.setHeightForWidth(seg_button->sizePolicy().hasHeightForWidth());
        seg_button->setSizePolicy(sizePolicy2);
        seg_button->setMinimumSize(QSize(0, 60));
        seg_button->setMaximumSize(QSize(16777215, 60));
        QFont font10;
        font10.setFamily(QStringLiteral("Consolas"));
        font10.setPointSize(19);
        font10.setBold(true);
        font10.setWeight(75);
        seg_button->setFont(font10);
        seg_button->setStyleSheet(QLatin1String("QPushButton\n"
            "{\n"
            "  background-color:rgb(180, 180, 180);\n"
            "\n"
            " \n"
            "}"));
        seg_button->setFlat(false);

        gridLayout_8->addWidget(seg_button, 2, 2, 1, 1);

        clip_button = new QPushButton(groupBox_16);
        clip_button->setObjectName(QStringLiteral("clip_button"));
        clip_button->setEnabled(true);
        sizePolicy.setHeightForWidth(clip_button->sizePolicy().hasHeightForWidth());
        clip_button->setSizePolicy(sizePolicy);
        clip_button->setMinimumSize(QSize(0, 60));
        clip_button->setMaximumSize(QSize(16777215, 60));
        clip_button->setFont(font10);
        clip_button->setMouseTracking(true);
        clip_button->setAcceptDrops(false);
        clip_button->setAutoFillBackground(false);
        clip_button->setStyleSheet(QLatin1String("QPushButton\n"
            "{\n"
            "  background-color:rgb(180, 180, 180);\n"
            "\n"
            " \n"
            "}"));
        clip_button->setInputMethodHints(Qt::ImhHiddenText);
        clip_button->setAutoDefault(false);
        clip_button->setFlat(false);

        gridLayout_8->addWidget(clip_button, 0, 2, 1, 1);

        clip_first_on = new QCheckBox(groupBox_16);
        clip_first_on->setObjectName(QStringLiteral("clip_first_on"));
        sizePolicy2.setHeightForWidth(clip_first_on->sizePolicy().hasHeightForWidth());
        clip_first_on->setSizePolicy(sizePolicy2);
        clip_first_on->setMaximumSize(QSize(16777215, 200));
        QFont font11;
        font11.setFamily(QString::fromUtf8("Adobe \351\273\221\344\275\223 Std R"));
        font11.setPointSize(16);
        font11.setBold(true);
        font11.setUnderline(true);
        font11.setWeight(75);
        clip_first_on->setFont(font11);
        clip_first_on->setLayoutDirection(Qt::RightToLeft);
        clip_first_on->setStyleSheet(QLatin1String("\n"
            "\n"
            "QCheckBox::indicator {\n"
            "width: 70px;\n"
            "height: 70px;\n"
            "};"));

        gridLayout_8->addWidget(clip_first_on, 0, 3, 1, 1);

        seg_cbox = new QCheckBox(groupBox_16);
        seg_cbox->setObjectName(QStringLiteral("seg_cbox"));
        seg_cbox->setFont(font11);
        seg_cbox->setLayoutDirection(Qt::RightToLeft);
        seg_cbox->setStyleSheet(QLatin1String("\n"
            "QCheckBox::indicator {\n"
            "width: 70px;\n"
            "height: 70px;\n"
            "};"));

        gridLayout_8->addWidget(seg_cbox, 2, 3, 1, 1);


        verticalLayout->addWidget(groupBox_16);

        groupBox_19 = new QGroupBox(groupBox_18);
        groupBox_19->setObjectName(QStringLiteral("groupBox_19"));
        sizePolicy.setHeightForWidth(groupBox_19->sizePolicy().hasHeightForWidth());
        groupBox_19->setSizePolicy(sizePolicy);
        groupBox_19->setMaximumSize(QSize(16777215, 100));
        gridLayout_4 = new QGridLayout(groupBox_19);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setHorizontalSpacing(18);
        gridLayout_4->setVerticalSpacing(0);
        gridLayout_4->setContentsMargins(18, 10, 18, 10);
        path_button = new QPushButton(groupBox_19);
        path_button->setObjectName(QStringLiteral("path_button"));
        sizePolicy2.setHeightForWidth(path_button->sizePolicy().hasHeightForWidth());
        path_button->setSizePolicy(sizePolicy2);
        path_button->setMinimumSize(QSize(0, 65));
        path_button->setMaximumSize(QSize(16777215, 60));
        QFont font12;
        font12.setFamily(QStringLiteral("Consolas"));
        font12.setPointSize(14);
        font12.setBold(true);
        font12.setWeight(75);
        path_button->setFont(font12);
        path_button->setStyleSheet(QLatin1String("QPushButton\n"
            "{\n"
            "  background-color:rgb(180, 180, 180);\n"
            "\n"
            " \n"
            "}"));

        gridLayout_4->addWidget(path_button, 1, 3, 1, 1);

        undo_button = new QPushButton(groupBox_19);
        undo_button->setObjectName(QStringLiteral("undo_button"));
        sizePolicy2.setHeightForWidth(undo_button->sizePolicy().hasHeightForWidth());
        undo_button->setSizePolicy(sizePolicy2);
        undo_button->setMinimumSize(QSize(0, 65));
        undo_button->setMaximumSize(QSize(16777215, 60));
        undo_button->setFont(font12);
        undo_button->setStyleSheet(QLatin1String("QPushButton\n"
            "{\n"
            "  background-color:rgb(180, 180, 180);\n"
            "\n"
            " \n"
            "}"));

        gridLayout_4->addWidget(undo_button, 1, 1, 1, 1);

        change_button = new QPushButton(groupBox_19);
        change_button->setObjectName(QStringLiteral("change_button"));
        change_button->setEnabled(false);
        sizePolicy2.setHeightForWidth(change_button->sizePolicy().hasHeightForWidth());
        change_button->setSizePolicy(sizePolicy2);
        change_button->setMinimumSize(QSize(0, 65));
        change_button->setMaximumSize(QSize(16777215, 60));
        QFont font13;
        font13.setFamily(QStringLiteral("Consolas"));
        font13.setPointSize(14);
        font13.setBold(true);
        font13.setWeight(75);
        font13.setKerning(true);
        font13.setStyleStrategy(QFont::PreferDefault);
        change_button->setFont(font13);
        change_button->setAutoFillBackground(false);
        change_button->setStyleSheet(QLatin1String("QPushButton\n"
            "{\n"
            "  background-color:rgb(180, 180, 180);\n"
            "\n"
            " \n"
            "}"));
        change_button->setCheckable(false);
        change_button->setAutoExclusive(false);
        change_button->setAutoDefault(false);
        change_button->setFlat(false);

        gridLayout_4->addWidget(change_button, 1, 2, 1, 1);


        verticalLayout->addWidget(groupBox_19);


        verticalLayout_3->addWidget(groupBox_18);

        groupBox_21 = new QGroupBox(groupBox);
        groupBox_21->setObjectName(QStringLiteral("groupBox_21"));
        sizePolicy.setHeightForWidth(groupBox_21->sizePolicy().hasHeightForWidth());
        groupBox_21->setSizePolicy(sizePolicy);
        groupBox_21->setMaximumSize(QSize(16777215, 340));
        QFont font14;
        font14.setFamily(QStringLiteral("Arial Black"));
        font14.setPointSize(18);
        font14.setBold(true);
        font14.setWeight(75);
        groupBox_21->setFont(font14);
        groupBox_21->setStyleSheet(QLatin1String("QGroupBox\n"
            "{\n"
            "background-color:rgb(59, 59, 59);\n"
            "\n"
            "}"));
        gridLayout_5 = new QGridLayout(groupBox_21);
        gridLayout_5->setSpacing(20);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        gridLayout_5->setContentsMargins(-1, 5, -1, -1);
        left_button = new QPushButton(groupBox_21);
        left_button->setObjectName(QStringLiteral("left_button"));
        left_button->setMinimumSize(QSize(0, 60));
        QFont font15;
        font15.setFamily(QStringLiteral("Consolas"));
        font15.setPointSize(16);
        font15.setBold(true);
        font15.setWeight(75);
        left_button->setFont(font15);
        left_button->setStyleSheet(QLatin1String("QPushButton\n"
            "{\n"
            "  background-color:rgb(180, 180, 180);\n"
            "\n"
            " \n"
            "}"));

        gridLayout_5->addWidget(left_button, 2, 2, 1, 1);

        down_button = new QPushButton(groupBox_21);
        down_button->setObjectName(QStringLiteral("down_button"));
        down_button->setMinimumSize(QSize(0, 60));
        down_button->setFont(font15);
        down_button->setStyleSheet(QLatin1String("QPushButton\n"
            "{\n"
            "  background-color:rgb(180, 180, 180);\n"
            "\n"
            " \n"
            "}"));

        gridLayout_5->addWidget(down_button, 1, 4, 1, 1);

        out_button = new QPushButton(groupBox_21);
        out_button->setObjectName(QStringLiteral("out_button"));
        out_button->setMinimumSize(QSize(0, 60));
        out_button->setFont(font15);
        out_button->setStyleSheet(QLatin1String("QPushButton\n"
            "{\n"
            "  background-color:rgb(180, 180, 180);\n"
            "\n"
            " \n"
            "}"));

        gridLayout_5->addWidget(out_button, 0, 4, 1, 1);

        in_button = new QPushButton(groupBox_21);
        in_button->setObjectName(QStringLiteral("in_button"));
        in_button->setMinimumSize(QSize(0, 60));
        in_button->setFont(font15);
        in_button->setStyleSheet(QLatin1String("QPushButton\n"
            "{\n"
            "  background-color:rgb(180, 180, 180);\n"
            "\n"
            " \n"
            "}"));

        gridLayout_5->addWidget(in_button, 0, 2, 1, 1);

        up_button = new QPushButton(groupBox_21);
        up_button->setObjectName(QStringLiteral("up_button"));
        up_button->setMinimumSize(QSize(0, 60));
        up_button->setFont(font15);
        up_button->setStyleSheet(QLatin1String("QPushButton\n"
            "{\n"
            "  background-color:rgb(180, 180, 180);\n"
            "\n"
            " \n"
            "}"));

        gridLayout_5->addWidget(up_button, 1, 2, 1, 1);

        right_button = new QPushButton(groupBox_21);
        right_button->setObjectName(QStringLiteral("right_button"));
        right_button->setMinimumSize(QSize(0, 60));
        right_button->setFont(font15);
        right_button->setStyleSheet(QLatin1String("QPushButton\n"
            "{\n"
            "  background-color:rgb(180, 180, 180);\n"
            "\n"
            " \n"
            "}"));

        gridLayout_5->addWidget(right_button, 2, 4, 1, 1);


        verticalLayout_3->addWidget(groupBox_21);

        groupBox_17 = new QGroupBox(groupBox);
        groupBox_17->setObjectName(QStringLiteral("groupBox_17"));
        sizePolicy.setHeightForWidth(groupBox_17->sizePolicy().hasHeightForWidth());
        groupBox_17->setSizePolicy(sizePolicy);
        groupBox_17->setMinimumSize(QSize(0, 60));
        groupBox_17->setMaximumSize(QSize(16777215, 600));
        groupBox_17->setFont(font14);
        groupBox_17->setStyleSheet(QLatin1String("QGroupBox\n"
            "{\n"
            "background-color:rgb(59, 59, 59)\n"
            "}"));
        gridLayout = new QGridLayout(groupBox_17);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setHorizontalSpacing(12);
        gridLayout->setVerticalSpacing(0);
        gridLayout->setContentsMargins(18, 0, 18, 0);
        u_d_box = new QSpinBox(groupBox_17);
        u_d_box->setObjectName(QStringLiteral("u_d_box"));
        u_d_box->setMinimumSize(QSize(0, 60));
        u_d_box->setMaximumSize(QSize(120, 16777215));
        u_d_box->setFont(font8);

        gridLayout->addWidget(u_d_box, 2, 4, 1, 1);

        label_4 = new QLabel(groupBox_17);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMaximumSize(QSize(120, 16777215));
        QFont font16;
        font16.setFamily(QStringLiteral("Arial Narrow"));
        font16.setPointSize(12);
        font16.setBold(true);
        font16.setWeight(75);
        label_4->setFont(font16);
        label_4->setLayoutDirection(Qt::LeftToRight);

        gridLayout->addWidget(label_4, 4, 0, 1, 1);

        spin_box = new QSpinBox(groupBox_17);
        spin_box->setObjectName(QStringLiteral("spin_box"));
        spin_box->setMinimumSize(QSize(0, 60));
        spin_box->setMaximumSize(QSize(120, 16777215));
        spin_box->setFont(font8);

        gridLayout->addWidget(spin_box, 4, 4, 1, 1);

        l_r_scrollbar = new QScrollBar(groupBox_17);
        l_r_scrollbar->setObjectName(QStringLiteral("l_r_scrollbar"));
        l_r_scrollbar->setMinimumSize(QSize(0, 60));
        l_r_scrollbar->setStyleSheet(QLatin1String("QScrollBar\n"
            "{\n"
            "background-color:rgb(44, 62, 89)\n"
            "}"));
        l_r_scrollbar->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(l_r_scrollbar, 3, 1, 1, 1);

        label_3 = new QLabel(groupBox_17);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMaximumSize(QSize(120, 16777215));
        label_3->setFont(font16);
        label_3->setPixmap(QPixmap(QString::fromUtf8("Qt-bin/Debug/resources/\345\267\246\345\217\263\347\256\255\345\244\264.png")));

        gridLayout->addWidget(label_3, 3, 0, 1, 1);

        l_r_box = new QSpinBox(groupBox_17);
        l_r_box->setObjectName(QStringLiteral("l_r_box"));
        l_r_box->setMinimumSize(QSize(0, 60));
        l_r_box->setMaximumSize(QSize(120, 16777215));
        l_r_box->setFont(font8);
        l_r_box->setStyleSheet(QStringLiteral(""));

        gridLayout->addWidget(l_r_box, 3, 4, 1, 1);

        spin_scrollbar = new QScrollBar(groupBox_17);
        spin_scrollbar->setObjectName(QStringLiteral("spin_scrollbar"));
        spin_scrollbar->setMinimumSize(QSize(0, 60));
        spin_scrollbar->setStyleSheet(QLatin1String("QScrollBar\n"
            "{\n"
            "background-color:rgb(44, 62, 89)\n"
            "}"));
        spin_scrollbar->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(spin_scrollbar, 4, 1, 1, 1);

        u_d_scrollbar = new QScrollBar(groupBox_17);
        u_d_scrollbar->setObjectName(QStringLiteral("u_d_scrollbar"));
        u_d_scrollbar->setMinimumSize(QSize(0, 60));
        u_d_scrollbar->setStyleSheet(QLatin1String("QScrollBar\n"
            "{\n"
            "background-color:rgb(44, 62, 89)\n"
            "}"));
        u_d_scrollbar->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(u_d_scrollbar, 2, 1, 1, 1);

        label_2 = new QLabel(groupBox_17);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMaximumSize(QSize(120, 16777215));
        label_2->setFont(font16);
        label_2->setPixmap(QPixmap(QString::fromUtf8("Qt-bin/Debug/resources/\344\270\212\344\270\213\347\256\255\345\244\264-3.png")));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);


        verticalLayout_3->addWidget(groupBox_17);

        groupBox_20 = new QGroupBox(groupBox);
        groupBox_20->setObjectName(QStringLiteral("groupBox_20"));
        sizePolicy.setHeightForWidth(groupBox_20->sizePolicy().hasHeightForWidth());
        groupBox_20->setSizePolicy(sizePolicy);
        groupBox_20->setMaximumSize(QSize(600, 200));
        groupBox_20->setFont(font14);
        groupBox_20->setStyleSheet(QLatin1String("QGroupBox\n"
            "{\n"
            "background-color:rgb(59, 59, 59)\n"
            "}"));
        verticalLayout_14 = new QVBoxLayout(groupBox_20);
        verticalLayout_14->setSpacing(0);
        verticalLayout_14->setObjectName(QStringLiteral("verticalLayout_14"));
        verticalLayout_14->setSizeConstraint(QLayout::SetMinimumSize);
        verticalLayout_14->setContentsMargins(0, 0, 0, 0);
        groupBox_3 = new QGroupBox(groupBox_20);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setMaximumSize(QSize(16777215, 80));
        horizontalLayout = new QHBoxLayout(groupBox_3);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 0, -1, 0);
        maxWinWid = new QSlider(groupBox_3);
        maxWinWid->setObjectName(QStringLiteral("maxWinWid"));
        maxWinWid->setMinimumSize(QSize(0, 40));
        maxWinWid->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(maxWinWid);

        window_max_width = new QSpinBox(groupBox_3);
        window_max_width->setObjectName(QStringLiteral("window_max_width"));
        sizePolicy.setHeightForWidth(window_max_width->sizePolicy().hasHeightForWidth());
        window_max_width->setSizePolicy(sizePolicy);
        window_max_width->setMinimumSize(QSize(0, 50));
        window_max_width->setMaximumSize(QSize(120, 60));
        window_max_width->setFont(font8);
        window_max_width->setMinimum(-500);
        window_max_width->setMaximum(2000);

        horizontalLayout->addWidget(window_max_width);


        verticalLayout_14->addWidget(groupBox_3);

        groupBox_5 = new QGroupBox(groupBox_20);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        sizePolicy.setHeightForWidth(groupBox_5->sizePolicy().hasHeightForWidth());
        groupBox_5->setSizePolicy(sizePolicy);
        groupBox_5->setMaximumSize(QSize(16777215, 80));
        horizontalLayout_2 = new QHBoxLayout(groupBox_5);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        minWinWid = new QSlider(groupBox_5);
        minWinWid->setObjectName(QStringLiteral("minWinWid"));
        minWinWid->setMinimumSize(QSize(0, 40));
        minWinWid->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(minWinWid);

        window_min_width = new QSpinBox(groupBox_5);
        window_min_width->setObjectName(QStringLiteral("window_min_width"));
        sizePolicy.setHeightForWidth(window_min_width->sizePolicy().hasHeightForWidth());
        window_min_width->setSizePolicy(sizePolicy);
        window_min_width->setMinimumSize(QSize(0, 50));
        window_min_width->setMaximumSize(QSize(120, 60));
        window_min_width->setFont(font8);
        window_min_width->setMinimum(-500);
        window_min_width->setMaximum(2000);

        horizontalLayout_2->addWidget(window_min_width);


        verticalLayout_14->addWidget(groupBox_5);

        progressBar = new QProgressBar(groupBox_20);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        sizePolicy.setHeightForWidth(progressBar->sizePolicy().hasHeightForWidth());
        progressBar->setSizePolicy(sizePolicy);
        progressBar->setMaximumSize(QSize(16777215, 40));
        progressBar->setStyleSheet(QLatin1String("QProgressBar\n"
            "{\n"
            "background-color:rgb(80, 80, 80);\n"
            "}"));
        progressBar->setTextVisible(false);

        verticalLayout_14->addWidget(progressBar);


        verticalLayout_3->addWidget(groupBox_20);


        gridLayout_7->addWidget(groupBox, 0, 0, 1, 1);

        ProjectMainWindow->setCentralWidget(m_CentralWidget);
        menubar = new QMenuBar(ProjectMainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 2275, 35));
        QFont font17;
        font17.setFamily(QString::fromUtf8("\345\215\216\345\205\211\346\240\207\351\242\230\345\256\213_CNKI"));
        font17.setPointSize(9);
        font17.setBold(false);
        font17.setWeight(50);
        menubar->setFont(font17);
        menubar->setStyleSheet(QLatin1String("QMenuBar\n"
            "{\n"
            "  background-color:rgb(231, 231, 231)\n"
            "}"));
        m_MenuFile = new QMenu(menubar);
        m_MenuFile->setObjectName(QStringLiteral("m_MenuFile"));
        QFont font18;
        font18.setBold(true);
        font18.setWeight(75);
        m_MenuFile->setFont(font18);
        m_MenuFile->setTearOffEnabled(false);
        menuhelp = new QMenu(menubar);
        menuhelp->setObjectName(QStringLiteral("menuhelp"));
        ProjectMainWindow->setMenuBar(menubar);
        m_StatusBar = new QStatusBar(ProjectMainWindow);
        m_StatusBar->setObjectName(QStringLiteral("m_StatusBar"));
        m_StatusBar->setFont(font18);
        ProjectMainWindow->setStatusBar(m_StatusBar);

        menubar->addAction(m_MenuFile->menuAction());
        menubar->addAction(menuhelp->menuAction());
        m_MenuFile->addAction(m_OpenAction);
        m_MenuFile->addAction(actionquit);
        menuhelp->addAction(actionreadme);

        retranslateUi(ProjectMainWindow);
        QObject::connect(actionquit, SIGNAL(triggered()), ProjectMainWindow, SLOT(close()));

        clip_button->setDefault(false);
        change_button->setDefault(false);


        QMetaObject::connectSlotsByName(ProjectMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow* ProjectMainWindow)
    {
        ProjectMainWindow->setWindowTitle(QApplication::translate("ProjectMainWindow", "RSA Preoperative Planner", Q_NULLPTR));
        actionLoadImage->setText(QApplication::translate("ProjectMainWindow", "\346\211\223\345\274\200\345\233\276\345\203\217", Q_NULLPTR));
        m_OpenAction->setText(QApplication::translate("ProjectMainWindow", "import DICOM folder", Q_NULLPTR));
        actionclose->setText(QApplication::translate("ProjectMainWindow", "close", Q_NULLPTR));
        actionquit->setText(QApplication::translate("ProjectMainWindow", "quit", Q_NULLPTR));
        actionreadme->setText(QApplication::translate("ProjectMainWindow", "readme", Q_NULLPTR));
        actionrevision->setText(QApplication::translate("ProjectMainWindow", "revision ", Q_NULLPTR));
        widget->setTitle(QString());
        groupBox_11->setTitle(QString());
        groupBox_13->setTitle(QString());
        groupBox_14->setTitle(QString());
        groupBox_2->setTitle(QApplication::translate("ProjectMainWindow", "info", Q_NULLPTR));
        groupBox_12->setTitle(QString());
        groupBox_8->setTitle(QString());
        groupBox_9->setTitle(QString());
        groupBox_10->setTitle(QString());
        groupBox_7->setTitle(QString());
        checkBox_r->setText(QApplication::translate("ProjectMainWindow", "  right  ", Q_NULLPTR));
        checkBox_l->setText(QApplication::translate("ProjectMainWindow", "      left  ", Q_NULLPTR));
        groupBox_6->setTitle(QString());
        label->setText(QApplication::translate("ProjectMainWindow", " extract_value\357\274\232", Q_NULLPTR));
        threshold_lb->setText(QApplication::translate("ProjectMainWindow", "   threshold\357\274\232 ", Q_NULLPTR));
        groupBox_18->setTitle(QApplication::translate("ProjectMainWindow", "operation", Q_NULLPTR));
        groupBox_16->setTitle(QString());
        seg_button->setText(QApplication::translate("ProjectMainWindow", "segmentation", Q_NULLPTR));
        clip_button->setText(QApplication::translate("ProjectMainWindow", "clip", Q_NULLPTR));
        clip_first_on->setText(QString());
        seg_cbox->setText(QString());
        groupBox_19->setTitle(QString());
        path_button->setText(QApplication::translate("ProjectMainWindow", "path", Q_NULLPTR));
        undo_button->setText(QApplication::translate("ProjectMainWindow", "withdraw", Q_NULLPTR));
        change_button->setText(QApplication::translate("ProjectMainWindow", "change", Q_NULLPTR));
        groupBox_21->setTitle(QApplication::translate("ProjectMainWindow", "position revision", Q_NULLPTR));
        left_button->setText(QApplication::translate("ProjectMainWindow", "left", Q_NULLPTR));
        down_button->setText(QApplication::translate("ProjectMainWindow", "down", Q_NULLPTR));
        out_button->setText(QApplication::translate("ProjectMainWindow", "out", Q_NULLPTR));
        in_button->setText(QApplication::translate("ProjectMainWindow", "in", Q_NULLPTR));
        up_button->setText(QApplication::translate("ProjectMainWindow", "up", Q_NULLPTR));
        right_button->setText(QApplication::translate("ProjectMainWindow", "right", Q_NULLPTR));
        groupBox_17->setTitle(QApplication::translate("ProjectMainWindow", "angle revision", Q_NULLPTR));
        label_4->setText(QApplication::translate("ProjectMainWindow", "    spin", Q_NULLPTR));
        label_3->setText(QApplication::translate("ProjectMainWindow", "left&right", Q_NULLPTR));
        label_2->setText(QApplication::translate("ProjectMainWindow", "up&down", Q_NULLPTR));
        groupBox_20->setTitle(QString());
        groupBox_3->setTitle(QString());
        groupBox_5->setTitle(QString());
        m_MenuFile->setTitle(QApplication::translate("ProjectMainWindow", "file", Q_NULLPTR));
        menuhelp->setTitle(QApplication::translate("ProjectMainWindow", "help", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ProjectMainWindow : public Ui_ProjectMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROJECTMAINWINDOW_H
