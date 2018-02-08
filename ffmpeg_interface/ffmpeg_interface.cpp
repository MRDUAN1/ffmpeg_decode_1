#include "ffmpeg_interface.h"
#include "merge_music__.h"
#include "toolbox.h"
#include "global.h"
#include "cut_video__.h"
#include "decode_transform_video.h"
#include "transform_panel.h"
#include "decodec_higher.h"
#include "system_tray.h"
#include "camera_play.h"
#include "separate.h"
#include "separate__.h"
#include "merge_audio.h"
#include "camera_specifics.h"
#include "cut_video_2.h"
#include "merge_vides_.h"
#include "cut_video_2.h"
#include <vector>
#include <qfile.h>
#include <qapplication.h>
#include <qdesktopwidget.h>
#include <qcolor.h>
#include <qpalette.h>
#include <qprogressbar.h>
#include <qprocess.h>
#include <process.h>
#include <qmessagebox.h>
#include <qfile.h>
#include <qimage.h>
#include <qdatetime.h>
#include <QMetaType>
#include <qdesktopservices.h>
using std::string;

static QTableWidget *table;
static void set_maxvalue(QString str, int64_t i);
static void setvalue(QString, int64_t);
static vector<panel_list_data*>list_data_copy;
# pragma execution_character_set("utf-8")
/**************全局变量**************/
QString outPutPath;
ffmpeg_interface *interface_;
/**************全局变量**************/
void ffmpeg_interface::set_separate_widget(QString str)
{
	
}
void ffmpeg_interface::set_cut_music(QString path, int from, int to, int i)
{
	panel_list_data *pal = new panel_list_data;
	pal->is_failure = false;
	pal->is_over = false;
	pal->is_picture = false;
	pal->is_separate = false;
	pal->is_merge_audio = false;
	if (i == 0)
	{
		pal->is_merge_music = true;
		pal->is_cut_video = false;
		pal->audio_path = path;
		pal->is_cut_video = false;
	}
	else if (i == 1)
	{
		//分割
		pal->is_merge_music = false;
		pal->is_cut_video_2 = true;
		pal->cut_video = path;
		pal->is_cut_video = false;
	}
	else if (i == 2)
	{
		//截取
		pal->is_merge_music = false;
		pal->is_cut_video = true;
		pal->is_cut_video_2 = false;
		pal->cut_video = path;
	}
	//is_cut_video 截取
	pal->is_merge_video = false;
	pal->merge_videos = false;
	pal->from = from;
	pal->to = to;
	set_common_enable();
	pal->audio_path = path;
	if (i == 0)
		set_common_widget(path, "分割音频");
	else if (i == 1)
		set_common_widget(path, "分割视频");
	else set_common_widget(path, "剪贴视频");
	list_data_copy.push_back(pal);
}
void ffmpeg_interface::start_picture(QString input_name_, QString out_path)
{
	emit interface_->signal_num_all(input_name_, 100);
	QImage image(input_name_);
	image.save(out_path);
	emit interface_->signal_num(input_name_, 100);
}
void ffmpeg_interface::slot_num_all(QString name ,int num)
{
	set_maxvalue(name, num);
}
void ffmpeg_interface::slot_num(QString name, int num)
{
	QString str = name;
	QList<QTableWidgetItem*>it = table->findItems(str, 0);
	QTableWidgetItem* ii = it.front();
	int row = ii->row();
	QProgressBar *bar = (QProgressBar *)table->cellWidget(row, 3);
	bar->setValue(num);
	if ((100 - num) < 5000)
		bar->setValue(100);
}
void ffmpeg_interface::start_transfrom(void *num)
{
	QString str_information;
	bool is_special = false;
	int i = *(int*)num;
	delete num;
	if (list_data_copy[i]->is_over) return;
	if (list_data_copy[i]->is_failure)
	{
		str_information = "存在失败的转换,将跳过转换";
		emit interface_->signal_s(str_information);
		return;
	}
	if (list_data_copy[i]->is_merge_music)
	{
		//音频分割
		merge_music__ *music = new merge_music__;
		qRegisterMetaType<int64_t>("int64_t");
		music->set_file(list_data_copy[i]->audio_path, list_data_copy[i]->from, list_data_copy[i]->to);
		if (!music->start())
		{
			list_data_copy[i]->is_failure = true;
			str_information = "存在失败的转换,将跳过转换";
			emit interface_->signal_s(str_information);
			return;
		}
		list_data_copy[i]->is_over = true;
		return;
	}
	if (list_data_copy[i]->is_merge_video)
	{
		separate *sep = new separate(0);
		sep->set_filename(list_data_copy[i]->audio_url, list_data_copy[i]->video_url);
		if (!sep->start())
		{
			list_data_copy[i]->is_failure = true;
			QMessageBox::warning(0, "警告", list_data_copy[i]->video_url + "转换失败");
			return;
		}
		list_data_copy[i]->is_over = true;
		return;
	}
	if (list_data_copy[i]->is_separate)
	{
		separate__ *sep = new separate__;
		sep->set_filename(list_data_copy[i]->full_name, list_data_copy[i]->file_name);
		if (sep->start())
		{
			list_data_copy[i]->is_over = true;
		}
		else list_data_copy[i]->is_over = false;
		return;
	}
	if (list_data_copy[i]->is_merge_audio)
	{
		merge_audio *audio = new merge_audio(0);
		audio->set_file(list_data_copy[i]->audio_path_1, list_data_copy[i]->audio_path_2);
		audio->start();
		list_data_copy[i]->is_over = true;
		return;
	}
	if (list_data_copy[i]->is_cut_video)
	{
		//截取视频截取某一段视频
		cut_video_2 *video = new cut_video_2(0);
		video->set_filename(list_data_copy[i]->audio_path, list_data_copy[i]->from, list_data_copy[i]->to);
		video->start();
		list_data_copy[i]->is_over = true;
		return;
	}
	if (list_data_copy[i]->merge_videos)
	{
		merge_vides_ *merg = new merge_vides_(0);
		merg->set_filename(list_data_copy[i]->video_url, list_data_copy[i]->audio_url);
		merg->start();
		list_data_copy[i]->is_over = true;
		return;

	}
	else if (list_data_copy[i]->is_cut_video_2)
	{
		//分割视频
		cut_video__ *cut = new cut_video__(0);
		cut->set_file_name(list_data_copy[i]->cut_video, list_data_copy[i]->from, list_data_copy[i]->to);
		cut->start();
		list_data_copy[i]->is_over = true;
		return;
	}
	decode_transform_video *tran = new decode_transform_video;
	QString out_put__ = outPutPath + "/" + list_data_copy[i]->file_name;
	int h = out_put__.lastIndexOf(".");
	int all = out_put__.size();
	int h1 = all - h - 1;
	QString before = out_put__.right(h1);
	QString st = list_data_copy[i]->format.toLower();
	QByteArray ba = st.toLatin1();
	char *mm = ba.data();
	
	QString s = out_put__.replace(before, st.toLower());
	QString input = table->item(i, 1)->text();
	string iii = input.toLocal8Bit().data();
	if (!(global::return_decode_detail().find(iii) == global::return_decode_detail().end()))
	{
		delete tran;
		is_special = true;
		goto higher;
	}
	if (!strcmp(mm, "jpeg") || !strcmp(mm, "png") || !strcmp(mm, "bmp") || !strcmp(mm, "ico"))
	{
		start_picture(input, out_put__);
		list_data_copy[i]->is_over = true;
		return;
	}
	tran->get_input(input, out_put__);
	int hh = tran->start();

	if (hh != 0)
	{
		goto higher;
	}
	else
	{
		list_data_copy[i]->is_over = true;
		delete tran;
		return;
	}
	return;
higher:
	if (!is_special)
	{
		str_information = "快速转码失败,将尝试慢转码\n时间可能较慢,请耐心等待";
		emit interface_->signal_s("快速转码失败,将尝试慢转码\n时间可能较慢,请耐心等待");
	}
	decodec_higher *hi = new decodec_higher;
	hi->get_input(input, out_put__);
	if (!hi->start())
	{
		list_data_copy[i]->is_over = true;
	}
	return;
}
float io;
void setvalue(QString str, int64_t i)
{
	QList<QTableWidgetItem*>it = table->findItems(str, 0);
	QTableWidgetItem* ii = it.front();
	int row = ii->row();
	QProgressBar *bar = (QProgressBar *)table->cellWidget(row, 3);
	float all = bar->maximum();
	bar->setValue(i);
	float h = i / all;
	if (h >= 0.99)
		bar->setValue(all);
	
}
void set_maxvalue(QString str, int64_t i)
{
	QList<QTableWidgetItem*> it = table->findItems(str, Qt::MatchExactly);
	if (it.size() > 1 || it.size() == 0)
 		return;
	QTableWidgetItem* itt = it.front();
	int row = itt->row();
	QProgressBar *bar = (QProgressBar*)table->cellWidget(row, 3);
	bar->setMinimum(0);  // 最小值
	if (i == 0) i = 1;
	bar->setMaximum(i);  // 最大值
	bar->setValue(0);
	bar->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
}
/***************可优化***********************/
static int h = 0, pre_h;
int first = 0;
void ffmpeg_interface::length_all(int64_t i)
{
	QObject *obj = sender();
	QString str;
	commom_signal *sig = dynamic_cast<commom_signal*>(obj);
	sig->get_file_name(str);
	set_maxvalue(str, i);
	return;
}
void ffmpeg_interface::change_once_(int64_t i)
{
	QObject *obj = sender();
	QString str;
	if (obj == NULL) return;
	commom_signal *sig = dynamic_cast<commom_signal*>(obj);
	sig->get_file_name(str);
	setvalue(str, i);
	return;
}
ffmpeg_interface::ffmpeg_interface(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(this, SIGNAL(signal_s(QString str)), this, SLOT(inform_slot(QString)), Qt::QueuedConnection);
	qRegisterMetaType<int64_t>("int64_t");
	this->setFixedSize(1000, 600);
	toolbox *tool = new toolbox(this);
	tool->move(10, 73);
	table = new QTableWidget(this);
	table->move(330, 70);
	table->resize(670, 630);
	table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	table->setColumnCount(6);
	QStringList m_header;
	m_header <<  QString("文件名") << QString("来源") << QString("大小") << QString("转换状态") << QString("输出") << QString("大小");
	table->setHorizontalHeaderLabels(m_header);
	inti_headpiece_button();
	interface_ = this;
	row_list = 0;
	row_list_before = 0;
	set_connect();
	table->setSelectionBehavior(QAbstractItemView::SelectRows);
	table->setSelectionMode(QAbstractItemView::SingleSelection);
	table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	table->setContextMenuPolicy(Qt::CustomContextMenu);
	make_left_menu();
	outPutPath = "E:/outPut";
	QDir *temp = new QDir;
	bool exist = temp->exists(outPutPath);
	if (!exist)
		bool ok = temp->mkdir(outPutPath);
	system_tray *st = new system_tray;
}
void ffmpeg_interface::inform_slot(QString str)
{
	QMessageBox::warning(NULL, "警告", str);
}
void ffmpeg_interface::make_left_menu()
{
	menu = new QMenu(table);
	folder = new QAction("打开源文件夹", table);
	connect(folder, SIGNAL(triggered()), this, SLOT(folder_slot()));
	output = new QAction("打开输出文件夹", table);
	connect(output, SIGNAL(triggered()), this, SLOT(output_action_slot()));
	delete_action = new QAction("删除任务", table);
	connect(delete_action, SIGNAL(triggered()), this, SLOT(delete_action_slot()));
	delete_all = new QAction("清空列表", table);
	connect(delete_all, SIGNAL(triggered()), this, SLOT(delete_all_slot()));
	menu->addAction(folder);
	menu->addAction(output);
	menu->addAction(delete_action);
	menu->addAction(delete_all);
}
void ffmpeg_interface::folder_slot()
{
	QString file_dir = table->item(now_row, 1)->text();
	QFileInfo fi(file_dir);
	if (file_dir.isNull())
		return;
	QDesktopServices::openUrl(QUrl(fi.absoluteDir().path(), QUrl::TolerantMode));
}
void ffmpeg_interface::output_action_slot()
{
	QDesktopServices::openUrl(QUrl(outPutPath, QUrl::TolerantMode));
}
void ffmpeg_interface::delete_action_slot()
{
	int i = table->currentRow();
	table->removeRow(i);
	row_list--;
	row_list_before--;
}
void ffmpeg_interface::delete_all_slot()
{
	table->clear();
}
void ffmpeg_interface::skin_navy_slot()
{
	
	QFile file("./navy.css");
	file.open(QFile::ReadOnly);
	QString qss = QLatin1String(file.readAll());
	qApp->setStyleSheet(qss);
	qApp->setPalette(QPalette(QColor("#F0F0F0")));
}
void ffmpeg_interface::skin_black_slot()
{
	QFile file("./black.css");
	file.open(QFile::ReadOnly);
	QString qss = QLatin1String(file.readAll());
	qApp->setStyleSheet(qss);
	//qApp->setPalette(QPalette(QColor("#F0F0F0")));
	file.close();
}
void ffmpeg_interface::camera_slot()
{
	camera->setEnabled(false);
	camera_play *cam = new camera_play;
	cam->show();
	cam->start();
}
void ffmpeg_interface::set_connect()
{
	connect(camera, SIGNAL(clicked()), this, SLOT(camera_slot()));
	connect(skin_blue, SIGNAL(triggered()), this, SLOT(skin_blue_slot()));
	connect(skin_gray, SIGNAL(triggered()), this, SLOT(skin_gray_slot()));
	connect(skin_navy, SIGNAL(triggered()), this, SLOT(skin_navy_slot()));
	connect(skin_black, SIGNAL(triggered()), this, SLOT(skin_black_slot()));
	connect(task_quit, SIGNAL(triggered()), this, SLOT(quit_action_slot()));
	connect(task_min, SIGNAL(triggered()), this, SLOT(min_action_slot()));
	connect(task_option, SIGNAL(triggered()), this, SLOT(option_action_slot()));
	connect(help_help, SIGNAL(triggered()), this, SLOT(help_action_slot()));
	connect(ui.OPTION, SIGNAL(clicked()), this, SLOT(option_slot()));
	connect(table, SIGNAL(QTableWidget::itemChanged(QTableWidgetItem * item)), this, SLOT(cell_click_slot(QTableWidgetItem * item)));
	connect(ui.OUT_PUT, SIGNAL(clicked()), this, SLOT(output_slot()));
	connect(ui.REMOVE, SIGNAL(clicked()), this, SLOT(remove_slot()));
	connect(ui.REMOVE_ALL, SIGNAL(clicked()), this, SLOT(remove_all_slot()));
	connect(ui.START, SIGNAL(clicked()), this, SLOT(strat_slot()));
	connect(table, SIGNAL(customContextMenuRequested(const QPoint)), this, SLOT(show_menu(const QPoint)));
	ui.REMOVE->setEnabled(false);
	ui.REMOVE_ALL->setEnabled(false);
	ui.START->setEnabled(false);
}


