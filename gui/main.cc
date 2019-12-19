#include <QApplication>
#include "SculptorWindow.h"

#include <iostream>

using std::cout;
using std::endl;


// entry point
int main(int argc,	char* argv[])
{


	QApplication a(argc, argv);
    SculptorWindow *window = new SculptorWindow();

    window->show();
	return a.exec();
}
