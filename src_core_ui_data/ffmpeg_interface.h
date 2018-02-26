#ifndef FFMPEG_INTERFACE_H
#define FFMPEG_INTERFACE_H

#include <QtWidgets/QWidget>
#include "ui_ffmpeg_interface.h"

#include <qstring.h>
#include <qtablewidget.h>
#include <qpushbutton.h>
#include <qmenu.h>
#include <qaction.h>
#include <stdint.h>
#include <string>
using std::string;
class ffmpeg_interface : public QWidget
{
	Q_OBJECT

public:
	
	ffmpeg_interface(QWidget *parent = 0);
	void set_separate_widget(QString str);
	void set_progressbar_length(QString input_filrname);
	~ffmpeg_interface();
	void set_video_music_merge(QString video, QString audio, int i = 0);
	void set_cut_music(QString path, int from, int to, int i = 0);
signals:
	void signal_s(QString str);
	void signal_num_all(QString, int);
	void signal_num(QString, int);
private:
	struct clas{
		int64_t now_length;
		string inputName;
	};
	void SetStyle(const QString &styleName);
	void set_common_widget(QString str, QString name);
	void set_common_enable();
	void set_list_widget(int i = 0);
	static void start_picture(QString input_name, QString out_path);
	static void start_transfrom(void *);
	void set_connect();
	void inti_headpiece_button();
	void init_second_pushbutton();
	void make_left_menu();
	Ui::ffmpeg_interfaceClass ui;
	QMenu *task_menu, *help_menu, *skin_menu;
	QAction *task_quit, *task_min, *task_option;
	QAction *help_help, *help_about;
	QAction *skin_navy, *skin_black, *skin_blue, *skin_gray;
	QPushButton *task, *skin, *help, *camera;
	int row_list;
	int row_list_before;
	QMenu *menu;
	QAction *folder;
	QAction *output;
	QAction *delete_action;
	QAction *delete_all;
	int now_row;

	public slots:
	void inform_slot(QString);
	void slot_num_all(QString, int num);
	void slot_num(QString, int);
	void camerapushbutton_clear();
	void SetListWidgetFromPanel(); 
	void camera_slot();
	void output_slot();
	void remove_slot();
	void remove_all_slot();
	void strat_slot();
	void show_menu(const QPoint);
	void cell_click_slot(QTableWidgetItem * item);
	void folder_slot();
	void output_action_slot();
	void delete_action_slot();
	void delete_all_slot();
	
	void progress_update_slot(clas*);
	void quit_action_slot();
	void min_action_slot();
	void option_action_slot();
	void help_action_slot();
	void option_slot();
	static void skin_navy_slot();
	void skin_black_slot();
	void skin_gray_slot();
	void skin_blue_slot();
	void length_all(int64_t);
	void change_once_(int64_t);

};

#endif // FFMPEG_INTERFACE_H