void ffmpeg_interface::quit_action_slot()
{
	this->close();
}
void ffmpeg_interface::min_action_slot()
{
	this->showMinimized();

}
void ffmpeg_interface::option_action_slot()
{

}
void ffmpeg_interface::help_action_slot()
{

}
void ffmpeg_interface::option_slot()
{

}
void ffmpeg_interface::cell_click_slot(QTableWidgetItem * item)
{
	exit(0);
	printf("djg");
}
void ffmpeg_interface::show_menu(const QPoint pose)
{
	now_row = table->indexAt(pose).row();
	menu->move(cursor().pos());
	menu->exec();
	
}
void ffmpeg_interface::set_common_enable()
{
	QPalette paletee = ui.REMOVE_ALL->palette();
	paletee.setColor(QPalette::ButtonText, QColor(0, 0, 0));
	ui.REMOVE_ALL->setPalette(paletee);
	ui.START->setPalette(paletee);
	ui.REMOVE_ALL->setEnabled(true);
	ui.START->setEnabled(true);
}
void ffmpeg_interface::set_video_music_merge(QString video, QString audio, int i)
{
	QString str;
	set_common_enable();
	if (i == 0) str = "合并音视频";
	else if (i == 1) str = "合并音频";
	else if (i == 3) str = "合并视频";
	set_common_widget(video, str);
	panel_list_data *temp = new panel_list_data;
	temp->is_over = false;
	temp->is_failure = false;
	temp->is_picture = false;
	temp->is_separate = false;
	temp->is_merge_music = false;
	temp->is_cut_video = false;
	if (i == 0)
	{
		temp->is_merge_video = true;
		temp->is_merge_audio = false;
		temp->audio_url = audio;
		temp->video_url = video;
	}
	else if (i == 1)
	{
		temp->is_merge_audio = true;
		temp->is_merge_video = false;
		temp->audio_path_1 = video;
		temp->audio_path_2 = audio;
	}
	else  if (i == 3)
	{
		temp->merge_videos = true;
		temp->is_merge_audio = false;
		temp->is_merge_video = false;
		temp->audio_url = audio;
		temp->video_url = video;
	}
	
	list_data_copy.push_back(temp);
}
void ffmpeg_interface::set_list_widget(int j)
{
	bool is_pictures = global::return_panel_list_data()[j]->is_picture;
	table->setRowCount(++row_list_before);
	panel_list_data *ro = global::return_panel_list_data()[j];
	QString fileName = ro->full_name;
	QTableWidgetItem *filename = new QTableWidgetItem(ro->file_name);
	table->setItem(row_list, 0, filename);
	table->setToolTip(ro->file_name);
	QTableWidgetItem *name_item = new QTableWidgetItem(fileName);
	name_item->setToolTip(fileName);
	table->setItem(row_list, 1, name_item);
	QString fileDir = ro->file_dir;
	QTableWidgetItem *dir_item = new QTableWidgetItem(fileDir);
	dir_item->setToolTip(fileDir);
	table->setItem(row_list, 2, dir_item);
	QString fileTime_ = ro->format;
	QTableWidgetItem *time_item = new QTableWidgetItem(fileTime_);
	QProgressBar *progressbar = new QProgressBar(this);
	progressbar->setStyleSheet("QProgressBar{background:transparent;border-radius: 5px;} QProgressBar::chunk{background-color:rgb(210,233,247,180);}");
	table->setCellWidget(row_list, 3, progressbar);
	//QWidget *wi = table->cellWidget(row_list, 0);
	time_item->setToolTip(fileTime_);
	table->setItem(row_list, 3, time_item);
	QString fileSize = ro->size;
	QTableWidgetItem *size_item = new QTableWidgetItem(fileSize);
	size_item->setToolTip(fileSize);
	table->setItem(row_list, 2, size_item);
	QTableWidgetItem *out_put_item = new QTableWidgetItem(outPutPath);
	out_put_item->setToolTip(outPutPath);
	table->setItem(row_list, 4, out_put_item);
	row_list++;
	set_common_enable();
	ro->is_failure = false;
	ro->is_over = false;
	ro->is_merge_music = false;
	ro->is_merge_video = false;
	ro->is_picture = false;
	if (!ro->is_separate)
		ro->is_separate = false;
	else
		ro->is_separate = true;
	ro->is_merge_audio = false;
	ro->is_cut_video = false;
	ro->is_cut_video_2 = false;
	ro->merge_videos = false;
	list_data_copy.push_back(ro);
	global::return_panel_list_data().clear();
}
void ffmpeg_interface::SetListWidgetFromPanel()
{
	int i = global::return_panel_list_data().size();
	if (i == 0) return;
	for (int j = 0; j < i; j++)
	{
		set_list_widget(j);
	}
	
}
ffmpeg_interface::~ffmpeg_interface()
{

}
void ffmpeg_interface::inti_headpiece_button()
{
	task_menu = new QMenu(this);
	help_menu = new QMenu(this);
	skin_menu = new QMenu(this);
	task_quit = new QAction(task_menu);
	task_menu->addAction(task_quit);
	task_quit->setText("退出");
	task_min = new QAction(task_menu);
	task_min->setText("最小化到托盘");
	task_menu->addAction(task_min);
	task_option = new QAction(task_menu);
	task_option->setText("选择");
	task_menu->addAction(task_option);
	help_help = new QAction(help_menu);
	help_help->setText("帮助");
	help_menu->addAction(help_help);
	help_about = new QAction(help_menu);
	help_about->setText("关于");
	help_menu->addAction(help_about);
	skin_navy = new QAction(skin_menu);
	skin_navy->setText("深蓝色");
	skin_menu->addAction(skin_navy);
	skin_blue = new QAction(skin_menu);
	skin_blue->setText("蓝色");
	skin_menu->addAction(skin_blue);
	skin_gray = new QAction(skin_menu);
	skin_menu->addAction(skin_gray);
	skin_gray->setText("灰色");
	skin_black = new QAction(skin_menu);
	skin_black->setText("黑色");
	skin_menu->addAction(skin_black);
	task = new QPushButton(this);
	task->setMenu(task_menu);
	task->setFont(QFont("Times", 9, QFont::Light));
	task->setContentsMargins(0, 0, 0, 0);
	task->setStyleSheet("QPushButton::menu-indicator{image:none;} QPushButton:pressed{background-color:rgb(255,255,255);} QPushButton{background-color:rgb(255,255,255); border:none;} QPushButton:hover{background-color:rgb(216,216,216);border:none;}");
	task->setText("任务");
	//help = new QPushButton(this);
	//help->setStyleSheet("QPushButton::menu-indicator{image:none;} QPushButton:pressed{background-color:rgb(255,255,255);} QPushButton{background-color:rgb(255,255,255); border:none;} QPushButton:hover{background-color:rgb(216,216,216);border:none;}");
	help = new QPushButton(this);
	help->setMenu(help_menu);
	help->setText("帮助");
	help->setStyleSheet("QPushButton::menu-indicator{image:none;} QPushButton:pressed{background-color:rgb(255,255,255);} QPushButton{background-color:rgb(255,255,255); border:none;} QPushButton:hover{background-color:rgb(216,216,216);border:none;}");
	skin = new QPushButton(this);
	skin->setMenu(skin_menu);
	skin->setText("皮肤");
	//help->setStyleSheet("QPushButton::menu-indicator{image:none;}");
	skin->setStyleSheet("QPushButton::menu-indicator{image:none;} QPushButton:pressed{background-color:rgb(255,255,255);} QPushButton{background-color:rgb(255,255,255); border:none;} QPushButton:hover{background-color:rgb(216,216,216);border:none;}");
	task->move(5, 2);
	task->setGeometry(5, 2, 70, 25);
	task->setIcon(QIcon("./mp4.jpg"));
	QPalette p = task->palette();
	p.setBrush(QPalette::Button, QBrush(QPixmap("rmvb.png")));
	task->setPalette(p);
	skin->setGeometry(100, 2, 70, 25);
	help->setGeometry(195, 2, 70, 25);
	ui.OUT_PUT->setText("输出文件");
	ui.OPTION->setText("选项");
	ui.REMOVE->setText("移除");
	QPalette palette = ui.REMOVE->palette();
	palette.setColor(QPalette::ButtonText, QColor(162, 162, 162));
	ui.REMOVE->setPalette(palette);
	ui.REMOVE_ALL->setText("移除全部");
	ui.REMOVE_ALL->setPalette(palette);
	ui.START->setText("转换开始");
	ui.START->setPalette(palette);
	camera = new QPushButton(this);
	camera->setGeometry(290, 2, 70, 25);
	camera->setText("摄像头");
	camera->setStyleSheet("QPushButton::menu-indicator{image:none;} QPushButton:pressed{background-color:rgb(255,255,255);} QPushButton{background-color:rgb(255,255,255); border:none;} QPushButton:hover{background-color:rgb(216,216,216);border:none;}");
}
static void SetStyle(const QString &styleName)
{
	QFile file(QString("./%1.css").arg(styleName));
	file.open(QFile::ReadOnly);
	QString qss = QLatin1String(file.readAll());
	qApp->setStyleSheet(qss);
	qApp->setPalette(QPalette(QColor("#F0F0F0")));
}

