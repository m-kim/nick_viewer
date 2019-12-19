#include <QApplication>
#include <GL/glut.h>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include "SculptorWindow.h"
#include "DriverBH.h"

#include <iostream>

using std::cout;
using std::endl;

DriverBH *drv;

// entry point
int main(int argc,	char* argv[])
{

    drv = new DriverBH();

	QApplication a(argc, argv);
	glutInit(&argc,argv);
    SculptorWindow *window = new SculptorWindow(drv);

    window->show();
	return a.exec();
}
