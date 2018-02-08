#ifndef SEPARATE_GUI_H
#define SEPARATE_GUI_H

#include <QWidget>
#include "ui_separate_gui.h"

class separate_gui : public QWidget
{
	Q_OBJECT

public:
	separate_gui(QWidget *parent = 0);
	~separate_gui();

private:
	Ui::separate_gui ui;
};

#endif // SEPARATE_GUI_H
