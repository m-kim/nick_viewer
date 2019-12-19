#include <QtGui>
#include "SculptorWidget.h"
#include <QtOpenGL/QGLWidget>
#include "SculptorWindow.h"
#include <iostream>

using namespace std;
SculptorWindow::SculptorWindow(DriverBH *d)
{
	ui = new Ui::MainWindow();
	ui->setupUi(this);
	currentGlWidget = new SculptorWidget();
    currentGlWidget->drv = d;
	currentGlWidget->makeCurrent();
	glewInit();
	setCentralWidget(currentGlWidget);
    setWindowTitle(tr("Sculptor"));

    currentGlWidget->setBackgroundColor(57/255., 124/255., 75/255.);
    connectActions();
}

void SculptorWindow::connectActions()
{
	connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(about()));
	connect(ui->actionBackground, SIGNAL(triggered()), this, SLOT(background()));
	connect(ui->actionVolume, SIGNAL(triggered()), this, SLOT(volume()));
    connect(ui->verticalSlider, SIGNAL(valueChanged(int)), this, SLOT(setVisibleLevel(int)));
    connect(ui->btnSaveImg, SIGNAL(clicked()), currentGlWidget, SLOT(savePng()));
    connect(ui->checkBox, SIGNAL(stateChanged(int)), this, SLOT(setLeafVisible(int)));

}

void SculptorWindow::keyPressEvent( QKeyEvent *e )
{
	switch(e->key()){
    case Qt::Key_Escape:
        delete currentGlWidget;
    	close();
    	break;
    default:
    	currentGlWidget->keyPressEvent(e);
	}
}


void SculptorWindow::about()
{
    QMessageBox::about(this, tr("About Sculptor"),
        tr("The <b>Sculptor</b>."));
}

void SculptorWindow::background()
{
	QColor cur_color = currentGlWidget->getBackgroundColor();
	QColor col = QColorDialog::getColor(cur_color);
	currentGlWidget->setBackgroundColor(col.redF(), col.greenF(), col.blueF());
}
void SculptorWindow::mousePressEvent(QMouseEvent *e)
{
	currentGlWidget->mousePressEvent(e);
}
void SculptorWindow::mouseMoveEvent(QMouseEvent *e)
{
	currentGlWidget->mouseMoveEvent(e);
}
void SculptorWindow::wheelEvent(QWheelEvent *e)
{
	currentGlWidget->wheelEvent(e);
}

void SculptorWindow::volume()
{
	bool volume_render = currentGlWidget->getVolumeRender();
	currentGlWidget->setVolumeRender(!volume_render);
}

void SculptorWindow::setVisibleLevel(int val)
{
    currentGlWidget->setVisibleLevel(val);
}

void SculptorWindow::spacingChanged(int val)
{
	currentGlWidget->setSpacingValue(val);
}

void SculptorWindow::setLeafVisible(int val){
    currentGlWidget->setLeafVisible(val);
}
