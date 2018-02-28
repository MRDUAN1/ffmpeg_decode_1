#include "toolbox.h"
#include "ffmpeg_interface.h"
#include "merge_gui.h"
#include "global.h"
#include "seperte_music.h"
#include <qtoolbox.h>
#include <qpixmap.h>
#include <qicon.h>
#include <qsize.h>
#include <qpalette.h>
#include <map>
#include <vector>
#include <qfiledialog.h>
#include "transform_panel.h"
static std::map<QPushButton*, QString>button_string; //按钮和转码格式名称的映射
extern ffmpeg_interface *interface_;
toolbox::toolbox(QWidget *parent)
	: QToolBox(parent)
{
	this->resize(300, 500);
	video = new QGroupBox;
	video->setStyleSheet("background-color:rgb(255, 255, 252)");
	sound = new QGroupBox;
	sound->setStyleSheet("background-color:rgb(255, 255, 252)");
	photograph = new QGroupBox;
	photograph->setStyleSheet("background-color:rgb(255, 255, 252)");
	other = new QGroupBox;
	other->setStyleSheet("background-color:rgb(255, 255, 252)");
	videos = new QGridLayout(video);
	sounds = new QGridLayout(sound);
	photographs = new QGridLayout(photograph);
	others = new QGridLayout(other);
	this->addItem((QWidget*)video, tr("视频"));
	this->addItem((QWidget*)sound, tr("音频"));
	this->addItem((QWidget*)photograph, tr("图片"));
	this->addItem((QWidget*)other, tr("其他"));
	this->setStyleSheet("QToolBox::tab {background:rgb(255,255,255);color: black;}"
		"QToolBox::tab:hover {font: italic;color: black; background-color:rgb(216,216,216);}"
		"QToolBox{ border-width:1px; border-style:rgb(255, 255, 252); border-top-color:rgb(255, 255, 255); }");
	create_layout();
	set_connect();
	init_map_button_list();
}
void toolbox::create_layout()
{
	video_button_1 = new QPushButton();
	video_button_1->setFixedSize(90, 90);
	video_button_1->setIcon(QPixmap("./imag/avi.png"));
	video_button_1->setIconSize(QSize(80, 80));
	video_button_2 = new QPushButton();
	video_button_2->setFixedSize(90, 90);
	video_button_2->setIcon(QPixmap("./imag/tgp.png"));
	video_button_2->setIconSize(QSize(80, 80));
	video_button_3 = new QPushButton();
	video_button_3->setFixedSize(90, 90);
	video_button_3->setIcon(QPixmap("./imag/MKV.png"));
	video_button_3->setIconSize(QSize(80, 80));
	video_button_4 = new QPushButton();
	video_button_4->setFixedSize(90, 90);
	video_button_4->setIcon(QPixmap("./imag/12.png"));
	video_button_4->setIconSize(QSize(80, 80));
	video_button_5 = new QPushButton();
	video_button_5->setFixedSize(90, 90);
	video_button_5->setIcon(QPixmap("./imag/flv.png"));
	video_button_5->setIconSize(QSize(80, 80));
	video_button_6 = new QPushButton();
	video_button_6->setFixedSize(90, 90);
	video_button_6->setIcon(QPixmap("./imag/mov.png"));
	video_button_6->setIconSize(QSize(80, 80));
	video_button_7 = new QPushButton();
	video_button_7->setFixedSize(90, 90);
	video_button_7->setIcon(QPixmap("./imag/mpg.png"));
	video_button_7->setIconSize(QSize(80, 80));
	video_button_8 = new QPushButton();
	video_button_8->setFixedSize(90, 90);
	video_button_8->setIcon(QPixmap("./imag/wmv.png"));
	video_button_8->setIconSize(QSize(80, 80));
	video_button_9 = new QPushButton();
	video_button_9->setFixedSize(90, 90);
	video_button_9->setIcon(QPixmap("./imag/12.jpg"));
	video_button_9->setIconSize(QSize(80, 80));
	audio_button_1 = new QPushButton();
	audio_button_1->setFixedSize(90, 90);
	audio_button_1->setIcon(QPixmap("./imag/mp33.png"));
	audio_button_1->setIconSize(QSize(80, 80));
	audio_button_2 = new QPushButton();
	audio_button_2->setFixedSize(90, 90);
	audio_button_2->setIcon(QPixmap("./imag/wma.png"));
	audio_button_2->setIconSize(QSize(80, 80));
	audio_button_3 = new QPushButton();
	audio_button_3->setFixedSize(90, 90);
	audio_button_3->setIcon(QPixmap("./imag/flac.png"));
	audio_button_3->setIconSize(QSize(80, 80));
	audio_button_4 = new QPushButton();
	audio_button_4->setFixedSize(90, 90);
	audio_button_4->setIcon(QPixmap("./imag/aac.png"));
	audio_button_4->setIconSize(QSize(80, 80));
	audio_button_5 = new QPushButton();
	audio_button_5->setFixedSize(90, 90);
	audio_button_5->setIcon(QPixmap("./imag/m4a.png"));
	audio_button_5->setIconSize(QSize(80, 80));
	audio_button_6 = new QPushButton();
	audio_button_6->setFixedSize(90, 90);
	audio_button_6->setIcon(QPixmap("./imag/ogg.png"));
	audio_button_6->setIconSize(QSize(80, 80));
	audio_button_7 = new QPushButton();
	audio_button_7->setFixedSize(90, 90);
	//audio_button_7->setIcon(QPixmap("./avi.png")); //mp2
	//audio_button_7->setIconSize(QSize(80, 80));
	audio_button_8 = new QPushButton();
	audio_button_8->setFixedSize(90, 90);
	//audio_button_8->setIcon(QPixmap("./avi.png"));
	//audio_button_8->setIconSize(QSize(80, 80));
	audio_button_9 = new QPushButton();
	audio_button_9->setFixedSize(90, 90);
	audio_button_1->setIcon(QPixmap("./mp33.png"));
	audio_button_1->setIconSize(QSize(80, 80));
	photo_button_1 = new QPushButton();
	photo_button_1->setFixedSize(90, 90);
	photo_button_1->setStyleSheet("QPushButton{background-color:green;\
								  	color:white; border-radius:10px; border:2px groove gray; \
									border - style: outset; }"
									"QPushButton:hover{background-color:white; color: black;}"
									"QPushButton:pressed{background-color:rgb(85, 170, 255);\
											   border - style: inset; }"
											   );
	//photo_button_1->setIcon(QPixmap("./JPG.png"));
	//photo_button_1->setIconSize(QSize(80, 80));
	photo_button_1->setText("jpg");
	photo_button_2 = new QPushButton();
	photo_button_2->setStyleSheet("QPushButton{background-color:green;\
								  								  	color:white; border-radius:10px; border:2px groove gray; \
																										border - style: outset; }"
																										"QPushButton:hover{background-color:white; color: black;}"
																										"QPushButton:pressed{background-color:rgb(85, 170, 255);\
																																					   border - style: inset; }"
																																					   );
	photo_button_2->setFixedSize(90, 90);
	//photo_button_2->setIcon(QPixmap("./png.png"));
	//photo_button_2->setIconSize(QSize(80, 80));
	photo_button_2->setText("PNG");
	photo_button_3 = new QPushButton();
	photo_button_3->setStyleSheet("QPushButton{background-color:green;\
								  								  	color:white; border-radius:10px; border:2px groove gray; \
																										border - style: outset; }"
																										"QPushButton:hover{background-color:white; color: black;}"
																										"QPushButton:pressed{background-color:rgb(85, 170, 255);\
																																					   border - style: inset; }"
																																					   );
	photo_button_3->setFixedSize(90, 90);
	//photo_button_3->setIcon(QPixmap("./png.png"));
	//photo_button_3->setIconSize(QSize(80, 80));
	photo_button_3->setText("ICO");
	photo_button_4 = new QPushButton();
	photo_button_4->setStyleSheet("QPushButton{background-color:green;\
								  								  	color:white; border-radius:10px; border:2px groove gray; \
																										border - style: outset; }"
																										"QPushButton:hover{background-color:white; color: black;}"
																										"QPushButton:pressed{background-color:rgb(85, 170, 255);\
																																					   border - style: inset; }"
																																					   );
	photo_button_4->setFixedSize(90, 90);
	photo_button_4->setText("BMP");
	//photo_button_4->setIcon(QPixmap("./bmp.png"));
//	photo_button_4->setIconSize(QSize(80, 80));
	
	other_button_1 = new QPushButton();
	other_button_1->setFixedSize(90, 90);
	other_button_1->setText("视频分离");
	this->other_button_1->setStyleSheet("QPushButton{background-color:green;\
	color:white; border-radius:10px; border:2px groove gray; \
border - style: outset; }"
		   "QPushButton:hover{background-color:white; color: black;}"
		   "QPushButton:pressed{background-color:rgb(85, 170, 255);\
		   border - style: inset; }"
		   );
	other_button_2 = new QPushButton();
	other_button_2->setText("混流");
	this->other_button_2->setStyleSheet("QPushButton{background-color:green;\
											color:white; border-radius:10px; border:2px groove gray; \
											border - style: outset; }"
											"QPushButton:hover{background-color:white; color: black;}"
											"QPushButton:pressed{background-color:rgb(85, 170, 255);\
													   border - style: inset; }"
													   );
	other_button_2->setFixedSize(90, 90);
	other_button_3 = new QPushButton();
	this->other_button_3->setStyleSheet("QPushButton{background-color:green;\
																					color:white; border-radius:10px; border:2px groove gray; \
																																border - style: outset; }"
																																"QPushButton:hover{background-color:white; color: black;}"
																																"QPushButton:pressed{background-color:rgb(85, 170, 255);\
																																													   border - style: inset; }"
																																													   );
	other_button_3->setText("音频分割");
	other_button_3->setFixedSize(90, 90);
	other_button_4 = new QPushButton();
	this->other_button_4->setStyleSheet("QPushButton{background-color:green;\
																					color:white; border-radius:10px; border:2px groove gray; \
																																border - style: outset; }"
																																"QPushButton:hover{background-color:white; color: black;}"
																																"QPushButton:pressed{background-color:rgb(85, 170, 255);\
																																													   border - style: inset; }"
																																													   );
	other_button_4->setText("音频合并");
	other_button_4->setFixedSize(90, 90);
	other_button_5 = new QPushButton();
	this->other_button_5->setStyleSheet("QPushButton{background-color:green;\
																					color:white; border-radius:10px; border:2px groove gray; \
																																border - style: outset; }"
																																"QPushButton:hover{background-color:white; color: black;}"
																																"QPushButton:pressed{background-color:rgb(85, 170, 255);\
																																													   border - style: inset; }"
																																													   );
	other_button_5->setText("视频分割");
	other_button_5->setFixedSize(90, 90);
	other_button_6 = new QPushButton();
	this->other_button_6->setStyleSheet("QPushButton{background-color:green;\
																					color:white; border-radius:10px; border:2px groove gray; \
																																border - style: outset; }"
																																"QPushButton:hover{background-color:white; color: black;}"
																																"QPushButton:pressed{background-color:rgb(85, 170, 255);\
																																													   border - style: inset; }"
																																													   );
	other_button_6->setText("视频合并");
	other_button_6->setFixedSize(90, 90);
	other_button_7 = new QPushButton();
	this->other_button_7->setStyleSheet("QPushButton{background-color:green;\
																																									color:white; border-radius:10px; border:2px groove gray; \
																																																																																																								border - style: outset; }"
																																																																																																								"QPushButton:hover{background-color:white; color: black;}"
																																																																																																								"QPushButton:pressed{background-color:rgb(85, 170, 255);\
																																																																																																																																																																																																																				   border - style: inset; }");

	other_button_7->setFixedSize(90, 90);
	other_button_7->setText("截取视频");
	other_button_8 = new QPushButton();
	other_button_8->setFixedSize(90, 90);
	other_button_9 = new QPushButton();
	other_button_9->setFixedSize(90, 90);
	videos->addWidget(video_button_1, 0, 0);
	videos->addWidget(video_button_2, 0, 1);
	videos->addWidget(video_button_3, 0, 2);
	videos->addWidget(video_button_4, 1, 0);
	videos->addWidget(video_button_5, 1, 1);
	videos->addWidget(video_button_6, 1, 2);
	videos->addWidget(video_button_7, 2, 0);
	videos->addWidget(video_button_8, 2, 1);
	//videos->addWidget(video_button_9, 2, 2);
	sounds->addWidget(audio_button_1, 0, 0);
	sounds->addWidget(audio_button_2, 0, 1);
	sounds->addWidget(audio_button_3, 0, 2);
	sounds->addWidget(audio_button_4, 1, 0);
	sounds->addWidget(audio_button_5, 1, 1);
	sounds->addWidget(audio_button_6, 1, 2);
	sounds->addWidget(audio_button_7, 2, 0);
	sounds->addWidget(audio_button_8, 2, 1);
	sounds->addWidget(audio_button_9, 2, 2);
	photographs->addWidget(photo_button_1, 0, 0);
	photographs->addWidget(photo_button_2, 0, 1);
	photographs->addWidget(photo_button_3, 0, 2);
	photographs->addWidget(photo_button_4, 1, 0);
	others->addWidget(other_button_1, 0, 0);
	others->addWidget(other_button_2, 0, 1);
	others->addWidget(other_button_3, 0, 2);
	others->addWidget(other_button_4, 1, 0);
	others->addWidget(other_button_5, 1, 1);
	others->addWidget(other_button_6, 1, 2);
	others->addWidget(other_button_7, 2, 0);
	others->addWidget(other_button_8, 2, 1);
	others->addWidget(other_button_9, 2, 2);
}
void toolbox::set_connect()
{
	connect(video_button_1, SIGNAL(clicked()), this, SLOT(transform_video()));
	connect(video_button_2, SIGNAL(clicked()), this, SLOT(transform_video()));
	connect(video_button_3, SIGNAL(clicked()), this, SLOT(transform_video()));
	connect(video_button_4, SIGNAL(clicked()), this, SLOT(transform_video()));
	connect(video_button_5, SIGNAL(clicked()), this, SLOT(transform_video()));
	connect(video_button_6, SIGNAL(clicked()), this, SLOT(transform_video()));
	connect(video_button_7, SIGNAL(clicked()), this, SLOT(transform_video()));
	connect(video_button_8, SIGNAL(clicked()), this, SLOT(transform_video()));
	connect(audio_button_1, SIGNAL(clicked()), this, SLOT(transform_audio()));
	connect(audio_button_2, SIGNAL(clicked()), this, SLOT(transform_audio()));
	connect(audio_button_3, SIGNAL(clicked()), this, SLOT(transform_audio()));
	connect(audio_button_4, SIGNAL(clicked()), this, SLOT(transform_audio()));
	connect(audio_button_5, SIGNAL(clicked()), this, SLOT(transform_audio()));
	connect(audio_button_6, SIGNAL(clicked()), this, SLOT(transform_audio()));
	connect(audio_button_7, SIGNAL(clicked()), this, SLOT(transform_audio()));
	//connect(audio_button_8, SIGNAL(clicked()), this, SLOT(transform_audio())); //mp2
	connect(photo_button_1, SIGNAL(clicked()), this, SLOT(transform_picture()));
	connect(photo_button_2, SIGNAL(clicked()), this, SLOT(transform_picture()));
	connect(photo_button_3, SIGNAL(clicked()), this, SLOT(transform_picture()));
	connect(photo_button_4, SIGNAL(clicked()), this, SLOT(transform_picture()));
	//connect(photo_button_5, SIGNAL(clicked()), this, SLOT(avi_handle()));
	//connect(photo_button_6, SIGNAL(clicked()), this, SLOT(avi_handle()));
	//connect(photo_button_7, SIGNAL(clicked()), this, SLOT(avi_handle()));
	//connect(photo_button_8, SIGNAL(clicked()), this, SLOT(avi_handle()));
	connect(other_button_1, SIGNAL(clicked()), this, SLOT(separate_video()));
	connect(other_button_2, SIGNAL(clicked()), this, SLOT(merge_video()));
	connect(other_button_3, SIGNAL(clicked()), this, SLOT(merge_music()));
	connect(other_button_4, SIGNAL(clicked()), this, SLOT(merge_audio_()));
	connect(other_button_5, SIGNAL(clicked()), this, SLOT(cut_video()));
	connect(other_button_6, SIGNAL(clicked()), this, SLOT(merge_videos()));
	connect(other_button_7, SIGNAL(clicked()), this, SLOT(cut_video_()));
}
void toolbox::cut_video_()
{
	seperte_music *video = new seperte_music(0, 2);
	video->show();
}
void toolbox::merge_videos()
{
	merge_gui *gui = new merge_gui(0, 3);
	gui->show();
}
void toolbox::cut_video()
{
	seperte_music *video = new seperte_music(0, 1);
	video->show();
}
void toolbox::merge_audio_()
{
	merge_gui *gui_ = new merge_gui(0, 1);
	gui_->show();
}
toolbox::~toolbox()
{

}
void toolbox::merge_music()
{
	//剪贴音频
	seperte_music *music = new seperte_music;
	music->show();
	
}
void toolbox::merge_video()
{
	merge_gui *gui_ = new merge_gui(0);
	gui_->show();
}
void toolbox::separate_video()
{
	transform_panel *tran = new transform_panel("视音频分离", 0, true);
	tran->show();
	
}
void toolbox::transform_video()
{
	QPushButton *pus =  (QPushButton*)sender();
	auto str = button_string.find(pus);
	QString type = str->second;
	transform_panel *tran = new transform_panel(type);
	tran->show();
	
}
void toolbox::transform_audio()
{
	QPushButton *pus = (QPushButton*)sender();
	auto str = button_string.find(pus);
	QString type = str->second;
	transform_panel *tran = new transform_panel(type);
	tran->show();
}
void toolbox::transform_picture()
{
	QPushButton *pus = (QPushButton*)sender();
	auto str = button_string.find(pus);
	QString type = str->second;
	transform_panel *tran = new transform_panel(type);
	tran->show();
}
void toolbox::init_map_button_list()
{
	button_string[video_button_1] = "AVI";
	button_string[video_button_2] = "3GP";
	button_string[video_button_3] = "MKV";
	button_string[video_button_4] = "MP4";
	button_string[video_button_5] = "FLV";
	button_string[video_button_6] = "MOV";
	button_string[video_button_7] = "MPG";
	button_string[video_button_8] = "WMV";
	button_string[audio_button_1] = "MP3";
	button_string[audio_button_2] = "WMA";
	button_string[audio_button_3] = "FLAC";
	button_string[audio_button_4] = "AAC";
	button_string[audio_button_5] = "m4a";
	button_string[audio_button_6] = "ogg";
	button_string[audio_button_7] = "mp2";
	button_string[photo_button_1] = "jpeg";
	button_string[photo_button_2] = "png";
	button_string[photo_button_3] = "ico";
	button_string[photo_button_4] = "bmp";

	
}
/*enum picture_form{
		jpeg,
		png,
		ico,
		bmp
	};*/
