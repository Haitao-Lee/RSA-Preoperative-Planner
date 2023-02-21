#include <lamda.h>
#include <ProjectMainWindow.h>
#include <itkOutputWindow.h>


/****************************************************************************
  set up  ui of main interface 
****************************************************************************/
ProjectMainWindow::ProjectMainWindow()
{
	vtkOutputWindow::SetGlobalWarningDisplay(0);//不弹出vtkOutputWindow窗口
	itk::OutputWindow::SetGlobalWarningDisplay(0);;//不弹出itkOutputWindow窗口
	setupUi(this);

	QSplitter* operate_window_splitter = new QSplitter(Qt::Horizontal);//新建水平分割器
	//QSplitter* slicer_window_splitter = new QSplitter(Qt::Vertical);
	//QSplitter* all_window_splitter = new QSplitter(Qt::Horizontal);
//    mainSplitter->resize(600,300);//如果把分割器放置在layout中，那么就无需设置size

	QString style = QString("QSplitter::handle { background-color: rgb(179, 179, 179); }") //分割线的颜色
		+ QString("QSplitter {border: 1px solid green}");

	operate_window_splitter->setStyleSheet(style);
	operate_window_splitter->setHandleWidth(0);//分割线的宽度
	operate_window_splitter->setChildrenCollapsible(1);

	operate_window_splitter->addWidget(this->groupBox);
	operate_window_splitter->addWidget(this->widget_15);
	operate_window_splitter->addWidget(this->groupBox_12);
	operate_window_splitter->addWidget(this->groupBox_2);
	this->groupBox_13->layout()->replaceWidget(this->window_widget, operate_window_splitter);
	this->window_widget->hide();

	//all_window_splitter->setStyleSheet(style);
	//all_window_splitter->setHandleWidth(0);//分割线的宽度
	//all_window_splitter->setChildrenCollapsible(1);
	//all_window_splitter->addWidget(this->groupBox_14);
	//all_window_splitter->addWidget(this->groupBox_12);
	//this->groupBox_13->layout()->replaceWidget(this->window_widget, all_window_splitter);
	//this->window_widget->hide();

	//slicer_window_splitter->setStyleSheet(style);
	//slicer_window_splitter->setHandleWidth(0);//分割线的宽度
	//slicer_window_splitter->setChildrenCollapsible(1);
	//slicer_window_splitter->addWidget(this->groupBox_8);
	//slicer_window_splitter->addWidget(this->groupBox_9);
	//slicer_window_splitter->addWidget(this->groupBox_10);
	//this->groupBox_12->layout()->replaceWidget(this->slicer_widget, slicer_window_splitter);
	//this->slicer_widget->hide();

	//QPalette p = this->output_pte->palette();
	//p.setColor(QPalette::Active, QPalette::Base, Qt::white);
	//p.setColor(QPalette::Inactive, QPalette::Base, Qt::white);
	//this->output_pte->setPalette(p);

	this->undo_button->setStyleSheet(
		//正常状态样式
		"QPushButton{"
		"background-color:rgba(136,136,136,136);"//背景色（也可以设置图片）
		"border-style:outset;"                  //边框样式（inset/outset）
		"border-width:1px;"                     //边框宽度像素
		"border-radius:20px;"                   //边框圆角半径像素
		"border-color:rgba(255,255,255,30);"    //边框颜色
		"font:bold 40px;"                       //字体，字体大小
		"color:rgba(0,0,0,255);"                //字体颜色
		"padding:6px;"                          //填衬
		"border - top:1px solid rgb(237, 238, 241);"
		"border - bottom:1px solid rgb(237, 238, 241);"
		"}"
		//鼠标按下样式
		"QPushButton:pressed{"
		"background-color:rgba(100,255,100,200);"
		"border-color:rgba(255,255,255,30);"
		"border-style:inset;"
		"color:rgba(0,0,0,200);"
		"}"

		//鼠标悬停样式
		"QPushButton:hover{"
		"background-color:rgba(200,200,200,100);"
		"border-color:rgba(255,255,255,200);"
		"color:rgba(0,0,0,200);"
		"}");
	this->clip_button->setStyleSheet(
		//正常状态样式
		"QPushButton{"
		"background-color:rgba(136,136,136,136);"//背景色（也可以设置图片）
		"border-style:outset;"                  //边框样式（inset/outset）
		"border-width:1px;"                     //边框宽度像素
		"border-radius:20px;"                   //边框圆角半径像素
		"border-color:rgba(255,255,255,30);"    //边框颜色
		"font:bold 40px;"                       //字体，字体大小
		"color:rgba(0,0,0,255);"                //字体颜色
		"padding:6px;"                          //填衬
		"}"
		//鼠标按下样式
		"QPushButton:pressed{"
		"background-color:rgba(100,255,100,200);"
		"border-color:rgba(255,255,255,30);"
		"border-style:inset;"
		"color:rgba(0,0,0,200);"
		"}"

		//鼠标悬停样式
		"QPushButton:hover{"
		"background-color:rgba(200,200,200,100);"
		"border-color:rgba(255,255,255,200);"
		"color:rgba(0,0,0,200);"
		"}");
	this->seg_button->setStyleSheet(
		//正常状态样式
		"QPushButton{"
		"background-color:rgba(136,136,136,136);"//背景色（也可以设置图片）
		"border-style:outset;"                  //边框样式（inset/outset）
		"border-width:1px;"                     //边框宽度像素
		"border-radius:20px;"                   //边框圆角半径像素
		"border-color:rgba(255,255,255,30);"    //边框颜色
		"font:bold 40px;"                       //字体，字体大小
		"color:rgba(0,0,0,255);"                //字体颜色
		"padding:6px;"                          //填衬
		"}"
		//鼠标按下样式
		"QPushButton:pressed{"
		"background-color:rgba(20,20,20,0);"
		"border-color:rgba(255,255,255,30);"
		"border-style:inset;"
		"color:rgba(0,0,0,200);"
		"}"

		//鼠标悬停样式
		"QPushButton:hover{"
		"background-color:rgba(200,200,200,100);"
		"border-color:rgba(255,255,255,200);"
		"color:rgba(0,0,0,200);"
		"}");

	this->rebuild_button->setStyleSheet(
		//正常状态样式
		"QPushButton{"
		"background-color:rgba(136,136,136,136);"//背景色（也可以设置图片）
		"border-style:outset;"                  //边框样式（inset/outset）
		"border-width:1px;"                     //边框宽度像素
		"border-radius:20px;"                   //边框圆角半径像素
		"border-color:rgba(255,255,255,30);"    //边框颜色
		"font:bold 40px;"                       //字体，字体大小
		"color:rgba(0,0,0,255);"                //字体颜色
		"padding:6px;"                          //填衬
		"}"
		//鼠标按下样式
		"QPushButton:pressed{"
		"background-color:rgba(20,20,20,0);"
		"border-color:rgba(255,255,255,30);"
		"border-style:inset;"
		"color:rgba(0,0,0,200);"
		"}"

		//鼠标悬停样式
		"QPushButton:hover{"
		"background-color:rgba(200,200,200,100);"
		"border-color:rgba(255,255,255,200);"
		"color:rgba(0,0,0,200);"
		"}");

	this->change_button->setStyleSheet(
		//正常状态样式
		"QPushButton{"
		"background-color:rgba(136,136,136,136);"//背景色（也可以设置图片）
		"border-style:outset;"                  //边框样式（inset/outset）
		"border-width:1px;"                     //边框宽度像素
		"border-radius:20px;"                   //边框圆角半径像素
		"border-color:rgba(255,255,255,30);"    //边框颜色
		"font:bold 40px;"                       //字体，字体大小
		"color:rgba(0,0,0,255);"                //字体颜色
		"padding:6px;"                          //填衬
		"}"
		//鼠标按下样式
		"QPushButton:pressed{"
		"background-color:rgba(20,20,20,0);"
		"border-color:rgba(255,255,255,30);"
		"border-style:inset;"
		"color:rgba(0,0,0,200);"
		"}"

		//鼠标悬停样式
		"QPushButton:hover{"
		"background-color:rgba(200,200,200,100);"
		"border-color:rgba(255,255,255,200);"
		"color:rgba(0,0,0,200);"
		"}");
	this->path_button->setStyleSheet(
		//正常状态样式
		"QPushButton{"
		"background-color:rgba(136,136,136,136);"//背景色（也可以设置图片）
		"border-style:outset;"                  //边框样式（inset/outset）
		"border-width:1px;"                     //边框宽度像素
		"border-radius:20px;"                   //边框圆角半径像素
		"border-color:rgba(255,255,255,30);"    //边框颜色
		"font:bold 40px;"                       //字体，字体大小
		"color:rgba(0,0,0,255);"                //字体颜色
		"padding:6px;"                          //填衬
		"}"
		//鼠标按下样式
		"QPushButton:pressed{"
		"background-color:rgba(100,255,100,200);"
		"border-color:rgba(255,255,255,30);"
		"border-style:inset;"
		"color:rgba(0,0,0,200);"
		"}"

		//鼠标悬停样式
		"QPushButton:hover{"
		"background-color:rgba(200,200,200,100);"
		"border-color:rgba(255,255,255,200);"
		"color:rgba(0,0,0,200);"
		"}");
	this->in_button->setStyleSheet(
		//正常状态样式
		"QPushButton{"
		"background-color:rgba(136,136,136,136);"//背景色（也可以设置图片）
		"border-style:outset;"                  //边框样式（inset/outset）
		"border-width:1px;"                     //边框宽度像素
		"border-radius:20px;"                   //边框圆角半径像素
		"border-color:rgba(255,255,255,30);"    //边框颜色
		"font:bold 40px;"                       //字体，字体大小
		"color:rgba(0,0,0,255);"                //字体颜色
		"padding:6px;"                          //填衬
		"}"
		//鼠标按下样式
		"QPushButton:pressed{"
		"background-color:rgba(100,255,100,200);"
		"border-color:rgba(255,255,255,30);"
		"border-style:inset;"
		"color:rgba(0,0,0,200);"
		"}"

		//鼠标悬停样式
		"QPushButton:hover{"
		"background-color:rgba(200,200,200,100);"
		"border-color:rgba(255,255,255,200);"
		"color:rgba(0,0,0,200);"
		"}");
	this->out_button->setStyleSheet(
		//正常状态样式
		"QPushButton{"
		"background-color:rgba(136,136,136,136);"//背景色（也可以设置图片）
		"border-style:outset;"                  //边框样式（inset/outset）
		"border-width:1px;"                     //边框宽度像素
		"border-radius:20px;"                   //边框圆角半径像素
		"border-color:rgba(255,255,255,30);"    //边框颜色
		"font:bold 40px;"                       //字体，字体大小
		"color:rgba(0,0,0,255);"                //字体颜色
		"padding:6px;"                          //填衬
		"}"
		//鼠标按下样式
		"QPushButton:pressed{"
		"background-color:rgba(100,255,100,200);"
		"border-color:rgba(255,255,255,30);"
		"border-style:inset;"
		"color:rgba(0,0,0,200);"
		"}"

		//鼠标悬停样式
		"QPushButton:hover{"
		"background-color:rgba(200,200,200,100);"
		"border-color:rgba(255,255,255,200);"
		"color:rgba(0,0,0,200);"
		"}");
	this->up_button->setStyleSheet(
		//正常状态样式
		"QPushButton{"
		"background-color:rgba(136,136,136,136);"//背景色（也可以设置图片）
		"border-style:outset;"                  //边框样式（inset/outset）
		"border-width:1px;"                     //边框宽度像素
		"border-radius:20px;"                   //边框圆角半径像素
		"border-color:rgba(255,255,255,30);"    //边框颜色
		"font:bold 40px;"                       //字体，字体大小
		"color:rgba(0,0,0,255);"                //字体颜色
		"padding:6px;"                          //填衬
		"}"
		//鼠标按下样式
		"QPushButton:pressed{"
		"background-color:rgba(100,255,100,200);"
		"border-color:rgba(255,255,255,30);"
		"border-style:inset;"
		"color:rgba(0,0,0,200);"
		"}"

		//鼠标悬停样式
		"QPushButton:hover{"
		"background-color:rgba(200,200,200,100);"
		"border-color:rgba(255,255,255,200);"
		"color:rgba(0,0,0,200);"
		"}");
	this->down_button->setStyleSheet(
		//正常状态样式
		"QPushButton{"
		"background-color:rgba(136,136,136,136);"//背景色（也可以设置图片）
		"border-style:outset;"                  //边框样式（inset/outset）
		"border-width:1px;"                     //边框宽度像素
		"border-radius:20px;"                   //边框圆角半径像素
		"border-color:rgba(255,255,255,30);"    //边框颜色
		"font:bold 40px;"                       //字体，字体大小
		"color:rgba(0,0,0,255);"                //字体颜色
		"padding:6px;"                          //填衬
		"}"
		//鼠标按下样式
		"QPushButton:pressed{"
		"background-color:rgba(100,255,100,200);"
		"border-color:rgba(255,255,255,30);"
		"border-style:inset;"
		"color:rgba(0,0,0,200);"
		"}"

		//鼠标悬停样式
		"QPushButton:hover{"
		"background-color:rgba(200,200,200,100);"
		"border-color:rgba(255,255,255,200);"
		"color:rgba(0,0,0,200);"
		"}");
	this->left_button->setStyleSheet(
		//正常状态样式
		"QPushButton{"
		"background-color:rgba(136,136,136,136);"//背景色（也可以设置图片）
		"border-style:outset;"                  //边框样式（inset/outset）
		"border-width:1px;"                     //边框宽度像素
		"border-radius:20px;"                   //边框圆角半径像素
		"border-color:rgba(255,255,255,30);"    //边框颜色
		"font:bold 40px;"                       //字体，字体大小
		"color:rgba(0,0,0,255);"                //字体颜色
		"padding:6px;"                          //填衬
		"}"
		//鼠标按下样式
		"QPushButton:pressed{"
		"background-color:rgba(100,255,100,200);"
		"border-color:rgba(255,255,255,30);"
		"border-style:inset;"
		"color:rgba(0,0,0,200);"
		"}"

		//鼠标悬停样式
		"QPushButton:hover{"
		"background-color:rgba(200,200,200,100);"
		"border-color:rgba(255,255,255,200);"
		"color:rgba(0,0,0,200);"
		"}");
	this->right_button->setStyleSheet(
		//正常状态样式
		"QPushButton{"
		"background-color:rgba(136,136,136,136);"//背景色（也可以设置图片）
		"border-style:outset;"                  //边框样式（inset/outset）
		"border-width:1px;"                     //边框宽度像素
		"border-radius:20px;"                   //边框圆角半径像素
		"border-color:rgba(255,255,255,30);"    //边框颜色
		"font:bold 40px;"                       //字体，字体大小
		"color:rgba(0,0,0,255);"                //字体颜色
		"padding:6px;"                          //填衬
		"}"
		//鼠标按下样式
		"QPushButton:pressed{"
		"background-color:rgba(100,255,100,200);"
		"border-color:rgba(255,255,255,30);"
		"border-style:inset;"
		"color:rgba(0,0,0,200);"
		"}"

		//鼠标悬停样式
		"QPushButton:hover{"
		"background-color:rgba(200,200,200,100);"
		"border-color:rgba(255,255,255,200);"
		"color:rgba(0,0,0,200);"
		"}");

	this->screw1_up_btn->setStyleSheet(
		//正常状态样式
		"QPushButton{"
		"background-color:rgba(136,136,136,136);"//背景色（也可以设置图片）
		"border-style:outset;"                  //边框样式（inset/outset）
		"border-width:1px;"                     //边框宽度像素
		"border-radius:20px;"                   //边框圆角半径像素
		"border-color:rgba(255,255,255,30);"    //边框颜色
		"font:bold 40px;"                       //字体，字体大小
		"color:rgba(0,0,0,255);"                //字体颜色
		"padding:6px;"                          //填衬
		"}"
		//鼠标按下样式
		"QPushButton:pressed{"
		"background-color:rgba(100,255,100,200);"
		"border-color:rgba(255,255,255,30);"
		"border-style:inset;"
		"color:rgba(0,0,0,200);"
		"}"

		//鼠标悬停样式
		"QPushButton:hover{"
		"background-color:rgba(200,200,200,100);"
		"border-color:rgba(255,255,255,200);"
		"color:rgba(0,0,0,200);"
		"}");

	this->screw1_down_btn->setStyleSheet(
		//正常状态样式
		"QPushButton{"
		"background-color:rgba(136,136,136,136);"//背景色（也可以设置图片）
		"border-style:outset;"                  //边框样式（inset/outset）
		"border-width:1px;"                     //边框宽度像素
		"border-radius:20px;"                   //边框圆角半径像素
		"border-color:rgba(255,255,255,30);"    //边框颜色
		"font:bold 40px;"                       //字体，字体大小
		"color:rgba(0,0,0,255);"                //字体颜色
		"padding:6px;"                          //填衬
		"}"
		//鼠标按下样式
		"QPushButton:pressed{"
		"background-color:rgba(100,255,100,200);"
		"border-color:rgba(255,255,255,30);"
		"border-style:inset;"
		"color:rgba(0,0,0,200);"
		"}"

		//鼠标悬停样式
		"QPushButton:hover{"
		"background-color:rgba(200,200,200,100);"
		"border-color:rgba(255,255,255,200);"
		"color:rgba(0,0,0,200);"
		"}");

	this->screw1_left_btn->setStyleSheet(
		//正常状态样式
		"QPushButton{"
		"background-color:rgba(136,136,136,136);"//背景色（也可以设置图片）
		"border-style:outset;"                  //边框样式（inset/outset）
		"border-width:1px;"                     //边框宽度像素
		"border-radius:20px;"                   //边框圆角半径像素
		"border-color:rgba(255,255,255,30);"    //边框颜色
		"font:bold 40px;"                       //字体，字体大小
		"color:rgba(0,0,0,255);"                //字体颜色
		"padding:6px;"                          //填衬
		"}"
		//鼠标按下样式
		"QPushButton:pressed{"
		"background-color:rgba(100,255,100,200);"
		"border-color:rgba(255,255,255,30);"
		"border-style:inset;"
		"color:rgba(0,0,0,200);"
		"}"

		//鼠标悬停样式
		"QPushButton:hover{"
		"background-color:rgba(200,200,200,100);"
		"border-color:rgba(255,255,255,200);"
		"color:rgba(0,0,0,200);"
		"}");

	this->screw1_right_btn->setStyleSheet(
		//正常状态样式
		"QPushButton{"
		"background-color:rgba(136,136,136,136);"//背景色（也可以设置图片）
		"border-style:outset;"                  //边框样式（inset/outset）
		"border-width:1px;"                     //边框宽度像素
		"border-radius:20px;"                   //边框圆角半径像素
		"border-color:rgba(255,255,255,30);"    //边框颜色
		"font:bold 40px;"                       //字体，字体大小
		"color:rgba(0,0,0,255);"                //字体颜色
		"padding:6px;"                          //填衬
		"}"
		//鼠标按下样式
		"QPushButton:pressed{"
		"background-color:rgba(100,255,100,200);"
		"border-color:rgba(255,255,255,30);"
		"border-style:inset;"
		"color:rgba(0,0,0,200);"
		"}"

		//鼠标悬停样式
		"QPushButton:hover{"
		"background-color:rgba(200,200,200,100);"
		"border-color:rgba(255,255,255,200);"
		"color:rgba(0,0,0,200);"
		"}");

	this->screw1_update->setStyleSheet(
		//正常状态样式
		"QPushButton{"
		"background-color:rgba(136,136,136,136);"//背景色（也可以设置图片）
		"border-style:outset;"                  //边框样式（inset/outset）
		"border-width:1px;"                     //边框宽度像素
		"border-radius:20px;"                   //边框圆角半径像素
		"border-color:rgba(255,255,255,30);"    //边框颜色
		"font:bold 40px;"                       //字体，字体大小
		"color:rgba(0,0,0,255);"                //字体颜色
		"padding:6px;"                          //填衬
		"}"
		//鼠标按下样式
		"QPushButton:pressed{"
		"background-color:rgba(100,255,100,200);"
		"border-color:rgba(255,255,255,30);"
		"border-style:inset;"
		"color:rgba(0,0,0,200);"
		"}"

		//鼠标悬停样式
		"QPushButton:hover{"
		"background-color:rgba(200,200,200,100);"
		"border-color:rgba(255,255,255,200);"
		"color:rgba(0,0,0,200);"
		"}");

	this->screw2_up_btn->setStyleSheet(
		//正常状态样式
		"QPushButton{"
		"background-color:rgba(136,136,136,136);"//背景色（也可以设置图片）
		"border-style:outset;"                  //边框样式（inset/outset）
		"border-width:1px;"                     //边框宽度像素
		"border-radius:20px;"                   //边框圆角半径像素
		"border-color:rgba(255,255,255,30);"    //边框颜色
		"font:bold 40px;"                       //字体，字体大小
		"color:rgba(0,0,0,255);"                //字体颜色
		"padding:6px;"                          //填衬
		"}"
		//鼠标按下样式
		"QPushButton:pressed{"
		"background-color:rgba(100,255,100,200);"
		"border-color:rgba(255,255,255,30);"
		"border-style:inset;"
		"color:rgba(0,0,0,200);"
		"}"

		//鼠标悬停样式
		"QPushButton:hover{"
		"background-color:rgba(200,200,200,100);"
		"border-color:rgba(255,255,255,200);"
		"color:rgba(0,0,0,200);"
		"}");


	this->screw2_down_btn->setStyleSheet(
		//正常状态样式
		"QPushButton{"
		"background-color:rgba(136,136,136,136);"//背景色（也可以设置图片）
		"border-style:outset;"                  //边框样式（inset/outset）
		"border-width:1px;"                     //边框宽度像素
		"border-radius:20px;"                   //边框圆角半径像素
		"border-color:rgba(255,255,255,30);"    //边框颜色
		"font:bold 40px;"                       //字体，字体大小
		"color:rgba(0,0,0,255);"                //字体颜色
		"padding:6px;"                          //填衬
		"}"
		//鼠标按下样式
		"QPushButton:pressed{"
		"background-color:rgba(180,180,180,100);"
		"border-color:rgba(255,255,255,30);"
		"border-style:inset;"
		"color:rgba(0,0,0,200);"
		"}"

		//鼠标悬停样式
		"QPushButton:hover{"
		"background-color:rgba(200,200,200,100);"
		"border-color:rgba(255,255,255,200);"
		"color:rgba(0,0,0,200);"
		"}");

	this->screw2_left_btn->setStyleSheet(
		//正常状态样式
		"QPushButton{"
		"background-color:rgba(136,136,136,136);"//背景色（也可以设置图片）
		"border-style:outset;"                  //边框样式（inset/outset）
		"border-width:1px;"                     //边框宽度像素
		"border-radius:20px;"                   //边框圆角半径像素
		"border-color:rgba(255,255,255,30);"    //边框颜色
		"font:bold 40px;"                       //字体，字体大小
		"color:rgba(0,0,0,255);"                //字体颜色
		"padding:6px;"                          //填衬
		"}"
		//鼠标按下样式
		"QPushButton:pressed{"
		"background-color:rgba(100,255,100,200);"
		"border-color:rgba(255,255,255,30);"
		"border-style:inset;"
		"color:rgba(0,0,0,200);"
		"}"

		//鼠标悬停样式
		"QPushButton:hover{"
		"background-color:rgba(200,200,200,100);"
		"border-color:rgba(255,255,255,200);"
		"color:rgba(0,0,0,200);"
		"}");

	this->screw2_right_btn->setStyleSheet(
		//正常状态样式
		"QPushButton{"
		"background-color:rgba(136,136,136,136);"//背景色（也可以设置图片）
		"border-style:outset;"                  //边框样式（inset/outset）
		"border-width:1px;"                     //边框宽度像素
		"border-radius:20px;"                   //边框圆角半径像素
		"border-color:rgba(255,255,255,30);"    //边框颜色
		"font:bold 40px;"                       //字体，字体大小
		"color:rgba(0,0,0,255);"                //字体颜色
		"padding:6px;"                          //填衬
		"}"
		//鼠标按下样式
		"QPushButton:pressed{"
		"background-color:rgba(100,255,100,200);"
		"border-color:rgba(255,255,255,30);"
		"border-style:inset;"
		"color:rgba(0,0,0,200);"
		"}"

		//鼠标悬停样式
		"QPushButton:hover{"
		"background-color:rgba(200,200,200,100);"
		"border-color:rgba(255,255,255,200);"
		"color:rgba(0,0,0,200);"
		"}");

	this->screw2_update->setStyleSheet(
		//正常状态样式
		"QPushButton{"
		"background-color:rgba(136,136,136,136);"//背景色（也可以设置图片）
		"border-style:outset;"                  //边框样式（inset/outset）
		"border-width:1px;"                     //边框宽度像素
		"border-radius:20px;"                   //边框圆角半径像素
		"border-color:rgba(255,255,255,30);"    //边框颜色
		"font:bold 40px;"                       //字体，字体大小
		"color:rgba(0,0,0,255);"                //字体颜色
		"padding:6px;"                          //填衬
		"}"
		//鼠标按下样式
		"QPushButton:pressed{"
		"background-color:rgba(100,255,100,200);"
		"border-color:rgba(255,255,255,30);"
		"border-style:inset;"
		"color:rgba(0,0,0,200);"
		"}"

		//鼠标悬停样式
		"QPushButton:hover{"
		"background-color:rgba(200,200,200,100);"
		"border-color:rgba(255,255,255,200);"
		"color:rgba(0,0,0,200);"
		"}");




	//this->groupBox->setStyleSheet(QObject::tr("#groupBox{border: 0px solid;}"));
	//this->groupBox_2->setStyleSheet(QObject::tr("#groupBox{border: 0px solid;}"));
	//this->groupBox_3->setStyleSheet(QObject::tr("#groupBox{border: 0px solid;}"));
	//this->groupBox_5->setStyleSheet(QObject::tr("#groupBox{border: 0px solid;}"));
	//this->groupBox_6->setStyleSheet(QObject::tr("#groupBox{border: 0px solid;}"));
	//this->groupBox_7->setStyleSheet(QObject::tr("#groupBox{border: 0px solid;}"));
	//this->groupBox_8->setStyleSheet(QObject::tr("#groupBox{border: 0px solid;}"));
	//this->groupBox_9->setStyleSheet(QObject::tr("#groupBox{border: 0px solid;}"));
	//this->groupBox_10->setStyleSheet(QObject::tr("#groupBox{border: 0px solid;}"));
	//this->groupBox_11->setStyleSheet(QObject::tr("#groupBox{border: 0px solid;}"));
	//this->groupBox_12->setStyleSheet(QObject::tr("#groupBox{border: 0px solid;}"));
	//this->groupBox_13->setStyleSheet(QObject::tr("#groupBox{border: 0px solid;}"));
	//this->groupBox_14->setStyleSheet(QObject::tr("#groupBox{border: 0px solid;}"));
	//this->groupBox_15->setStyleSheet(QObject::tr("#groupBox{border: 0px solid;}"));
	//this->groupBox_16->setStyleSheet(QObject::tr("#groupBox{border: 0px solid;}"));
	//this->groupBox_17->setStyleSheet(QObject::tr("#groupBox{border: 0px solid;}"));
	//this->groupBox_18->setStyleSheet(QObject::tr("#groupBox{border: 0px solid;}"));
	//this->groupBox_19->setStyleSheet(QObject::tr("#groupBox{border: 0px solid;}"));
	//this->groupBox_20->setStyleSheet(QObject::tr("#groupBox{border: 0px solid;}"));
	//this->groupBox_21->setStyleSheet(QObject::tr("#groupBox{border: 0px solid;}"));
	//this->groupBox_22->setStyleSheet(QObject::tr("#groupBox{border: 0px solid;}"));
	//this->groupBox_23->setStyleSheet(QObject::tr("#groupBox{border: 0px solid;}"));
	//this->groupBox_24->setStyleSheet(QObject::tr("#groupBox{border: 0px solid;}"));
	//this->groupBox_25->setStyleSheet(QObject::tr("#groupBox{border: 0px solid;}"));

	
	this->rebuild_button->setEnabled(0);
	this->path_button->setEnabled(0);
	this->seg_button->setEnabled(0);
	this->undo_button->setEnabled(0);
	this->threshold1_sb->setRange(0, 255);
	this->threshold2_sb->setRange(0, 255);
	this->marchingCubes_sb->setRange(0, 2000);
	this->marchingCubes_sb->setValue(200);
	this->progressBar->setValue(0);
	this->progressBar->setRange(0, 10000);
	this->clip_first_on->setEnabled(true);

	//this->checkBox_r->setChecked(true);
	//this->checkBox_l->setChecked(false);
	this->opacity_slider->setSingleStep(1);
	this->opacity_slider->setTracking(1);
	this->opacity_slider->setEnabled(false);
	this->horizontalSlider_1->setSingleStep(1);
	this->horizontalSlider_1->setTracking(1);
	//this->horizontalSlider_1->setTickPosition(QSlider::TicksBothSides);
	this->horizontalSlider_1->setRange(0, 100);
	this->horizontalSlider_1->setValue(0);
	this->curSlice1 = 50;
	this->horizontalSlider_1->setEnabled(0);

	this->horizontalSlider_2->setSingleStep(1);
	this->horizontalSlider_2->setTracking(1);
	//this->horizontalSlider_2->setTickPosition(QSlider::TicksBothSides);
	this->horizontalSlider_2->setRange(0, 100);
	this->horizontalSlider_2->setValue(0);
	this->curSlice2 = 50;
	this->horizontalSlider_2->setEnabled(0);

	this->horizontalSlider_3->setSingleStep(1);
	this->horizontalSlider_3->setTracking(1);
	//this->horizontalSlider_3->setTickPosition(QSlider::TicksBothSides);
	this->horizontalSlider_3->setRange(0, 100);
	this->horizontalSlider_3->setValue(0);
	this->curSlice3 = 50;
	this->horizontalSlider_3->setEnabled(0);

	this->minWinWid->setRange(-999, 2000);
	this->minWinWid->setValue(-100);
	this->maxWinWid->setRange(-999, 2000);
	this->maxWinWid->setValue(500);
	this->window_min_width->setRange(-999, 2000);
	this->window_min_width->setValue(-100);
	this->window_max_width->setRange(-999, 2000);
	this->window_max_width->setValue(500);

	this->m_style = vtkSmartPointer<PickerInteractorStyle>::New();

	this->m_style->colorTable = vtkSmartPointer<vtkLookupTable>::New();
	this->m_style->colorTable->SetRange(-100, 500);
	this->m_style->colorTable->SetValueRange(0.0, 1.0);
	this->m_style->colorTable->SetSaturationRange(0.0, 0.0);
	this->m_style->colorTable->SetRampToLinear();
	this->m_style->colorTable->Build();
	//this->menuexport->setEnabled(0);

	this->path1_widget->setEnabled(0);
	this->path3_widget->setEnabled(0);


	this->m_pRenderer = vtkSmartPointer<vtkRenderer>::New();
	this->m_rWindow = vtkSmartPointer<vtkRenderWindow>::New();
	this->m_pRenderer1 = vtkSmartPointer<vtkRenderer>::New();
	this->m_rWindow1 = vtkSmartPointer<vtkRenderWindow>::New();
	this->m_pRenderer2 = vtkSmartPointer<vtkRenderer>::New();
	this->m_rWindow2 = vtkSmartPointer<vtkRenderWindow>::New();
	this->m_pRenderer3 = vtkSmartPointer<vtkRenderer>::New();
	this->axesWidget = vtkSmartPointer<vtkOrientationMarkerWidget>::New();
	this->textWidget = vtkSmartPointer<vtkTextWidget>::New();
	this->m_rWindow3 = vtkSmartPointer<vtkRenderWindow>::New();
	this->m_style->callback1 = vtkSmartPointer< vtkImageInteractionCallback>::New();
	this->m_style->callback2 = vtkSmartPointer< vtkImageInteractionCallback>::New();
	this->m_style->callback3 = vtkSmartPointer< vtkImageInteractionCallback>::New();

	// 设置m_QVTKWidget的渲染器
	this->operate_window->GetRenderWindow()->AddRenderer(this->m_pRenderer);
	this->qvtkWidget_1->GetRenderWindow()->AddRenderer(this->m_pRenderer1);
	this->qvtkWidget_2->GetRenderWindow()->AddRenderer(this->m_pRenderer2);
	this->qvtkWidget_3->GetRenderWindow()->AddRenderer(this->m_pRenderer3);

	//连接打开的信号与相应的槽
	connect(m_OpenAction, SIGNAL(triggered()), this, SLOT(onOpenSlot()));

	connect(actionreadme, SIGNAL(triggered()), this, SLOT(onReadmeDialog()));

	connect(action_obj, SIGNAL(triggered()), this, SLOT(onSaveOBJDialog()));

	connect(actionresult, SIGNAL(triggered()), this, SLOT(onSaveTXTDialog()));

	//connect(actionrevision, SIGNAL(triggered()), this, SLOT(onRevisionDialog()));

	m_Connections = vtkEventQtSlotConnect::New();
	m_Connections->Connect(operate_window->GetRenderWindow()->GetInteractor(),
		vtkCommand::MouseMoveEvent,
		this,
		SLOT(updateCoords(vtkObject*)));
	m_Connections->Connect(qvtkWidget_1->GetRenderWindow()->GetInteractor(),
		vtkCommand::MouseMoveEvent,
		this,
		SLOT(updateCoords(vtkObject*)));
	m_Connections->Connect(qvtkWidget_2->GetRenderWindow()->GetInteractor(),
		vtkCommand::MouseMoveEvent,
		this,
		SLOT(updateCoords(vtkObject*)));
	m_Connections->Connect(qvtkWidget_2->GetRenderWindow()->GetInteractor(),
		vtkCommand::MouseMoveEvent,
		this,
		SLOT(updateCoords(vtkObject*)));

	connect(this->undo_button, SIGNAL(clicked()), this, SLOT(undoLastOperation()));

	connect(this->clip_first_on, SIGNAL(clicked()), this, SLOT(clipOrNot()));

	connect(this->clip_button, SIGNAL(clicked()), this, SLOT(clip()));

	connect(this->change_button, SIGNAL(clicked()), this, SLOT(changeClippingArea()));

	connect(this->threshold1_sb, SIGNAL(valueChanged(int)), this, SLOT(changeThreshold()));

	connect(this->threshold2_sb, SIGNAL(valueChanged(int)), this, SLOT(changeThreshold()));

	connect(this->output_pte, SIGNAL(customContextMenuRequested()), this, SLOT(on_plainTextEdit_customContextMenuRequested(const QPoint & pos)));

	connect(this->path_button, SIGNAL(clicked()), this, SLOT(path_display()));

	connect(this->seg_cbox, SIGNAL(clicked()), this, SLOT(connect_first()));

	connect(this->seg_button, SIGNAL(clicked()), this, SLOT(segment()));

	/*connect(this->checkBox_r, SIGNAL(clicked()), this, SLOT(leftOrRight()));

	connect(this->checkBox_l, SIGNAL(clicked()), this, SLOT(rightOrLeft()));*/

	//connect(this->opacity_slider, SIGNAL(valueChanged(int)), this, SLOT(this->ajustOpacity()));

	connect(this->opacity_slider, &QSlider::valueChanged, this, &ProjectMainWindow::ajustOpacity);

	connect(this->minWinWid, &QSlider::valueChanged, this, &ProjectMainWindow::min_slider_window_syn);

	connect(this->maxWinWid, &QSlider::valueChanged, this, &ProjectMainWindow::max_slider_window_syn);

	connect(this->window_min_width, SIGNAL(valueChanged(int)), this, SLOT(min_box_window_syn()));

	connect(this->window_max_width, SIGNAL(valueChanged(int)), this, SLOT(max_box_window_syn()));

	connect(this->horizontalSlider_1, &QSlider::valueChanged, this, &ProjectMainWindow::setSlice1);

	connect(this->horizontalSlider_2, &QSlider::valueChanged, this, &ProjectMainWindow::setSlice2);

	connect(this->horizontalSlider_3, &QSlider::valueChanged, this, &ProjectMainWindow::setSlice3);

	connect(this->in_button, SIGNAL(clicked()), this, SLOT(in_revision()));

	connect(this->out_button, SIGNAL(clicked()), this, SLOT(out_revision()));

	connect(this->up_button, SIGNAL(clicked()), this, SLOT(up_revision()));

	connect(this->down_button, SIGNAL(clicked()), this, SLOT(down_revision()));

	connect(this->left_button, SIGNAL(clicked()), this, SLOT(left_revision()));

	connect(this->right_button, SIGNAL(clicked()), this, SLOT(right_revision()));

	connect(this->u_d_scrollbar, &QSlider::valueChanged, this, &ProjectMainWindow::u_d_revision);

	connect(this->l_r_scrollbar, &QSlider::valueChanged, this, &ProjectMainWindow::l_r_revision);

	connect(this->spin_scrollbar, &QSlider::valueChanged, this, &ProjectMainWindow::spin_revision);

	connect(this->u_d_box, SIGNAL(valueChanged(int)), this, SLOT(u_d_syn()));

	connect(this->l_r_box, SIGNAL(valueChanged(int)), this, SLOT(l_r_syn()));

	connect(this->spin_box, SIGNAL(valueChanged(int)), this, SLOT(spin_syn()));

	connect(this->rebuild_button, SIGNAL(clicked()), this, SLOT(onRebuildDialog()));

	connect(this->marchingCubes_sb, SIGNAL(valueChanged(int)), this, SLOT(change_iso_value()));

	connect(this->screw1_up_btn, SIGNAL(clicked()), this, SLOT(up_revision1()));

	connect(this->screw1_down_btn, SIGNAL(clicked()), this, SLOT(down_revision1()));

	connect(this->screw1_left_btn, SIGNAL(clicked()), this, SLOT(left_revision1()));

	connect(this->screw1_right_btn, SIGNAL(clicked()), this, SLOT(right_revision1()));

	connect(this->screw2_up_btn, SIGNAL(clicked()), this, SLOT(up_revision2()));

	connect(this->screw2_down_btn, SIGNAL(clicked()), this, SLOT(down_revision2()));

	connect(this->screw2_left_btn, SIGNAL(clicked()), this, SLOT(left_revision2()));

	connect(this->screw2_right_btn, SIGNAL(clicked()), this, SLOT(right_revision2()));

	connect(this->screw1_update, SIGNAL(clicked()), this, SLOT(update()));

	connect(this->screw2_update, SIGNAL(clicked()), this, SLOT(update()));
}

ProjectMainWindow::~ProjectMainWindow()
{
	//m_myThread.m_bStart = false;
	//m_myThread.wait();
	delete this;
}




