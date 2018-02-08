//����ͷ���Ž���
#ifndef CAMERA_PLAY_H
#define CAMERA_PLAY_H

#include <QWidget>
#include <string>
#include "ui_camera_play.h"
using namespace std;

class camera_play : public QWidget
{
	Q_OBJECT

public:
	camera_play(QWidget *parent = 0);
	~camera_play();
	void start();
	void closeEvent(QCloseEvent *event);
private:
	
	const char *filter_mirror110 = "crop=iw/2:ih:0:0,split[left][tmp];[tmp]hflip[right]; \[left]pad=iw*2[a];[a][right]overlay=w";
	QString image_filename; //��ӵ�ͼƬ·������
	static void camera_playing(void*);
	string string_filter; //�˾�
	Ui::camera_play ui;
public slots:
	void choice_picture();
	void handle_filter_changed(int);
	void ok();
signals:
	void cam_clear(); //����ͷʹ�����
};

#endif // CAMERA_PLAY_H
