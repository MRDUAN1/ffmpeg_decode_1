//界面文件
#ifndef SEPERTE_MUSIC_H
#define SEPERTE_MUSIC_H

#include <QWidget>
#include "ui_seperte_music.h"

class seperte_music : public QWidget
{
	Q_OBJECT

public:
	//i为1分割音频，2分割视频
	seperte_music(QWidget *parent = 0, int i = 0);
	~seperte_music();
	public slots:
	
private:
	Ui::seperte_music ui;
	bool is_first;
	int tt;
	int from, to;
	bool cut_video_parameter();
	QString file_name;
	public slots:
	void cancel();
	void ok();
	void choice_file();
};

#endif // SEPERTE_MUSIC_H