void ffmpeg_interface::output_slot()
{
	outPutPath = QFileDialog::getExistingDirectory(this, "重新设置目录", "./");
}
void ffmpeg_interface::remove_slot()
{
	int rowIndex = table->currentRow();
	QTableWidgetItem *item = table->item(rowIndex, 0);
	QString str = item->text();
	
	if (rowIndex != -1)
	{
		table->removeRow(rowIndex);
		row_list--;
		row_list_before--;
	}
	if (row_list == 0)
	{
		QPalette paletee = ui.REMOVE->palette();
		paletee.setColor(QPalette::ButtonText, QColor(162, 162, 162));
		ui.REMOVE_ALL->setPalette(paletee);
		ui.START->setPalette(paletee);
		ui.REMOVE->setPalette(paletee);
		ui.REMOVE_ALL->setEnabled(true);
		ui.START->setEnabled(false);
		ui.REMOVE->setEnabled(false);
	}
}
void ffmpeg_interface::remove_all_slot()
{
	table->clear();
	row_list = 0;
	row_list_before = 0;
	global::return_panel_list_data().clear();
	list_data_copy.clear();
}
void ffmpeg_interface::strat_slot()
{
	
	//int count = table->rowCount();
	int count = list_data_copy.size();
	for (int i = 0; i < count; i++)
	{
		int *hh = new int;
		*hh = i;
		_beginthread(start_transfrom, 0, hh);
	}
}
void ffmpeg_interface::set_progressbar_length(QString input_filename)
{
	QList<QTableWidgetItem*> it = table->findItems(input_filename, Qt::MatchExactly);
	if (it.size() > 1 || it.size() == 0)
		return;
	QTableWidgetItem* itt = it.front();
	int row = itt->row();
	QProgressBar *bar = (QProgressBar*)table->cellWidget(row, 3);
	bar->setMinimum(0);  // 最小值
	bar->setMaximum(100);  // 最大值
	bar->setValue(0);
	bar->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	int64_t tt = bar->maximum();
}
void ffmpeg_interface::progress_update_slot(clas* cl)
{
	QString str = QString::fromLocal8Bit(cl->inputName.data());
	QList<QTableWidgetItem*>it = table->findItems(str, 0);
	QTableWidgetItem* ii = it.front();
	int row = ii->row();
	QProgressBar *bar = (QProgressBar *)table->cellWidget(row, 3);
	bar->setValue(cl->now_length);
}
void ffmpeg_interface::skin_gray_slot()
{
	QFile file("./gray.css");
	file.open(QFile::ReadOnly);
	QString qss = QLatin1String(file.readAll());
	qApp->setStyleSheet(qss);
	qApp->setPalette(QPalette(QColor("#F0F0F0")));
}
void ffmpeg_interface::skin_blue_slot()
{
	QFile file("./blue.css");
	file.open(QFile::ReadOnly);
	QString qss = QLatin1String(file.readAll());
	qApp->setStyleSheet(qss);
	qApp->setPalette(QPalette(QColor("#F0F0F0")));
}
void ffmpeg_interface::set_common_widget(QString path, QString name)
{
	table->setRowCount(++row_list_before);
	QTableWidgetItem *filename = new QTableWidgetItem(path);
	table->setItem(row_list, 0, filename);
	QTableWidgetItem *com = new QTableWidgetItem(name);
	table->setItem(row_list, 1, com);
	QTableWidgetItem *size = new QTableWidgetItem(name);
	table->setItem(row_list, 2, size);
	QTableWidgetItem *state = new QTableWidgetItem(name);
	table->setItem(row_list, 3, state);
	QTableWidgetItem *output = new QTableWidgetItem(outPutPath);
	table->setItem(row_list, 4, output);
	QProgressBar *progressbar = new QProgressBar(this);
	progressbar->setStyleSheet("QProgressBar{background:transparent;border-radius: 5px;} QProgressBar::chunk{background-color:rgb(210,233,247,180);}");
	table->setCellWidget(row_list, 3, progressbar);
	row_list++;
}
void ffmpeg_interface::camerapushbutton_clear()
{
	camera->setEnabled(true);
}
