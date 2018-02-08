#ifndef TOOLBOX_H
#define TOOLBOX_H

#include <QToolBox>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QString>
#include <qdatetime.h>
#include <qtimer.h>
#include <string>
#include <qpushbutton.h>
#include <qgridlayout.h>
# pragma execution_character_set("utf-8")
class toolbox : public QToolBox
{
	Q_OBJECT

public:
	enum type
	{
		merge_video_audio,
		merge_audio
	};
	toolbox(QWidget *parent);
	~toolbox();

private:
	QGroupBox *video;
	QGroupBox *sound;
	QGroupBox *photograph;
	QGroupBox *other;
	QPushButton *video_button_1, *video_button_2, *video_button_3, *video_button_4, *video_button_5, *video_button_6, *video_button_7, *video_button_8, *video_button_9;
	QPushButton *audio_button_1, *audio_button_2, *audio_button_3, *audio_button_4, *audio_button_5, *audio_button_6, *audio_button_7, *audio_button_8, *audio_button_9;
	QPushButton *photo_button_1, *photo_button_2, *photo_button_3, *photo_button_4, *photo_button_5, *photo_button_6, *photo_button_7, *photo_button_8, *photo_button_9;
	QPushButton *other_button_1, *other_button_2, *other_button_3, *other_button_4, *other_button_5, *other_button_6, *other_button_7, *other_button_8, *other_button_9;
	QGridLayout *videos, *sounds, *photographs, *others;
	void create_layout();
	void set_connect();
	
	enum video_form{
		avi,
		tgp,
		mkv,
		mp4,
		flv,
		mov,
		mpg,
		wmv
	};
	video_form form_video;
	enum audio_form{
		mp3,
		wma,
		flac,
		aac,
		m4a,
		ogg,
		mp2
	};
	audio_form form_audio;
	enum picture_form{
		jpeg,
		png,
		ico,
		bmp
	};
	picture_form form_picture;
	public slots:
	void transform_audio();
	void transform_video();
	void transform_picture();
	void init_map_button_list();
	void separate_video();
	void merge_video();
	void merge_audio_();
	void merge_music();
	void cut_video();
	void merge_videos();
	void cut_video_();
};

#endif // TOOLBOX_H
