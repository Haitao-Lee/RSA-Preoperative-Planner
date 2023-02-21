#ifndef Project_MainWindow_H
#define Project_MainWindow_H

#include <QMainWindow>
#include "RSA Preoperative Planner-bin\ui_RSA Preoperative Planner.h"
#include <vtkSmartPointer.h>
#include <QtWidgets/QApplication>
#include <QApplication>
#include <QMainWindow>
#include <vtkAutoInit.h>
#include <iostream>
#include <vtkOrientationMarkerWidget.h>
#include <qdialog.h>	 
#include "PointPickerInteractorStyle.h"
#include <qapplication.h>
#include <qfuture.h>
#include <QtConcurrent/qtconcurrentrun.h>


class vtkImageViewer2;
class vtkRenderer;
class vtkEventQtSlotConnect;
class vtkObject;
class vtkCommand;

 



class ProjectMainWindow : public QMainWindow, public Ui::ProjectMainWindow
{
	Q_OBJECT;

public:
	//myThread m_myThread;
	ProjectMainWindow();
	~ProjectMainWindow();
	void progressBegin();
	void progressMiddle();
	void progressEnd();

public slots:


	//��Ӧ��ͼ���ļ��Ĳۺ���
	void onOpenSlot();
	void lamda_onOpenSlot();

	//��Ӧ����ƶ�����Ϣ��ʵʱ������ĵ�ǰλ��
	void updateCoords(vtkObject* obj);

	//�ж��Ƿ񳷻�
	void undoLastOperation();
	void lamda_undoLastOperation();


	//�ж��Ƿ���Ҫ�Ȳ���
	void clipOrNot();
	void lamda_clipOrNot();

	//����
	void clip();
	void lamda_clip();

	//�ı�ü�������
	void changeClippingArea();
	void lamda_changeClippingArea();

	//�ı��ж�ֲ�붤�Ƿ�¶������ֵ
	void  changeThreshold();
	void  lamda_changeThreshold();

	//�����Ŀ�ݲ˵�
	void on_plainTextEdit_customContextMenuRequested(const QPoint& pos);
	void lamda_on_plainTextEdit_customContextMenuRequested(const QPoint& pos);

	//�������·��
	void path_display();
	void lamda_path_display();

	//���½�����
	//void update_progress(int nNum);

	//��˵������
	void onReadmeDialog();
	void lamda_onReadmeDialog();

	//��΢������
	void onRevisionDialog();
	void lamda_onRevisionDialog();

	//��ѡ��ͨ����
	void connect_first();
	void lamda_connect_first();

	//����������ͨ��
	void segment();
	void lamda_segment();

	////�ı����Ҽ�
	//void rightOrLeft();
	//void lamda_rightOrLeft();
	//void leftOrRight();
	//void lamda_leftOrRight();


	//�ı�͸����
	void ajustOpacity();
	void lamda_ajustOpacity();

	//�ı��ֵ����ȡֵ
	void change_iso_value();
	void lamda_change_iso_value();


	//����ͬ������λ����
	void min_slider_window_syn();
	void lamda_min_slider_window_syn();
	void min_box_window_syn();
	void lamda_min_box_window_syn();
	void max_slider_window_syn();
	void lamda_max_slider_window_syn();
	void max_box_window_syn();
	void lamda_max_box_window_syn();

	//������Ƭλ��
	void setSlice1();
	void lamda_setSlice1();
	void setSlice2();
	void lamda_setSlice2();
	void setSlice3();
	void lamda_setSlice3();

	//�������ƽ�����ɶ�
	void in_revision();
	void lamda_in_revision();
	void out_revision();
	void lamda_out_revision();
	void up_revision();
	void lamda_up_revision();
	void down_revision();
	void lamda_down_revision();
	void left_revision();
	void lamda_left_revision();
	void right_revision();
	void lamda_right_revision();


	//���������ת���ɶ�
	void l_r_revision();
	void lamda_l_r_revision();
	void u_d_revision();
	void lamda_u_d_revision();
	void spin_revision();
	void lamda_spin_revision();

	//�ݶ�ͨ��1����
	void up_revision1();
	void down_revision1();
	void left_revision1();
	void right_revision1();

	//�ݶ�ͨ��2����
	void up_revision2();
	void down_revision2();
	void left_revision2();
	void right_revision2();

	//�����ݶ�����������ꡢ�ܶ���ֵ
	void update();

	//��תͬ��
	void l_r_syn();
	void lamda_l_r_syn();
	void u_d_syn();
	void lamda_u_d_syn();
	void spin_syn();
	void lamda_spin_syn();


	//���ؽ�����
	void onRebuildDialog();
	void lamda_onRebuildDialog();

	//�򿪱���stl�Ĵ���
	void onSaveOBJDialog();
	void lamda_onSaveOBJDialog();

	//�򿪱���txt�Ĵ���
	void onSaveTXTDialog();
	void lamda_onSaveTXTDialog();


private:
	vtkSmartPointer<vtkImageViewer2>            m_pImageViewer;
	vtkSmartPointer<vtkRenderer>                m_pRenderer;
	vtkSmartPointer<vtkRenderer>                m_pRenderer1;
	vtkSmartPointer<vtkRenderer>                m_pRenderer2;
	vtkSmartPointer<vtkRenderer>                m_pRenderer3;
	vtkSmartPointer<vtkRenderWindow>            m_rWindow;
	vtkSmartPointer<vtkRenderWindow>            m_rWindow1;
	vtkSmartPointer<vtkRenderWindow>            m_rWindow2;
	vtkSmartPointer<vtkRenderWindow>            m_rWindow3;
	vtkSmartPointer<PickerInteractorStyle>      m_style;
	vtkSmartPointer<vtkOrientationMarkerWidget> axesWidget;
	vtkSmartPointer<vtkTextWidget>              textWidget;
	vtkEventQtSlotConnect*                      m_Connections;
	/*vtkSmartPointer<vtkImageInteractionCallback> callback1;
	vtkSmartPointer<vtkImageInteractionCallback> callback2;
	vtkSmartPointer<vtkImageInteractionCallback> callback3;
	vtkSmartPointer<vtkLookupTable>  colorTable;*/
	//vtkSmartPointer<vtkImageInteractionCallback> slice;
	
	double maxHu1;
	double maxHu2;
	double optimalHu1;
	double optimalHu2;
	int curSlice1;
	int curSlice2;
	int curSlice3;

};

#endif
