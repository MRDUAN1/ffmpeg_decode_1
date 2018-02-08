#include "camera_play.h"
#include "camera_specifics.h"
#include "ffmpeg_interface.h"
#include <qfiledialog.h>
#include <qfile.h>
#include <string>
#include <qmessagebox.h>
#include <process.h>
#include <qdatetime.h>
static HWND label_wind;
static camera_specifics *cam_spe;
extern ffmpeg_interface *interface_;
# pragma execution_character_set("utf-8")
static QString fileName;
camera_play::camera_play(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.pushButton_2->setText("��ѡ��ͼƬ");
	ui.label->setStyleSheet("background:rgb(0, 0, 127);");
	label_wind = (HWND)ui.label->winId();
	ui.label_size_caption->setText("��ѡ����Ļ��С");
	ui.label_size_caption->setText("��������Ļ��С");
	ui.label_size_caption->hide();
	//ui.captions_color->hide();
	ui.captions_color->addItem("��ɫ");
	ui.captions_color->addItem("��ɫ");
	ui.captions_color->addItem("��ɫ");
	ui.captions_color->addItem("��ɫ");
	ui.captions_color->addItem("��ɫ");
	//ui.captions_color->addItem("��ɫ");
	ui.label_choice->setText("��Ƶ��Ч");
	ui.filte_choice->addItem("��");
	//ui.filte_choice->addItem("�����Ļ");
	ui.filte_choice->addItem("�ı�ֱ���");
	ui.filte_choice->addItem("�ü���Ƶ");
	ui.filte_choice->addItem("��ת");
	ui.filte_choice->addItem("��Ƶ����");
	ui.filte_choice->addItem("��Ƶ��ɫ");
	ui.filte_choice->addItem("����");
	ui.filte_choice->addItem("�����Ļ");
	ui.filte_choice->addItem("������Ļ");
	ui.filte_choice->addItem("��ת90");
	ui.filte_choice->addItem("��ת180");
	ui.filte_choice->addItem("��ת270");
	ui.filte_choice->addItem("���ˮӡ");
	ui.size_resolution->hide();
	ui.size->hide();
	this->setFixedSize(400, 480);
	ui.pushButton->setText("ȷ��");
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(ok()));
	connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(choice_picture()));
	connect(ui.filte_choice, SIGNAL(currentIndexChanged(int)), this, SLOT(handle_filter_changed(int)));
	connect(this, SIGNAL(cam_clear()), interface_, SLOT(camerapushbutton_clear()));
	ui.label_4->setText("��������Ļ");
	ui.label_5->setText("����������");
	ui.label_6->setText("��ѡ����ɫ");
}
void camera_play::choice_picture()
{
	
	image_filename = QFileDialog::getOpenFileName(0, "��ѡ��ͼƬ");
	QFileInfo fi(image_filename);
	image_filename = fi.fileName();
}
void camera_play::closeEvent(QCloseEvent *event)
{

	QMessageBox::StandardButton button = QMessageBox::question(NULL, "��ʾ", "�Ƿ񱣴���Ƶ");
	if (button == QMessageBox::StandardButton::Yes)
	{
		cam_spe->set_exit();
		//return;
	}
	else if (button == QMessageBox::StandardButton::No)
	{
		cam_spe->set_exit();
		Sleep(100);
		QFile::remove(fileName);
	}
	cam_spe->deleteLater();
	emit cam_clear();
	
}
void camera_play::start()
{
	_beginthread(camera_playing, 0, NULL);
	
}
void camera_play::camera_playing(void *)
{
	cam_spe = NULL;
	
	cam_spe = new camera_specifics;
	cam_spe->set_hwnd(label_wind);
	QDateTime time = QDateTime::currentDateTime();
	QString str = time.toString("yy_MM_dd_hh_mm_ss");
	str = str + "_camera.mkv";
	fileName = str;
	cam_spe->copy_out_path(str);
	cam_spe->start();
	cam_spe->deleteLater();
}
void camera_play::ok()
{
	string_filter.clear();
	ui.filte_choice->currentIndex();
	string paramter = ui.size_resolution->text().toStdString();
	int i = ui.filte_choice->currentIndex();
	
	if (i == 1) string_filter = "scale=" + paramter + "/a";

	else if (i == 2) {
		string_filter = "crop=" + paramter;
	}
	else if (i == 3)
	{
		string_filter = "negate";
	}
	else if (i == 4)
	{
		string_filter.clear();
		string_filter = filter_mirror110;
	}
	else if (i == 5)
	{
		string_filter = "edgedetect[out]";
	}
	else if (i == 6)
	{
		string_filter = "curves=vintage";
	}
	else if (i == 7)
	{
		string_filter = "drawtext=fontfile=ttt.ttf:fontcolor=";
		paramter = ui.line_caption->text().toStdString();
		int index = ui.captions_color->currentIndex();
		int index_size = ui.size->currentIndex();
		int sizee = 10 + 5 * index_size;
		char hh[20] = { '\0' };
		QString x_str = ui.X_->text();
		QString y_str = ui.Y_->text();
		QString pos = "x=" + x_str + ":" + "y=" + y_str;
		itoa(sizee, hh, 10);
		string ie(hh);
		switch (index)
		{

		case 0:
		{
				  string_filter += "red:fontsize=" + ie + ":text='" + paramter + "':" + pos.toStdString();
				  break;
		}
		case 1:
		{
				  string_filter += "black:fontsize=" + ie + ":text='" + paramter + "':" + pos.toStdString();
				  break;
		}
		case 2:
		{
				  string_filter += "white:fontsize=" + ie + ":text='" + paramter + "':" + pos.toStdString();
				  break;
		}
		case 3:
		{
				  string_filter += "black:fontsize=" + ie + ":text='" + paramter + "':" + pos.toStdString();
				  break;
		}
		case 4:
		{
				  string_filter += "green:fontsize=" + ie + ":text='" + paramter + "':" + pos.toStdString();
				  break;
		}
		case 5:
		{
				  string_filter += "blue:fontsize=" + ie + ":text='" + paramter + "':" + pos.toStdString();
				  break;
		}
		}
	}
	else if (i == 8)
	{
		string_filter.clear();
		string_filter = "transpose=0";
	}
	else if (i == 9)
	{
		string_filter.clear();
		string_filter = "transpose=1";
	}
	else if (i == 10)
	{
		string_filter.clear();
		string_filter = "transpose=2";
	}
	else if (i == 12)
	{
		string_filter.clear();
		if (image_filename.isEmpty() && ui.X_->text().isNull() && ui.Y_->text().isNull())
		{
			QMessageBox::warning(this, "����", "����д����");
			return;
		}
		int transparent = ui.size->currentIndex();
		int tran = 10 + 5 * transparent;
		double real_tran = tran / 100.0;
		char buff[20] = { '\0' };
		gcvt(real_tran, 1, buff);
		string ing(buff);
		string_filter = "movie=";
		

		//const char *filter_watermark = "movie=test.jpg,scale=150:300,colorkey=0x000000:0.1:0.7[wm];[in][wm]overlay=100:100[out]";
		string_filter += image_filename.toLocal8Bit().data();
		string_filter += ",colorkey=0x000000:0.1:";
		string_filter += ing;
		string_filter += "[wm];[in][wm]overlay=" + ui.X_->text().toStdString() + ":" + ui.Y_->text().toStdString() + "[out]";
		//string_filter = "movie=test.jpg[wm];[in][wm]overlay=100:100[out]";
		
	}
	if (string_filter.empty())
	{
		cam_spe->set_filter_change("null", label_wind);
	}
	
	else
	{
		
		cam_spe->set_filter_change(string_filter, label_wind);
	}

}
void camera_play::handle_filter_changed(int i)
{
	switch (i)
	{
	case 0:
	{
			  string_filter.clear();
			  this->setFixedSize(400, 480);
			  break;
	}
	case 1:
	{
			  string_filter.clear();
			 // string_filter = "scale=";
			  ui.label_size_caption->setText("������ֱ���");
			  ui.label_size_caption->show();
			  ui.size->hide();
			  ui.size_resolution->show();
			  this->setFixedSize(400, 480);
			  break;
	}
	case 2:
	{ 
			  string_filter.clear();
			  //string_filter = "crop=";
			  ui.label_size_caption->setText("������ü���Ƶ����");
			  ui.label_size_caption->show();
			  ui.size->hide();
			  ui.size_resolution->show();
			  this->setFixedSize(400, 480);
			  break;
	}
	case 3:
	{
			  ui.label_size_caption->hide();
			  string_filter.clear();
			 // string_filter = "negate";
			  this->setFixedSize(400, 480);
			  ui.size_resolution->hide();
			  ui.size->hide();
			  break;
	}
	case 4:
	{
			  ui.label_size_caption->hide();
			  string_filter.clear();
			  this->setFixedSize(400, 480);
			  ui.size_resolution->hide();
			  ui.size->hide();
			  break;
	}
	case 5:
	{
			  ui.label_size_caption->hide();
			  string_filter.clear();
			 
			  this->setFixedSize(400, 480);
			  ui.size_resolution->hide();
			  ui.size->hide();
			  break;
	}
	case 6:
	{
			  ui.label_size_caption->hide();
			  string_filter.clear();
			  
			  this->setFixedSize(400, 480);
			  ui.size_resolution->hide();
			  ui.size->hide();
			  break;
	}
	case 7:
	{
			 /* string_filter.clear();
			 // string_filter = "drawtext=fontfile=ttt.ttf:fontcolor=";
			  ui.label_size_caption->show();
			  ui.label_size_caption->setText("ѡ���С");
			  ui.size->show();
			  this->setFixedSize(400, 560);
			  ui.size->show();
			  ui.size_resolution->hide();
			  //ui.size->hide();
			  break;*/
			  string_filter.clear();
			  ui.label_4->setText("��������Ļ");
			  ui.size->show();
			  ui.pushButton_2->hide();
			  ui.line_caption->show();
			  ui.label_size_caption->show();
			  ui.label_size_caption->setText("ѡ���С");
			  //string_filter = "drawtext=fontfile=ttt.ttf:fontcolor=";
			  this->setFixedSize(400, 560);
			  ui.size_resolution->hide();
			  // ui.size->hide();
			  break;
	}
	case 8:
	{
			  string_filter.clear();
			  ui.label_4->setText("��������Ļ");
			  ui.size->show();
			  ui.pushButton_2->hide();
			  ui.line_caption->show();
			  ui.label_size_caption->show();
			  ui.label_size_caption->setText("ѡ���С");
			  //string_filter = "drawtext=fontfile=ttt.ttf:fontcolor=";
			  this->setFixedSize(400, 560);
			  ui.size_resolution->hide();
			 // ui.size->hide();
			  break;
	}
	case 9:
	case 10:
	case 11:
	{
			  this->setFixedSize(400, 480);
			  ui.label_size_caption->hide();
			  ui.size_resolution->hide();
			  ui.size->hide();
			  break;
	}
	case 12:
	{
			   string_filter.clear();
			   ui.label_6->hide();
			   //ui.label_6->setText("��ѡ��ͼƬ͸����");
			   ui.label_size_caption->show();
			   ui.label_size_caption->setText("��ѡ��ͼƬ͸����");
			   ui.size->show();
			   ui.pushButton_2->show();
			   ui.line_caption->hide();
			   ui.captions_color->hide();
			   ui.label_4->setText("��ѡ��ͼƬ");
			   this->setFixedSize(400, 560);
			   break;
	}
	}
}
camera_play::~camera_play()
{

}
