#include "seperte_music.h"
#include "ffmpeg_interface.h"
#include <qfiledialog.h>
#include <qmessagebox.h>
# pragma execution_character_set("utf-8")
extern ffmpeg_interface *interface_;
seperte_music::seperte_music(QWidget *parent, int i)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setAttribute(Qt::WA_ShowModal, true);
	is_first = false;
	tt = i;
	if (tt == 0)
	{

		ui.choice_file->setText("��ѡ����Ƶ");
		this->setWindowTitle("��Ƶ�ָ�");
	}
	else if (tt == 1)
	{
		ui.choice_file->setText("��ѡ����Ƶ");
		this->setWindowTitle("�ָ���Ƶ");
	}
	else if (tt == 2)
	{
		ui.choice_file->setText("��ѡ����Ƶ");
		this->setWindowTitle("��ȡ��Ƶ");
	}
	
	ui.label->setText("��ѡ���ȡʱ��");
	ui.ok->setText("ȷ��");
	ui.cancel->setText("ȡ��");
	connect(ui.lineEdit_2, SIGNAL(selectionChanged()), this, SLOT(change_edit()));
	connect(ui.ok, SIGNAL(clicked()), this, SLOT(ok()));
	connect(ui.cancel, SIGNAL(clicked()), this, SLOT(cancel()));
	connect(ui.choice_file, SIGNAL(clicked()), this, SLOT(choice_file()));
	this->setAttribute(Qt::WA_DeleteOnClose);
	
}
void seperte_music::choice_file()
{
	file_name = QFileDialog::getOpenFileName(0, "��ȡ�ļ�·��");
	ui.lineEdit->setText(file_name);
}
bool seperte_music::cut_video_parameter()
{
	from = ui.lineEdit_2->text().toInt();
	to = ui.lineEdit_3->text().toInt();
	if (from >= to)
	{

		QMessageBox::warning(0, "����", "��������ȷ������");
		from = 0;
		to = 0;
		return false;
	}
	return true;
}
void seperte_music::cancel()
{
	interface_->show();
	this->close();
}
void seperte_music::ok()
{
	if (ui.lineEdit->text().isEmpty() || ui.lineEdit_2->text().isEmpty() || ui.lineEdit_3->text().isEmpty())
	{
		QMessageBox::warning(0, "����", "����д��������Ƶ��Ϣ");
		return;
	}
	else
	{
		if (!cut_video_parameter())
			return;
			interface_->set_cut_music(file_name, from, to, tt);
	}
	interface_->show();
	this->close();
}

seperte_music::~seperte_music()
{

}
