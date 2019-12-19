#ifndef SculptorWidget_H
#define SculptorWidget_H
#include <sstream>

#include "QtSculptorWidget.h"

typedef char VOLUME_TYPE;

class SculptorWidget : public QtSculptorWidget
{
public:
	SculptorWidget( int timerInterval=0, QWidget *parent=0, QGLWidget *shareWidget = 0);
	~SculptorWidget();
	void keyPressEvent( QKeyEvent *e );

    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
	void mouseReleaseEvent(QMouseEvent *);
	void wheelEvent(QWheelEvent *);

    QColor getBackgroundColor();
    void setBackgroundColor(float R, float G, float B);
    bool getVolumeRender(){return volume_render;};
    void setVolumeRender(bool _vol_render){volume_render = _vol_render;  QGLWidget::updateGL();};
    void setVisibleLevel(int val);
    void setSpacingValue(int val);
    void setLeafVisible(int val);

protected:
	void initializeGL();
	void resizeGL( int width, int height );
	void paintGL();
private:
    GLuint texvolume;

	QColor background_color;
	bool volume_render;

};
#endif
