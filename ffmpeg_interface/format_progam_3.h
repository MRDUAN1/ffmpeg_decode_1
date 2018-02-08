/******************播放器所在文件的类******************************/
#ifndef FORMAT_PROGAM_3_H
#define FORMAT_PROGAM_3_H

#include <QtWidgets/QWidget>
#include "ui_format_progam_3.h"
#include "player.h"
#include "wrap_base.h"
#include "packet_queue.h"
#include "audio.h"
#include "video.h"
#include <qtimer.h>
#include <process.h>
#include <Windows.h>
#include <qlayout.h>
#include "label_video.h"

class format_progam_3 : public QWidget
{
	Q_OBJECT

public:
	
	format_progam_3(QWidget *parent = 0);
	//设置要裁剪的大小
	void set_line_num(double, double, double, double);
	//设置正在播放的文件名
	void set_input_name(QString str);
	~format_progam_3();
	//开始播放视频
	void start();
	//double get_video_clock(PlayerState *is);
	int incr; //seek frame的增量
protected:
	void closeEvent(QCloseEvent *event);
	//控制前后左右键，使得快进或慢退
	void keyPressEvent(QKeyEvent *k);
	public slots:
	void caption_ok();
	void line_caption_slot();
	
	void is_check();
	//播放完成
	void dealer_ok();
	void handle_filter_changed(int);
	//保存图片
	void save_jpeg();
	void start_edit_finish();
	//结束时间
	void end_edit_finish();
	void suspend_play();
	void slow_play();
	void fast_play();
	void slider_change(int num);
	void update_slider();
	void breaks();
private:
	
	//QString filter_mirror1, filter_mirror12, filter_mirror3, filter_descr3, filter_watermark, filter_negate, filter_edge, filter_split4, filter_vintage;
	bool ok_exit;
	label_video *la;
	void set_name();
	QTimer *time;
	QString input_name; //正在播放的文件名
	int position;
	void set_progressbar();
	int hours, mins, secs, us;
	HANDLE io_cp;
	bool is_play;
	PlayerState    *ps = NULL;
	Ui::format_progam_3 ui;
	double pos_s;
	bool is_select;
	QString pos_ww;
	QString pos_hh;
	QString wid_ww;
	QString wid_hh;
};

#endif // FORMAT_PROGAM_3_H
