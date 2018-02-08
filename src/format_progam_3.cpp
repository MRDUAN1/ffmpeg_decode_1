#include "format_progam_3.h"
#include "SDL2/SDL.h"
#include "global.h"
#include "include\SDL2\SDL_main.h"
#include <qmessagebox.h>
#include <qevent.h>
#include <string>
#include <map>
static bool is_over;
static label_video *laa;
# pragma execution_character_set("utf-8")
#define SDL_MAIN_HANDLE
#pragma comment(lib, "lib/avutil.lib")
#pragma comment(lib, "lib/avcodec.lib")
#pragma comment(lib, "lib/avformat.lib")
#pragma comment(lib, "lib/avdevice.lib")
#pragma comment(lib, "lib/swresample.lib")
#pragma comment(lib, "lib/avfilter.lib")
#pragma comment(lib, "lib/SDL2.lib")
#pragma comment(lib, "lib/SDL2main.lib")
#pragma comment(lib, "lib/swscale.lib")
//裁剪需要四个参数，改分辨率三个参数
static string string_filter;
static QString str;
static bool if_break;
static bool is_close;
double get_video_clock(PlayerState *is)
{
	double delta;

	delta = (av_gettime() - is->cur_frame_pts) / 1000000.0;
	return is->cur_frame_pts + delta;
}
double get_external_clock(PlayerState *is)
{
	return av_gettime() / 1000000.0;
}
double get_master_clock(PlayerState *is)
{
	return is->cur_frame_pts;
}
void stream_seek(PlayerState *is, int64_t pos, int rel)
{
	if (!is->seek_req)
	{
		is->seek_pos = pos;
		is->seek_flags = rel < 0 ? AVSEEK_FLAG_BACKWARD : AVSEEK_FLAG_BYTE;
		is->seek_req = 1;
	}
}
void format_progam_3::set_input_name(QString str)
{
	input_name = str;
}
void format_progam_3::keyPressEvent(QKeyEvent *k)
{
	if (k->key() == Qt::Key_Down)
	{
		incr = -10.0;
		goto do_seek;
	}
	if (k->key() == Qt::Key_Up)
	{
		incr = 10;
		goto do_seek;
	}
	if (k->key() == Qt::Key_Left)
	{
		incr = -10;
		goto do_seek;
	}
	if (k->key() == Qt::Key_Right)
	{
		incr = 10;
		goto do_seek;
	}
do_seek:
	pos_s = get_master_clock(ps);
	pos_s += incr;
	stream_seek(ps, (int64_t)(pos_s * AV_TIME_BASE), incr);
	incr = 0;
}
void format_progam_3::save_jpeg()
{
	bool l = true;
	global::set_camera_status(l);
}
void format_progam_3::set_line_num(double pos_w, double pos_h, double wid_w, double wid_h)
{
	pos_ww = QString::number(pos_w);
	pos_hh = QString::number(pos_h);
	wid_ww = QString::number(wid_w);
	wid_hh = QString::number(wid_h);
	QString al = wid_ww + ":" + wid_hh + ":" + pos_ww + ":" + pos_hh;
	ui.lineEdit->setText(al);
	string_filter = "crop=" + al.toStdString();
	tree_file *tr = new tree_file;
	tr->i = 2;
	tr->string_filter = string_filter;
	global::return_decode_detail()[input_name.toLocal8Bit().data()] = tr;
}
format_progam_3::format_progam_3(QWidget *parent)
: QWidget(parent)
{
	ui.setupUi(this);
	//this->show()
	ui.start_2->setText("从");
	ui.end_2->setText("到");
	ui.checkBox->setText("添加特效");
	ui.start->setIcon(QIcon("./stop.png"));
	this->setWindowFlags(Qt::Dialog);
	this->setWindowModality(Qt::WindowModal);
	this->show();
	ui.label_cut->setText("裁剪范围");
	is_over = false;
	is_close = false;
	ok_exit = false;
	ui.slow->setIcon(QIcon("./imag/slow_slow.png"));
	ui.quick->setIcon(QIcon("./imag/fast_fast.png"));
	ui.break_->setIcon(QIcon("./imag/stopp.png"));
	this->setAttribute(Qt::WA_DeleteOnClose);
	ui.frame_3->setEnabled(false);
	ui.frame_3->setStyleSheet("border:1px solid black");
	ui.label_size_caption->setText("请输入字幕大小");
	//ui.captions_color->hide();
	ui.captions_color->addItem("红色");
	ui.captions_color->addItem("黑色");
	ui.captions_color->addItem("白色");
	ui.captions_color->addItem("绿色");
	ui.captions_color->addItem("蓝色");
	//ui.captions_color->addItem("红色");
	ui.add_filter->setText("视频特效");
	ui.filte_choice->addItem("无");
	//ui.filte_choice->addItem("添加字幕");
	ui.filte_choice->addItem("改变分辨率");
	ui.filte_choice->addItem("裁剪视频");
	ui.filte_choice->addItem("反转");
	ui.filte_choice->addItem("视频镜像");
	ui.filte_choice->addItem("视频反色");
	ui.filte_choice->addItem("复古");
	ui.filte_choice->addItem("添加字幕");
	ui.filte_choice->addItem("滚动字幕");
	format_progam_3 *temp = this;
	global::set_format(temp);
	bool is = false;
	global::set_camera_status(is);
	//this->setAttribute(Qt::WA_DeleteOnClose);
	position = 0;
	if_break = true;
	ui.start_video->setText("00:0:0");
	set_name();
	ui.save_picture->setText("保存图片");
	ui.label_size->setText("字幕位置");
	ui.label_size->setEnabled(false);
	connect(ui.lineEdit_4, SIGNAL(editingFinished()), this, SLOT(caption_ok()));
	connect(ui.checkBox, SIGNAL(stateChanged(int)), this, SLOT(is_check()));
	connect(ui.line_caption, SIGNAL(editingFinished()), this, SLOT(line_caption_slot()));
	connect(ui.filte_choice, SIGNAL(currentIndexChanged(int)), this, SLOT(handle_filter_changed(int)));
	connect(ui.save_picture, SIGNAL(clicked()), this, SLOT(save_jpeg()));
	connect(ui.break_, SIGNAL(clicked()), this, SLOT(breaks()));
	connect(ui.slow, SIGNAL(clicked()), this, SLOT(slow_play()));
	connect(ui.start, SIGNAL(clicked()), this, SLOT(suspend_play()));
	connect(ui.quick, SIGNAL(clicked()), this, SLOT(fast_play()));
	connect(ui.horizontalSlider, SIGNAL(sliderMoved(int)), this, SLOT(slider_change(int)));
	connect(ui.lineEdit_2, SIGNAL(editingFinished()), this, SLOT(start_edit_finish()));
	connect(ui.lineEdit_3, SIGNAL(editingFinished()), this, SLOT(end_edit_finish()));
	connect(ui.ok, SIGNAL(clicked()), this, SLOT(dealer_ok()));
}
void format_progam_3::caption_ok()
{
	ui.line_caption->setEnabled(true);
}
//程序退出，点击ok后程序退出
void format_progam_3::dealer_ok()
{
	ok_exit = true;
	this->close();
}
void format_progam_3::is_check()
{
	Qt::CheckState i = ui.checkBox->checkState();
	if (i == Qt::CheckState::Unchecked)
		ui.frame_3->setEnabled(false);
	else ui.frame_3->setEnabled(true);
}
void format_progam_3::line_caption_slot()
{
	string paramter = ui.line_caption->text().toStdString();
	int i = ui.filte_choice->currentIndex();
	if (i == 1) string_filter += paramter + "/a";

	else if (i == 2) {
		string_filter += paramter;
	}
	else if (i == 7)
	{
		ui.label_size->setEnabled(true);
		int index = ui.captions_color->currentIndex();
		int index_size = ui.size->currentIndex();
		int sizee = 10 + 5 * index_size;
		char hh[20] = { '\0' };
		itoa(sizee, hh, 10);
		string ie(hh);
		switch (index)
		{

		case 0:
		{
				  string_filter += "red:fontsize=" + ie + ":text='" + paramter + "':"+ ui.lineEdit_4->text().toStdString();
				  break;
		}
		case 1:
		{
				  string_filter += "black:fontsize=" + ie + ":text='" + paramter + "':" + ui.lineEdit_4->text().toStdString();
				  break;
		}
		case 2:
		{
				  string_filter += "white:fontsize=" + ie + ":text='" + paramter + "':" + ui.lineEdit_4->text().toStdString();
				  break;
		}
		case 3:
		{
				  string_filter += "black:fontsize=" + ie + ":text='" + paramter + "':" + ui.lineEdit_4->text().toStdString();
				  break;
		}
		case 4:
		{
				  string_filter += "green:fontsize=" + ie + ":text='" + paramter + "':" + ui.lineEdit_4->text().toStdString();
				  break;
		}
		case 5:
		{
				  string_filter += "blue:fontsize=" + ie + ":text='" + paramter + "':" + ui.lineEdit_4->text().toStdString();
				  break;
		}
		}
	}
	tree_file *temp_tree_file = new tree_file;
	temp_tree_file->i = i;
	temp_tree_file->string_filter = string_filter;
	global::return_decode_detail()[input_name.toLocal8Bit().data()] = temp_tree_file;
}
void format_progam_3::handle_filter_changed(int i)
{
	if (i == 0)
	{
		string_filter = "null";
		ui.label_choice->setText("未选中");
		ui.line_caption->setEnabled(false);
		
	}
	else if (i == 1)
	{
		string_filter = "scale=";
		ui.label_choice->setText("请输入分辨率");
		ui.label_choice->setToolTip("格式:分辨率:x:y");
		ui.line_caption->setEnabled(true);
		ui.lineEdit_4->setEnabled(false);
		ui.size->setEnabled(false);
		ui.captions_color->setEnabled(false);
	}
	else if (i == 2)
	{
		string_filter = "crop=";
		ui.label_choice->setText("请输入要裁剪区域大小");
		ui.label_choice->setToolTip("格式:x:y:宽度:高度");
		ui.line_caption->setEnabled(true);
		ui.lineEdit_4->setEnabled(false);
		ui.size->setEnabled(false);
		ui.captions_color->setEnabled(false);
	}
	else if (i == 3)
	{
		string_filter = "negate";
		ui.label_choice->setText("反色");
		ui.line_caption->setEnabled(false);
		ui.lineEdit_4->setEnabled(false);
		ui.size->setEnabled(false);
		ui.captions_color->setEnabled(false);
		tree_file *f = new tree_file;
		f->i = 3;
		f->string_filter = string_filter;
		global::return_decode_detail()[input_name.toLocal8Bit().data()] = f;
	}
	else if (i == 4)
	{
		string_filter = "crop=iw/2:ih:0:0,split[left][tmp];[tmp]hflip[right]";
		ui.label_choice->setText("视频镜像");
		ui.line_caption->setEnabled(false);
		ui.lineEdit_4->setEnabled(false);
		ui.size->setEnabled(false);
		ui.captions_color->setEnabled(false);
		tree_file *f = new tree_file;
		f->i = 4;
		f->string_filter = string_filter;
		global::return_decode_detail()[input_name.toLocal8Bit().data()] = f;
	}
	else if (i == 5)
	{
		string_filter = "edgedetect[out]";
		ui.label_choice->setText("视频反转");
		ui.line_caption->setEnabled(false);
		ui.lineEdit_4->setEnabled(false);
		ui.size->setEnabled(false);
		ui.captions_color->setEnabled(false);
		tree_file *f = new tree_file;
		f->i = 5;
		f->string_filter = string_filter;
		global::return_decode_detail()[input_name.toLocal8Bit().data()] = f;
	}
	else if (i == 6)
	{
		string_filter = "curves=vintage";
		ui.label_choice->setText("复古效果");
		ui.line_caption->setEnabled(false);
		ui.lineEdit_4->setEnabled(false);
		ui.size->setEnabled(false);
		ui.captions_color->setEnabled(false);
		tree_file *f = new tree_file;
		f->i = 6;
		f->string_filter = string_filter;
		global::return_decode_detail()[input_name.toLocal8Bit().data()] = f;
	}
	else if (i == 7)
	{
		string_filter = "drawtext=fontfile=ttt.ttf:fontcolor=";
		ui.label_choice->setText("请输入字幕");
		ui.line_caption->setEnabled(false);
		ui.size->setEnabled(true);
		ui.captions_color->setEnabled(true);
	}
	else if (i == 8)
	{
		string_filter = "drawtext=fontfile=ttt.ttf:fontcolor=";
		ui.label_choice->setText("请输入字幕");
		ui.line_caption->setEnabled(false);
		ui.size->setEnabled(true);
		ui.captions_color->setEnabled(true);
	}

}
//结束时间
void format_progam_3::end_edit_finish()
{
	QString str = ui.lineEdit_2->text();
	
}
//起始时间
void format_progam_3::start_edit_finish()
{
	QString str = ui.lineEdit_3->text();
}
//停止播放
void format_progam_3::breaks()
{
	if_break = false;
}
//根据视频进度更新进度条
void format_progam_3::update_slider()
{
	ui.horizontalSlider->setSliderPosition(ps->cur_frame_pts);
	int len = ui.horizontalSlider->sliderPosition();

	int minn = len / 60;
	//secs %= 60;
	int hour = mins / 60;
	int sec = len - hour * 60 * 60 - minn * 60;
	QString hor = QString::number(hour);
	QString minnn = QString::number(minn);
	QString secnn = QString::number(sec);
	QString str_time;
	if (hour == 0)
		str_time = QString("00:%1:%2").arg(minn).arg(secnn);
	else
		str_time = QString("%1:%2:%3").arg(hor).arg(minn).arg(secnn);
	ui.horizontalSlider->setToolTip(str_time);
	ui.start_video->setText(str_time);
}
//关闭窗口结束播放进程，关闭声音
void format_progam_3::closeEvent(QCloseEvent *event)
{
	is_close = true;
	TerminateThread(io_cp, 0);
	string_filter.clear();
	str.clear();
	ps = NULL;
	if_break = false;
	bool temp = false;
	global::set_camera_status(temp);
	//如果已经结束就关闭声音
	if (!is_over)
	SDL_CloseAudio();
	if (!ok_exit)
	{
		if (global::return_decode_detail().find(input_name.toLocal8Bit().data()) != global::return_decode_detail().end())
		{
			global::return_decode_detail().erase(input_name.toLocal8Bit().data());
		}
	}
}
format_progam_3::~format_progam_3()
{

}
void format_progam_3::set_name()
{
	
	ui.cut_cut->setText("截取片断");
	ui.end_2->setToolTip("停止");
	ui.end_cut_now->setText("结束时间");
	ui.start_time_cut->setText("开始时间");
	ui.quick->setToolTip("快进");
	ui.slow->setToolTip("慢放");
	ui.ok->setText("开始");
	
}
void format_progam_3::start()
{
	str = input_name;
	time = new QTimer;
	time->setInterval(1000);
	time->start();
	connect(time, SIGNAL(timeout()), this, SLOT(update_slider()));
	is_play = true;
	SDL_Event event;
	ps = (PlayerState *)av_malloc(sizeof(PlayerState));
	if (ps == NULL)
	{
		fprintf(ERR_STREAM, "malloc ps error\n");
	}

	player_state_init(ps);
	memset(ps->filename, 0, 1024);
	memcpy(ps->filename, input_name.toLocal8Bit().data(), strlen(input_name.toLocal8Bit().data()));

	//get_file_name(ps->filename, argc, argv);

	if (prepare_common(ps) != 0)
	{
		fprintf(ERR_STREAM, "prepare common error\n");
		exit(-1);
	}

	av_dump_format(ps->pformat_ctx, 0, ps->filename, false);
	//至少有一种流，读流，解码。

	if (ps->audio_stream_index != -1)
	{
		packet_queue_init(&ps->audio_packet_queue);
		prepare_audio(ps);
		play_audio(ps);
	}
	la = new label_video(this);
	laa = la;
	la->setGeometry(20, 10, 300, 265);
	
	la->show();
	HWND i = (HWND)la->winId();
	ps->pwindow = SDL_CreateWindowFrom((void*)i);
	if (ps->video_stream_index != -1)
	{
		packet_queue_init(&ps->video_packet_queue);
		prepare_video(ps);
		play_video(ps);
	}

	if (ps->pformat_ctx->duration != AV_NOPTS_VALUE)
	{
		int64_t duration = ps->pformat_ctx->duration + 5000;
		secs = duration / AV_TIME_BASE;
		us = duration % AV_TIME_BASE;
		mins = secs / 60;
		//secs %= 60;
		hours = mins / 60;
		mins %= 60;
		set_progressbar();
	}
	int w = ps->pvideo_codec_ctx->width;
	int h = ps->pvideo_codec_ctx->height;
	double num_w = w / 300;
	double num_h = h / 265;
	la->set_scale_num(num_w, num_h);
	//SDL_CreateThread(decode_thread, "decode_thread", ps);
	io_cp = (HANDLE)_beginthread(decode_thread, 0, ps);
	while (1)
	{
		if (ps == NULL)
			return;
		if (is_close)
		{
			is_close = false;
			return;
		}
		if (ps->quit == 1)
		{
			break;
		}
		SDL_WaitEvent(&event);
		switch (event.type)
		{
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_LEFT:
				incr = -10.0;
				goto do_seek;
			case SDLK_RIGHT:
				incr = 10.0;
				goto do_seek;
			case SDLK_UP:
				incr = 60.0;
				goto do_seek;
			case SDLK_DOWN:
				incr = -60.0;
				goto do_seek;
			do_seek:
				pos_s = get_master_clock(ps);
				pos_s += incr;
				stream_seek(ps, (int64_t)(pos_s * AV_TIME_BASE), incr);
				incr = 0;
				break;
			}
		case ISSHE_REFRESH_EVENT:
		{
									if (is_close)
									{
										is_close = false;
										return;
									}
									decode_and_show(ps);
									break;
		}
		case SDL_WINDOWEVENT:
		{   SDL_GetWindowSize(ps->pwindow, &ps->window_w, &ps->window_h);
		break;
		}
		case SDL_QUIT:
		{
						 printf("SDL_QUIT！\n");
						 ps->quit = 1;
						 SDL_Quit();
						 break;
		}
		default:
		{
				   break;
		}
		}

	}
	//
	if (ps->video_stream_index != -1)
	{
		sws_freeContext(ps->psws_ctx);
	}
	is_over = true;
	return;
}
int prepare_common(PlayerState *ps)
{

	av_register_all();
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER))
	{
		fprintf(ERR_STREAM, "init SDL error: %s\n", SDL_GetError());
		return -1;
	}
	//打开文件
	//pformat_ctx会有所指向，不用分配内存
	if (avformat_open_input(&ps->pformat_ctx, str.toLocal8Bit().data(), NULL, NULL) != 0)
	{
		fprintf(ERR_STREAM, "open input file error\n");
		return -1;
	}

	if (avformat_find_stream_info(ps->pformat_ctx, NULL) < 0)
	{
		fprintf(ERR_STREAM, "Couldn't find stream info\n");
		return -1;
	}

	ps->video_stream_index = -1;
	ps->audio_stream_index = -1;
	if (find_stream_index(ps->pformat_ctx,
		&ps->video_stream_index,
		&ps->audio_stream_index) == -2)
	{
		fprintf(ERR_STREAM, "Couldn't find any stream index\n");
		return -1;
	}

	return 0;
}



