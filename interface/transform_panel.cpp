#include <string>
#include <qmenu.h>
#include <qaction.h>
#include <vector>
#include <qtextcodec.h>
#include "format_progam_3.h"
#include "ffmpeg_interface.h"
#include "ffmpeg_interface.h"
#include "transform_panel.h"
#include "global.h"
#include <qfile.h>
#include <qdir.h>
#include <qmessagebox.h>
extern "C"
{
#include "libavutil/opt.h"
#include "libavutil/time.h"
#include "libavutil/mathematics.h"
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavdevice/avdevice.h"
#include "libswscale/swscale.h"
#include "libswresample/swresample.h"
#include "libavutil/audio_fifo.h"
#if USEFILTER
#include "libavfilter/avfiltergraph.h"
#include "libavfilter/buffersink.h"
#include "libavfilter/buffersrc.h"
#endif
};
#define AV_TIME_BASE 1000000
#pragma comment(lib, "avutil.lib")
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avformat.lib")
#pragma comment(lib, "avdevice.lib")
#pragma comment(lib, "swresample.lib")
#pragma comment(lib, "avfilter.lib")
#pragma comment(lib, "swscale.lib")
extern ffmpeg_interface *interface_;
transform_panel::transform_panel(QString str,QWidget *parent, bool separate_video)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setAttribute(Qt::WA_ShowModal, true);
	if (separate_video)
		is_separate = true;
	else 
		is_separate = false;
	code = QTextCodec::codecForName("gb18030");
	init_table_widget();
	ui.label_transform_name->setText(str);
	now_row = 0;
	now_row_before = 0;
	init_settext();
	QDir *temp1 = new QDir;
	bool exist = temp1->exists("OUTPUT");
	if (!exist)
		bool ok = temp1->mkdir("OUTPUT");
	set_pushbutton_menu();
	set_connect();
	ui.tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
	ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	this->setAttribute(Qt::WA_DeleteOnClose);
	fileDirDefault = "./";
	ui.cut_part->setEnabled(false);
}
void transform_panel::set_pushbutton_menu()
{
	
}
void transform_panel::set_is_picture()
{
	is_picture_ = true;
}
void transform_panel::set_connect()
{
	connect(ui.tableWidget, SIGNAL(cellClicked(int, int)), this, SLOT(if_select(int, int)));
	connect(ui.add_file_up, SIGNAL(clicked()), this, SLOT(add_file_slot()));
	connect(ui.clear_list, SIGNAL(clicked()), this, SLOT(clear_list_slot()));
	connect(ui.ok_start, SIGNAL(clicked()), this, SLOT(ok_start_slot()));
	connect(ui.out_setting, SIGNAL(clicked()), this, SLOT(out_setting_slot()));
	connect(ui.cut_part, SIGNAL(clicked()), this, SLOT(cut_part_slot()));
	connect(ui.comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(combox_index(int)));
	connect(this, SIGNAL(ok_emit()), interface_, SLOT(SetListWidgetFromPanel()));
	connect(ui.remove_list, SIGNAL(clicked()), this, SLOT(remove_list_slot()));
	connect(ui.under_change, SIGNAL(clicked()), this, SLOT(add_folder_slot()));
}
transform_panel::~transform_panel()
{

}
void transform_panel::init_table_widget()
{
	QIcon pix("./CLEAR_ALL.png");
	QIcon pixx("./close.png");
	ui.clear_list->setIcon(pix);
	ui.clear_list->setIconSize(ui.clear_list->size());
	ui.remove_list->setIcon(pixx);
	ui.tableWidget->setColumnCount(5);
	//ui.tableWidget->setRowCount(7);
	ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.tableWidget->setColumnCount(5);
	QStringList m_header;
	m_header << QString("文件名") << QString("文件夹") << QString("大小") << QString("持续时间") << QString("截取片断");
	ui.tableWidget->setHorizontalHeaderLabels(m_header);
	ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}
