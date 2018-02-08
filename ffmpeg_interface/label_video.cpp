#include "label_video.h"
#include "format_progam_3.h"
#include "global.h"
label_video::label_video(QWidget *parent)
	: QLabel(parent)
{
	rubberBand = NULL;
	rubberBand = new QRubberBand(QRubberBand::Line, this);
	rubberBand->setStyleSheet("QWidget{border:2px solid red; border-color:transparent}");
}
void label_video::set_scale_num(double num_w_, double num_h_)
{
	num_h = num_h_;
	num_w = num_w_;
}
label_video::~label_video()
{

}
void label_video::mousePressEvent(QMouseEvent *event)
{
	origin = event->pos();
//	if (!rubberBand)
	//	rubberBand = new QRubberBand(QRubberBand::Line, this);
	rubberBand->setGeometry(QRect(origin, QSize()));
	rubberBand->show();
}
void label_video::mouseMoveEvent(QMouseEvent *event)
{
	rubberBand->setGeometry(QRect(origin, event->pos()).normalized());
}

void label_video::mouseReleaseEvent(QMouseEvent *event)
{
	rubberBand->hide();
	QPoint po = rubberBand->pos();
	double p_w_ = po.x() * num_w;
	double p_h_ = po.y() * num_h;
	QSize o = rubberBand->size();
	double width_ = o.width() * num_w;
	double height_ = o.height() * num_h;
	global::return_format()->set_line_num(p_w_, p_h_, width_, height_);

}

