#include "QtSculptorWidget.h"
#include <QKeyEvent>
#include <qapplication.h>
#include <qtimer.h>
#include <GL/glut.h>
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
    font = GLUT_BITMAP_8_BY_13;
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

void QtSculptorWidget::drawFPS()
{
	glColor3f(0.0f,1.0f,1.0f);
	frame++;
	timer=glutGet(GLUT_ELAPSED_TIME);
	if (timer - timebase > 1000) {
		sprintf(s,"FPS:%4.2f",frame*1000.0/(timer-timebase));
		timebase = timer;
		frame = 0;
	}

	setOrthographicProjection();
	glPushMatrix();
	glLoadIdentity();
	renderBitmapString(30,35,(void *)font,s);
	renderBitmapString(30,55,(void *)font,"Esc - Quit");
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
	gluOrtho2D(0, 512, 0, 512);
	// invert the y axis, down is positive
	glScalef(1, -1, 1);
	// mover the origin from the bottom left corner
	// to the upper left corner
	glTranslatef(0, -512, 0);
	glMatrixMode(GL_MODELVIEW);
}

void QtSculptorWidget::resetPerspectiveProjection() {
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void QtSculptorWidget::renderBitmapString(float x, float y, void *font,char *string)
{

  char *c;
  // set position to start drawing fonts
  glRasterPos2f(x, y);
  // loop all the characters in the string
  for (c=string; *c != '\0'; c++) {
    glutBitmapCharacter(font, *c);
  }
}