void transform_panel::init_settext()
{
	ui.add_file_under->setIcon(QPixmap("./imag/fie.png"));
	ui.add_file_under->setIconSize(QSize(40, 35));
	ui.add_file_under->setText("添加文件");
	ui.add_file_up->setIcon(QPixmap("./imag/ww.png"));
	ui.add_file_up->setIconSize(QSize(40, 35));
	ui.add_file_up->setText("添加文件");
	ui.cut_part->setText("截取片断");
	ui.high_quantity->setText("高质量");
	ui.ok_start->setIcon(QPixmap("./imag/start.png"));
	
	ui.ok_start->setIconSize(QSize(40, 35));
	ui.ok_start->setText("  确认");
	ui.under_change->setIcon(QPixmap("./imag/fie1.png"));
	ui.under_change->setIconSize(QSize(40, 35));
	ui.under_change->setText("  改变");

	ui.out_setting->setIcon(QPixmap("./imag/ss.png"));
	ui.out_setting->setIconSize(QSize(40, 35));
	ui.out_setting->setText(tr("输出设置"));
	ui.under_nameof_output_file->setText("输出文件夹");
}
void transform_panel::add_file_slot()
{
	QString in = QFileDialog::getOpenFileName(this, tr("Open File"), fileDirDefault);
	if (in.isNull()) return;
	QFileInfo info;
	QString s_tr;
	info = QFileInfo(in);
	s_tr = info.fileName();
	string file_full_name = in.toStdString();
	int last_pos =  file_full_name.rfind('/');
	string dir_path = file_full_name.substr(0, last_pos);
	qint64 size = info.size();
	insert_tablewidget(size, QString::fromStdString(dir_path), s_tr, in);
}
void transform_panel::insert_tablewidget(qint64 size_, QString dir, QString file_name, QString full_name)
{
	QString str;
	double s = size_ / 1024.00 / 1024.00;
	double g = size_ / 1024.00 / 1024.00 / 1024.00;
	if (s < 1)
		str = QString("%1k").arg(size_ / 1024);
	else if (s > 1 && g < 1)
		str = QString("%1M").arg(s);
	else if (g >= 1)
		str = QString("%1G").arg(g);
	ui.tableWidget->setRowCount(++now_row_before);
	QTableWidgetItem *file_name_ = new QTableWidgetItem(file_name);
	file_name_->setToolTip(file_name);
	QTableWidgetItem *dir_name = new QTableWidgetItem(dir);
	dir_name->setToolTip(dir);
	QTableWidgetItem *size__ = new QTableWidgetItem(str);
	ui.tableWidget->setItem(now_row, 0, file_name_);
	ui.tableWidget->setItem(now_row, 1, dir_name);
	ui.tableWidget->setItem(now_row, 2, size__);
	av_register_all();
	AVFormatContext    *pformat_ctx = NULL;
	//打开文件
	//pformat_ctx会有所指向，不用分配内存
	if (avformat_open_input(&pformat_ctx, full_name.toLocal8Bit().data(), NULL, NULL) != 0)
	{
		QMessageBox::warning(this, "警告", "打开文件失败\n注意不要包含中文路径");
		return;
	}
	if (avformat_find_stream_info(pformat_ctx, NULL) < 0)
	{
		return ;
	}
	int64_t duration = pformat_ctx->duration + 5000;
	int64_t secs = duration / AV_TIME_BASE;
	int64_t min = secs / 60;
	//secs %= 60;
	int64_t hour = min / 60;
	if (hour == 0) hour = 00;
	if (min == 0) min = 0;
	int m = min - hour / 60;
	int s1 = secs - hour / 60 - min / 60;
	QString arg = QString("%1:%2:%3").arg(hour).arg(m).arg(s1);
	QTableWidgetItem *length = new QTableWidgetItem(arg);
	ui.tableWidget->setItem(now_row, 3, length);
	avformat_close_input(&pformat_ctx);
	avformat_free_context(pformat_ctx);
	now_row++;
}
void transform_panel::clear_list_slot()
{
	global::return_panel_list_data().clear();
	ui.tableWidget->clear();
}
void transform_panel::ok_start_slot()
{
	int rowcount = ui.tableWidget->rowCount();
	int i;
	int row;
	for (int i = 0; i < rowcount; i++)
	{
		panel_list_data *ro = new panel_list_data;
		if (is_separate)
			ro->is_separate = true;
		else
			ro->is_separate = false;
		ro->file_dir = ui.tableWidget->item(i, 1)->text();
		QString temp = ui.tableWidget->item(i, 1)->text() + "/";
		temp += ui.tableWidget->item(i, 0)->text();
		ro->full_name = temp;
		ro->file_dir = ui.tableWidget->item(i, 1)->text();
		ro->file_name = ui.tableWidget->item(i, 0)->text();
		ro->size = ui.tableWidget->item(i, 2)->text();
		ro->last_time = ui.tableWidget->item(i, 3)->text();
		ro->format = ui.label_transform_name->text();
		if (is_picture_) ro->is_picture = true;
		else ro->is_picture = false;
		global::return_panel_list_data().push_back(ro);
	}
	emit ok_emit();
	this->close();
}
void transform_panel::out_setting_slot()
{

}
void transform_panel::change_slot()
{

}
void transform_panel::cut_part_slot()
{
	format_progam_3 *cutFormat = new format_progam_3(this);
	cutFormat->set_input_name(full_path);
	
	cutFormat->start();
	
}
void transform_panel::combox_index(int index)
{

	if (index == 3)
	{
		add_folder_slot();
	}
	if (index == 0)
	{

	}

}
void transform_panel::remove_list_slot()
{
	int rowIndex = ui.tableWidget->currentRow();
	if (rowIndex != -1)
	{
		ui.tableWidget->removeRow(rowIndex);
		now_row_before--;
		now_row--;
	}
}
void transform_panel::add_folder_slot()
{
	fileDirDefault = QFileDialog::getExistingDirectory(this, "重新设置目录", "./");
	ui.comboBox->addItem(fileDirDefault);
	int i = ui.comboBox->count();
	ui.comboBox->setCurrentIndex(i - 1);
}
void transform_panel::if_select(int, int)
{
	int row = ui.tableWidget->currentRow();
	ui.cut_part->setEnabled(true);
	full_path = ui.tableWidget->item(row, 1)->text();
	full_path += "/";
	full_path += ui.tableWidget->item(row, 0)->text();
}