/*======================================================================\
* Author     (作者): i.sshe
* Date       (日期): 2016/10/06
* Others     (其他): 只负责从流中读取packet
\*=======================================================================*/
void decode_thread(void *arg)
{
	PlayerState *ps = (PlayerState *)arg;
	AVPacket	packet;
	ps->seek_req = 0;
	//    AVPacket    *packet = av_packet_alloc();

	while (1)
	{
		if (!if_break)
		{
			break;
		}
		if (ps->quit == 1)
		{
			break;
		}
		if (ps->seek_req)
		{
			int stream_index = -1;
			int64_t seek_target = ps->seek_pos;

			/*if (ps->videoStream >= 0)
			stream_index = ps->videoStream;
			else if (ps->audioStream >= 0)
			stream_index = is->audioStream;*/

			if (stream_index >= 0)
			{
				AVRational base_q;
				base_q.den = 1;
				base_q.num = AV_TIME_BASE;
				seek_target = av_rescale_q(seek_target, base_q, ps->pformat_ctx->streams[stream_index]->time_base);
			}
			int p;
			if ((p = av_seek_frame(ps->pformat_ctx, stream_index, seek_target, AVSEEK_FLAG_ANY)) < 0)
			{

				fprintf(stderr, "%s: error while seeking/n", ps->pformat_ctx->filename);
			}
			ps->seek_pos = 0;
			/*else
			{
			if (is->audioStream >= 0)
			{
			packet_queue_flush(&is->audioq);
			//	packet_queue_put(&is->audioq, &flush_pkt);
			}
			if (is->videoStream >= 0)
			{
			packet_queue_flush(&is->videoq);
			//	packet_queue_put(&is->videoq, &flush_pkt);
			}
			}*/
			packet_queue_flush(&ps->video_packet_queue);
			packet_queue_flush(&ps->audio_packet_queue);
			ps->seek_req = 0;
			printf("av_seek_frame called/n");
		}
		//如果队列数据过多，就等待以下
		if (ps->audio_packet_queue.nb_packets >= MAX_AUDIO_QUEUE_SIZE ||
			ps->video_packet_queue.nb_packets >= MAX_VIDEO_QUEUE_SIZE)
		{
			printf("过多数据，延时\n");
			SDL_Delay(100);
			continue;
		}

		if (av_read_frame(ps->pformat_ctx, &packet) < 0)
		{
			if ((ps->pformat_ctx->pb->error) == 0)
			{
				printf("读完延时\n");
				SDL_Delay(100); //不是出错，可能是读完了
				break;//continue;
			}
			else
			{
				printf("出错，延时\n");
				continue; 		//出错了，继续读，这里
			}
		}
		//读取到数据了
		if (packet.stream_index == ps->video_stream_index)
		{
			packet_queue_put(&ps->video_packet_queue, &packet);
		}

		if (packet.stream_index == ps->audio_stream_index)
		{
			packet_queue_put(&ps->audio_packet_queue, &packet);
		}
		//av_free_packet(&packet);
	}
	laa->setStyleSheet("background-color:black");
	laa->setPixmap(QPixmap("./imag/start.png"));
	if_break = true;
	is_over = true;
	//    
	return ;
}
void player_state_init(PlayerState *ps)
{
	ps->pformat_ctx = NULL;
	ps->quit = 0;

	ps->audio_stream_index = -1;
	ps->paudio_stream = NULL;
	ps->paudio_codec_ctx = NULL;
	ps->paudio_codec = NULL;
	ps->audio_buf_size = 0;
	ps->audio_buf_index = 0;
	//视频
	ps->video_stream_index = -1;
	ps->pvideo_stream = NULL;
	ps->pvideo_codec_ctx = NULL;
	ps->pvideo_codec = NULL;
	ps->video_buf = NULL;
	ps->video_buf_size = 0;
	ps->video_buf_index = 0;
	ps->psws_ctx = NULL;

	ps->pixel_w = 0;
	ps->pixel_h = 0;
	ps->window_w = 0;
	ps->window_h = 0;

	ps->pwindow = NULL;
	ps->prenderer = NULL;
	ps->ptexture = NULL;
	ps->pixfmt = AV_PIX_FMT_YUV420P;

	ps->audio_clock = 0.0;
	ps->video_clock = 0.0;
	ps->pre_frame_pts = 0.0;		//前一帧显示时间
	//   ps->cur_frame_pkt_pts			= 0.0; 		//当前帧在packet中标记的pts
	ps->pre_cur_frame_delay = 40e-3; 	//当前帧和前一帧的延时，前面两个相减的结果
	ps->cur_frame_pts = 0.0;		//packet.pts
	ps->delay = 40;
	//    ps->frame_timer 				= (double)av_gettime()/1000000.0;
}
void format_progam_3::suspend_play()
{
	if (is_play)
	{
		ui.start->setIcon(QIcon("./imag/play.png"));
		SuspendThread(io_cp);
		is_play = false;
	}
	else
	{
		ui.start->setIcon(QIcon("./imag/stop.png"));
		ResumeThread(io_cp);
		is_play = true;
	}

}
void format_progam_3::slow_play()
{
	incr = -10;
	pos_s = get_master_clock(ps);
	pos_s += incr;
	stream_seek(ps, (int64_t)(pos_s * AV_TIME_BASE), incr);
	incr = 0;
}
void format_progam_3::fast_play()
{
	incr = 10;
	pos_s = get_master_clock(ps);
	pos_s += incr;
	stream_seek(ps, (int64_t)(pos_s * AV_TIME_BASE), incr);
	incr = 0;
}
void format_progam_3::set_progressbar()
{
	ui.horizontalSlider->setMinimum(0);  // 最小值
	ui.horizontalSlider->setMaximum(secs);  // 最大值
	ui.horizontalSlider->setValue(0);
	int minn = secs / 60;
	//secs %= 60;
	int hour = minn / 60;
	if (hour > 0) minn -= 60;
	int sec = secs - hour * 60 * 60 - minn * 60;
	QString hor = QString::number(hours);
	QString minnn = QString::number(mins);
	QString secnn = QString::number(secs);
	if (hour == 0)
		str = QString("%1:%2").arg(minn).arg(secnn);
	else
		str = QString("%1:%2:%3").arg(hor).arg(minn).arg(secnn);
	ui.end_video->setText(str);
	//int hours, mins, secs, us;
}
void format_progam_3::slider_change(int num)
{
	int numm;
	if (position > ui.horizontalSlider->sliderPosition())
	{
		numm = -num;
	}
	else
		numm = num;
	position = ui.horizontalSlider->sliderPosition();
	pos_s = get_master_clock(ps);
	pos_s += numm;
	stream_seek(ps, (int64_t)(ui.horizontalSlider->sliderPosition() * AV_TIME_BASE), incr);
	incr = 0;
	pos_s = 0;
}

