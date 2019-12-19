#include "QtSculptorWidget.h"
#include <QKeyEvent>
#include <qapplication.h>
#include <qtimer.h>
#include <cstdio>

QtSculptorWidget::QtSculptorWidget( int timerInterval, QWidget *parent, QGLWidget *shareWidget ) : QGLWidget( parent, shareWidget )
{
	if( timerInterval == 0 )
            m_timer = 0;
		else
		{
			m_timer = new QTimer( this );
			connect( m_timer, SIGNAL(timeout()), this, SLOT(timeOutSlot()) );
			m_timer->start( timerInterval );
		}
	frame=0;
	timebase=0;
}

void QtSculptorWidget::keyPressEvent( QKeyEvent *e )
{
}

void QtSculptorWidget::timeOut()
{
    repaint();
}

void QtSculptorWidget::timeOutSlot()
{
	timeOut();
}

QSize QtSculptorWidget::minimumSizeHint() const
{
    return QSize(128, 128);
}

QSize QtSculptorWidget::sizeHint() const
{
    return QSize(512, 512);
}

void QtSculptorWidget::drawPNM()
{
    glColor3f(0.0f,1.0f,1.0f);

	setOrthographicProjection();
	glPushMatrix();
	glLoadIdentity();


    glRasterPos2f(0,0);

    GLubyte *pixels = new GLubyte[512*512*3];
    for (int i=0; i<512; i++){
        for (int j=0; j<512; j++){
            pixels[(i*512+j * 3)] = 0;
            pixels[(i*512+j * 3)+1] = 0;
            pixels[(i*512+j * 3)+1] = 0;
        }
    }
    pixels[(256 * 512 + 256)*3] = 255;
    pixels[(256 * 512 + 256)*3+1] = 255;
    pixels[(256 * 512 + 256)*3+2] = 255;
    glDrawPixels(512,512,GL_RGB, GL_UNSIGNED_BYTE, pixels);

    delete pixels;

    glPopMatrix();
    resetPerspectiveProjection();

}

void QtSculptorWidget::setOrthographicProjection() {

	// switch to projection mode
	glMatrixMode(GL_PROJECTION);
	// save previous matrix which contains the
	//settings for the perspective projection
	glPushMatrix();
	// reset matrix
	glLoadIdentity();
	// set a 2D orthographic projection
    glOrtho(0, 512, 0, 512, -1,1);
	// invert the y axis, down is positive
	glMatrixMode(GL_MODELVIEW);
}

void QtSculptorWidget::resetPerspectiveProjection() {
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}


