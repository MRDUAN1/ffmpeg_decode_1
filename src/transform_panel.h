#ifndef TRANSFORM_PANEL_H
#define TRANSFORM_PANEL_H

#include <QWidget>
#include "ui_transform_panel.h"
#include <qfiledialog.h>
# pragma execution_character_set("utf-8")
class transform_panel : public QWidget
{
	Q_OBJECT

public:
	transform_panel(QString str, QWidget *parent = 0, bool separate_video = false);
	void set_is_picture(); //是否处理图片
	~transform_panel();
private:
	bool is_separate; //是处理视频还是音频
	void insert_tablewidget(qint64 size_, QString dir, QString filr_name, QString full_name);
	Ui::transform_panel ui;
	void init_table_widget();
	void init_settext(); //界面设置文字
	void set_connect();
	int now_row; //现在有几行
	bool is_picture_; //处理的是否是图片
	QString full_path; //路径名
	int now_row_before;
	void set_pushbutton_menu(); //设置按钮的菜单
	QString fileDirDefault; //设置默认输出文件
	QTextCodec *code;
signals:
	void ok_emit();
	//void set_connect();
	public slots:
	void combox_index(int);
	void add_file_slot();
	void clear_list_slot();
	void ok_start_slot();
	void out_setting_slot();
	void change_slot();
	void cut_part_slot();
	void remove_list_slot();
	void add_folder_slot();
	void if_select(int, int);
};

#endif // TRANSFORM_PANEL_H
