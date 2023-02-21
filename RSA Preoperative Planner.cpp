#include "ProjectMainWindow.h"
#include <QTextCodec>
#include <vtkOutputWindow.h>
#include <itkOutputWindow.h>


//程序发布时，可以不要注释以下语句，编译的时候就不会带控制台输出窗口
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


