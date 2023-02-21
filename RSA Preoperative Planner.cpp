#include "ProjectMainWindow.h"
#include <QTextCodec>
#include <vtkOutputWindow.h>
#include <itkOutputWindow.h>


//���򷢲�ʱ�����Բ�Ҫע��������䣬�����ʱ��Ͳ��������̨�������
#pragma comment( linker, "/subsystem:windows /entry:mainCRTStartup" )

int main( int argc , char *argv[] ) 
{
	QApplication app(argc, argv);
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));

	ProjectMainWindow *window = new ProjectMainWindow();
	//window->setWindowFlags(Qt::FramelessWindowHint);

	window->show();
	return app.exec();
};


