#ifndef QTSCULPTORWidget_H
#define QTSCULPTORWidget_H

#include <GL/glew.h>
#include <QtOpenGL/QGLWidget>
#include <QImageWriter>
#include <QFileDialog>
#include <iostream>
class QTimer;

class QtSculptorWidget:public QGLWidget
{
	Q_OBJECT
public:
	QtSculptorWidget( int timerInterval=0, QWidget *parent=0, QGLWidget *shareWidget = 0);
	QSize minimumSizeHint() const;
	QSize sizeHint() const;
	virtual void keyPressEvent( QKeyEvent *e );
public slots:
    void savePng(){
        QString s = QFileDialog::getSaveFileName(
                    this, tr("Save image (.png)"),
                            QDir::homePath(),
                            tr("png (*.png)"));
        savePng(s);
    }

    void savePng(QString s)
    {

        if (!s.isEmpty()){
            QImage img = grabFrameBuffer();
            QImageWriter writer;
            writer.setFormat("png");
            QString match(".png");
            if (!s.contains(match)){
                s.append(".png");
            }

            std::cout << s.toStdString() << std::endl;
            writer.setFileName(s);
            writer.write(img);
        }
    }
protected:
	//Got this from http://www.lighthouse3d.com/opengl/glsl/index.php?oglinfo
	// it prints out shader info (debugging!)
	//void printProgramInfoLog(GLuint obj);

	//Got this from http://www.lighthouse3d.com/opengl/glsl/index.php?oglinfo
	// it prints out shader info (debugging!)
	//void printShaderInfoLog(GLuint obj);

	virtual void initializeGL() = 0;
	virtual void resizeGL( int width, int height ) = 0;
	virtual void paintGL() = 0;
	virtual void timeOut();
	void drawFPS();
	void renderBitmapString(float x, float y, void *font,char *string);
	void resetPerspectiveProjection();
	void setOrthographicProjection();
protected slots:
	virtual void timeOutSlot();
private:
	QTimer *m_timer;
	int frame,timer,timebase;
	void* font;
	char s[30];
};

#endif
