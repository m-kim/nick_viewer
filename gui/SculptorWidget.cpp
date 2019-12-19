#include <QtGui/QKeyEvent>
#include <QtGui/QWheelEvent>

#include <string>
#include <sstream>
#include <iostream>

#include "SculptorWidget.h"

// Define the default location for eye and looking where
#define DEFAULT_EYE_X 0
#define DEFAULT_EYE_Y 0
#define DEFAULT_EYE_Z 2
#define DEFAULT_LOOKAT_X 0
#define DEFAULT_LOOKAT_Y 0
#define DEFAULT_LOOKAT_Z 0


#define GL_TEXTURE_TYPE GL_TEXTURE_RECTANGLE_ARB

using namespace std;
SculptorWidget::SculptorWidget( int timerInterval, QWidget *parent, QGLWidget *shareWidget):QtSculptorWidget(50, parent, shareWidget)
{
}

SculptorWidget::~SculptorWidget()
{
}


void SculptorWidget::initializeGL()
{
    //glEnable(GL_LIGHTING);
//	glEnable(GL_LIGHT0);
//	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_COLOR_MATERIAL);
//	glEnable(GL_NORMALIZE);
//    glCullFace(GL_BACK);
//    glPolygonMode(GL_FRONT, GL_FILL);
//    glPolygonMode(GL_BACK, GL_FILL);
//    glColorMaterial( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
    cout << "If you see this more than once...we're in trouble" << endl;
//	cam.tb = TrackBall(0.0,QVector3D(0,1,0),TrackBall::TrackMode::Sphere);
}

void SculptorWidget::resizeGL( int w, int h )
{
	glViewport(0,0,w,h);
    std::cout <<w  << " " << h << std::endl;
//    renderer->resize(w,h);
}

void SculptorWidget::paintGL()
{
//    renderer->drawRayEnd(cam);
	glClearColor(background_color.redF(), background_color.greenF(), background_color.blueF(), background_color.alphaF());
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    drawPNM();

}


void SculptorWidget::keyPressEvent( QKeyEvent *e )
{
	switch(e->key()){
	// quit
	case 27:
	case 'q':
	case 'Q':
		exit(0);
		break;
    default:
    	QtSculptorWidget::keyPressEvent(e);
	}

	QGLWidget::updateGL();
}

void SculptorWidget::mousePressEvent(QMouseEvent *e)
{
}

void SculptorWidget::mouseMoveEvent(QMouseEvent *e)
{
}

void SculptorWidget::mouseReleaseEvent(QMouseEvent *e)
{
}
void SculptorWidget::wheelEvent(QWheelEvent *e) 
{
}


void SculptorWidget::setBackgroundColor(float R, float G, float B)
{
	background_color.setRedF(R);
	background_color.setGreenF(G);
	background_color.setBlueF(B);
	QGLWidget::updateGL();
}

QColor SculptorWidget::getBackgroundColor()
{
	return background_color;
}


void SculptorWidget::setVisibleLevel(int val)
{
	//assume the val is between 1 and 100
    QGLWidget::updateGL();
}

void SculptorWidget::setSpacingValue(int val)
{
	//assume the val is between 1 and 100
    //drv->energy = (float)val/10.0;
    QGLWidget::updateGL();
}

void SculptorWidget::setLeafVisible(int val){
}
