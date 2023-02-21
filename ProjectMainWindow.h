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


	//响应打开图像文件的槽函数
	void onOpenSlot();
	void lamda_onOpenSlot();

	//响应鼠标移动的消息，实时输出鼠标的当前位置
	void updateCoords(vtkObject* obj);

	//判断是否撤回
	void undoLastOperation();
	void lamda_undoLastOperation();


	//判断是否需要先裁切
	void clipOrNot();
	void lamda_clipOrNot();

	//裁切
	void clip();
	void lamda_clip();

	//改变裁剪的区域
	void changeClippingArea();
	void lamda_changeClippingArea();

	//改变判断植入钉是否露出的阈值
	void  changeThreshold();
	void  lamda_changeThreshold();

	//输出框的快捷菜单
	void on_plainTextEdit_customContextMenuRequested(const QPoint& pos);
	void lamda_on_plainTextEdit_customContextMenuRequested(const QPoint& pos);

	//输出最终路径
	void path_display();
	void lamda_path_display();

	//更新进度条
	//void update_progress(int nNum);

	//打开说明窗口
	void onReadmeDialog();
	void lamda_onReadmeDialog();

	//打开微调中心
	void onRevisionDialog();
	void lamda_onRevisionDialog();

	//勾选连通分析
	void connect_first();
	void lamda_connect_first();

	//保留所需连通域
	void segment();
	void lamda_segment();

	////改变左右肩
	//void rightOrLeft();
	//void lamda_rightOrLeft();
	//void leftOrRight();
	//void lamda_leftOrRight();


	//改变透明度
	void ajustOpacity();
	void lamda_ajustOpacity();

	//改变等值面提取值
	void change_iso_value();
	void lamda_change_iso_value();


	//滑块同步窗宽窗位调节
	void min_slider_window_syn();
	void lamda_min_slider_window_syn();
	void min_box_window_syn();
	void lamda_min_box_window_syn();
	void max_slider_window_syn();
	void lamda_max_slider_window_syn();
	void max_box_window_syn();
	void lamda_max_box_window_syn();

	//设置切片位置
	void setSlice1();
	void lamda_setSlice1();
	void setSlice2();
	void lamda_setSlice2();
	void setSlice3();
	void lamda_setSlice3();

	//假体基座平移自由度
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


	//假体基座旋转自由度
	void l_r_revision();
	void lamda_l_r_revision();
	void u_d_revision();
	void lamda_u_d_revision();
	void spin_revision();
	void lamda_spin_revision();

	//螺钉通道1调整
	void up_revision1();
	void down_revision1();
	void left_revision1();
	void right_revision1();

	//螺钉通道2调整
	void up_revision2();
	void down_revision2();
	void left_revision2();
	void right_revision2();

	//更新螺钉调整后的坐标、密度数值
	void update();

	//旋转同步
	void l_r_syn();
	void lamda_l_r_syn();
	void u_d_syn();
	void lamda_u_d_syn();
	void spin_syn();
	void lamda_spin_syn();


	//打开重建窗口
	void onRebuildDialog();
	void lamda_onRebuildDialog();

	//打开保存stl的窗口
	void onSaveOBJDialog();
	void lamda_onSaveOBJDialog();

	//打开保存txt的窗口
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
