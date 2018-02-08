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

		ui.choice_file->setText("请选择音频");
		this->setWindowTitle("音频分割");
	}
	else if (tt == 1)
	{
		ui.choice_file->setText("请选择视频");
		this->setWindowTitle("分割视频");
	}
	else if (tt == 2)
	{
		ui.choice_file->setText("请选择视频");
		this->setWindowTitle("截取视频");
	}
	
	ui.label->setText("请选择截取时间");
	ui.ok->setText("确定");
	ui.cancel->setText("取消");
	connect(ui.lineEdit_2, SIGNAL(selectionChanged()), this, SLOT(change_edit()));
	connect(ui.ok, SIGNAL(clicked()), this, SLOT(ok()));
	connect(ui.cancel, SIGNAL(clicked()), this, SLOT(cancel()));
	connect(ui.choice_file, SIGNAL(clicked()), this, SLOT(choice_file()));
	this->setAttribute(Qt::WA_DeleteOnClose);
	
}
void seperte_music::choice_file()
{
	file_name = QFileDialog::getOpenFileName(0, "获取文件路径");
	ui.lineEdit->setText(file_name);
}
bool seperte_music::cut_video_parameter()
{
	from = ui.lineEdit_2->text().toInt();
	to = ui.lineEdit_3->text().toInt();
	if (from >= to)
	{

		QMessageBox::warning(0, "警告", "请输入正确的区间");
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
		QMessageBox::warning(0, "警告", "请填写完整音视频信息");
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
