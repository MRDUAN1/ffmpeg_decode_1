#include "merge_gui.h"
#include <qfiledialog.h>
#include "ffmpeg_interface.h"
#include <qmessagebox.h>
extern ffmpeg_interface *interface_;
# pragma execution_character_set("utf-8")
merge_gui::merge_gui(QWidget *parent, int t)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setAttribute(Qt::WA_ShowModal, true);
	tt = t;
	ui.ok->setText("ȷ��");
	ui.cancel->setText("ȡ��");
	if (t == 0)
	{
		ui.video_pushbutton->setText("��ѡ����Ƶ");
		ui.audio_pushbutton->setText("��ѡ����Ƶ");
		this->setWindowTitle("����");
	}
	else if (t == 1)
	{
		ui.video_pushbutton->setText("��ѡ����Ƶ1");
		ui.audio_pushbutton->setText("��ѡ����Ƶ2");
		this->setWindowTitle("�ϲ���Ƶ");
	}
	else if (t == 3)
	{
		ui.video_pushbutton->setText("��ѡ����Ƶ1");
		ui.audio_pushbutton->setText("��ѡ����Ƶ2");
		this->setWindowTitle("�ϲ���Ƶ");
	}
	connect(ui.video_pushbutton, SIGNAL(clicked()), this, SLOT(video_slot()));
	connect(ui.audio_pushbutton, SIGNAL(clicked()), this, SLOT(audio_slot()));
	connect(ui.ok, SIGNAL(clicked()), this, SLOT(ok()));
	connect(ui.cancel, SIGNAL(clicked()), this, SLOT(cancel()));
	this->setAttribute(Qt::WA_DeleteOnClose);
}
void merge_gui::video_slot()
{
	if (tt == 0 || tt == 3)
	{
		video_url = QFileDialog::getOpenFileName(this, "��ȡ��Ƶ·��");
	}
	else if (tt == 1)
	{
		video_url = QFileDialog::getOpenFileName(this, "��ȡ��Ƶ1·��");
	}
	
	ui.lineEdit->setText(video_url);
}
void merge_gui::audio_slot()
{
	if (tt == 0)
	{
		audio_url = QFileDialog::getOpenFileName(this, "��ȡ��Ƶ·��");
	}
	else if (tt == 1)
	{
		audio_url = QFileDialog::getOpenFileName(this, "��ȡ��Ƶ2·��");
	}
	else if (tt == 3)
	{
		audio_url = QFileDialog::getOpenFileName(this, "��ȡ��Ƶ2·��");
	}
	ui.lineEdit_2->setText(audio_url);
}
merge_gui::~merge_gui()
{

}
void merge_gui::ok()
{
	if (ui.lineEdit->text().isEmpty() || ui.lineEdit_2->text().isEmpty())
	{
		QMessageBox::warning(0, "����", "����д��������Ƶ��Ϣ");
		return;
	}
	else
	{
		
		interface_->set_video_music_merge(ui.lineEdit->text(), ui.lineEdit_2->text(), tt);
	}
	interface_->show();
	this->close();

}
void merge_gui::cancel()
{
	interface_->show();
	this->close();
}
