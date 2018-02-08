//通过画屏幕线来确定裁剪多少
#ifndef LABEL_VIDEO_H
#define LABEL_VIDEO_H

#include <QLabel>
#include <qevent.h>
#include <qrubberband.h>

class label_video : public QLabel
{
	Q_OBJECT

public:
	label_video(QWidget *parent);
	void set_scale_num(double, double);
	~label_video();

private:
	
	double num_w, num_h;
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	
	void mouseReleaseEvent(QMouseEvent *event);
	QPoint origin;
	QRubberBand *rubberBand;
};

#endif // LABEL_VIDEO_H
