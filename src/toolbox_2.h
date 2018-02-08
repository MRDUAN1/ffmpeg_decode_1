#ifndef TOOLBOX_2_H
#define TOOLBOX_2_H

#include <QWidget>
#include "ui_toolbox_2.h"

class toolbox_2 : public QWidget
{
	Q_OBJECT

public:
	toolbox_2(QWidget *parent = 0);
	~toolbox_2();

private:
	Ui::toolbox_2 ui;
};

#endif // TOOLBOX_2_H
