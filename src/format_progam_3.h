/******************�����������ļ�����******************************/
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
	//����Ҫ�ü��Ĵ�С
	void set_line_num(double, double, double, double);
	//�������ڲ��ŵ��ļ���
	void set_input_name(QString str);
	~format_progam_3();
	//��ʼ������Ƶ
	void start();
	//double get_video_clock(PlayerState *is);
	int incr; //seek frame������
protected:
	void closeEvent(QCloseEvent *event);
	//����ǰ�����Ҽ���ʹ�ÿ��������
	void keyPressEvent(QKeyEvent *k);
	public slots:
	void caption_ok();
	void line_caption_slot();
	
	void is_check();
	//�������
	void dealer_ok();
	void handle_filter_changed(int);
	//����ͼƬ
	void save_jpeg();
	void start_edit_finish();
	//����ʱ��
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
	QString input_name; //���ڲ��ŵ��ļ���
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
