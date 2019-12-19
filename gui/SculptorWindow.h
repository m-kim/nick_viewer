#ifndef SCULPTORWINDOW_H
#define SCULPTORWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
class SculptorWidget;
class DriverBH;
class SculptorWindow : public QMainWindow
{
    Q_OBJECT

public:
    SculptorWindow(DriverBH *d);
    void keyPressEvent( QKeyEvent *e );
    void mousePressEvent(QMouseEvent *);
	void mouseMoveEvent(QMouseEvent *);
	void wheelEvent(QWheelEvent *);
//private slots:
//    void setCurrentGlWidget();
//    void rotateOneStep();
	void connectActions();
protected slots:
	void about();
	void background();
	void volume();
    void setVisibleLevel(int);
	void spacingChanged(int);
    void setLeafVisible(int val);


private:

    enum { NumRows = 2, NumColumns = 3 };
    Ui::MainWindow *ui;
    SculptorWidget *currentGlWidget;
};

#endif
