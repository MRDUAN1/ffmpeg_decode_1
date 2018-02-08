#ifndef REMUTEX_H
#define REMUTEX_H

#include <QWidget>
#include "ui_remutex.h"

class remutex : public QWidget
{
	Q_OBJECT

public:
	remutex(QWidget *parent = 0);
	~remutex();

private:
	Ui::remutex ui;
};

#endif // REMUTEX_H
