#ifndef SculptorWidget_H
#define SculptorWidget_H
#include <sstream>
#include <RayCastRenderer.h>
#include "MarchingCubes.h"

#include "QtSculptorWidget.h"
#include <TrackballCamera.h>
#include <Light.h>
#include <Shader.h>
#include "drawbh.h"

typedef char VOLUME_TYPE;

class DriverBH;
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
    DriverBH *drv;

protected:
	void initializeGL();
	void resizeGL( int width, int height );
	void paintGL();
private:
    GLuint texvolume;
    TrackballCamera cam;
    RayCastRenderer<GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT, GL_REPEAT,
					VOLUME_TYPE, GL_LUMINANCE,GL_LUMINANCE,GL_UNSIGNED_BYTE> *renderer;

	Light light;

	QColor background_color;
    std::vector<VOLUME_TYPE> volume;
	bool volume_render;
    DrawBH drawbh;

};
#endif
