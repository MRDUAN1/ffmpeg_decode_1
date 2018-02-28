//合并音频视频，合并音频对话框
#ifndef MERGE_GUI_H
#define MERGE_GUI_H

#include <QWidget>
#include "ui_merge_gui.h"

class merge_gui : public QWidget
{
	Q_OBJECT

public:
	
	merge_gui(QWidget *parent = 0, int i = 0);
	
	~merge_gui();
	private slots:
	void video_slot();
	void audio_slot();
	void ok();
	void cancel();
private:
	Ui::merge_gui ui;
	QString video_url, audio_url;
	int tt;
};

#endif // MERGE_GUI_H
