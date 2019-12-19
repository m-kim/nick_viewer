#include <QtGui/QKeyEvent>
#include <QtGui/QWheelEvent>

#include <string>
#include <sstream>
#include <iostream>

#include "SculptorWidget.h"
#include "src_path.h"
#include "dataset_path.h"
#include "DriverBH.h"
#include "Particle.h"
#include "BarnesHut.h"

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

	cam.eye.convertArray(DEFAULT_EYE_X, DEFAULT_EYE_Y, DEFAULT_EYE_Z);
	cam.lookat.convertArray(DEFAULT_LOOKAT_X, DEFAULT_LOOKAT_Y, DEFAULT_LOOKAT_Z);

	light.canonicalLight[0] = 0;
	light.canonicalLight[1] = 5;
	light.canonicalLight[2] = 0;

}

SculptorWidget::~SculptorWidget()
{
    stringstream str;
    str << "output.xyz";
    drv->saveParticles(str);
}


void SculptorWidget::initializeGL()
{
    //glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);
    glCullFace(GL_BACK);
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_FILL);
    glColorMaterial( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
    cout << "If you see this more than once...we're in trouble" << endl;
//	cam.tb = TrackBall(0.0,QVector3D(0,1,0),TrackBall::TrackMode::Sphere);
}

void SculptorWidget::resizeGL( int w, int h )
{
	glViewport(0,0,w,h);
	cam.resize(w,h);
//    renderer->resize(w,h);
}

void SculptorWidget::paintGL()
{
//    renderer->drawRayEnd(cam);
	glClearColor(background_color.redF(), background_color.greenF(), background_color.blueF(), background_color.alphaF());
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	cam.preProjection();
	cam.preLookat();
	cam.lookAt();

    //renderer->render(cam, Vector_f(0,0,0), Vector_f(1,1,1), Vector_f(0.01,0.01,0.01));
    glPointSize(3.0);

    glTranslatef(-0.5,-0.5,-0.5);
//    for (int z=0; z<2; z++){
//        glBegin(GL_LINE_LOOP);
//        glVertex3f(0,           0,          z);  glVertex3f(1,0,        z);
//        glVertex3f(1,  1,  z);  glVertex3f(0,       1, z);
//        glEnd();
//    }
//    glBegin(GL_LINES);
//    for (int y=0; y<2; y++){
//        glVertex3f(1,  y, 0);  glVertex3f(1,   y,   1);
//        glVertex3f(0,           y, 0);  glVertex3f(0         ,   y,   1);
//    }
    drawbh.drawLevel(drv);
    //drawbh.drawObject(drv);
    cam.postProjection();
	cam.postLookAt();
	drawFPS();

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
	switch(e->button()){
	case Qt::LeftButton:
        cam.mouse(1, 0,e->x(),e->y());		//GLUT_DOWN == 0, GLUT_LEFT_BUTTON == 0
		break;

	case Qt::RightButton:
        cam.mouse(0, 0,e->x(),e->y());		//GLUT_DOWN == 0, GLUT_RIGHT_BUTTON == 1
		break;
	}
	e->accept();
}

void SculptorWidget::mouseMoveEvent(QMouseEvent *e)
{
	cam.motion(e->x(),e->y());
	e->accept();
   	QGLWidget::updateGL();
}

void SculptorWidget::mouseReleaseEvent(QMouseEvent *e)
{
	QGLWidget::mouseReleaseEvent(e);
	if (e->isAccepted())
		return;
	if (e->buttons() & Qt::RightButton){
		cam.release(e->x(), e->y());
		e->accept();
	}
	else if(e->buttons() & Qt::LeftButton){
		e->accept();
	}
	updateGL();
}
void SculptorWidget::wheelEvent(QWheelEvent *e) 
{
	cam.zoom(e->delta());
	e->accept();
    updateGL();
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
    drawbh.level = val;
    QGLWidget::updateGL();
}

void SculptorWidget::setSpacingValue(int val)
{
	//assume the val is between 1 and 100
    //drv->energy = (float)val/10.0;
    QGLWidget::updateGL();
}

void SculptorWidget::setLeafVisible(int val){
    drawbh.stop_at_leaf = val;
}
