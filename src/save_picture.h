#ifndef SAVE_PICTURE_H
#define SAVE_PICTURE_H

#include <QObject>

class save_picture : public QObject
{
	Q_OBJECT

public:
	int start();
	save_picture(QObject *parent);
	~save_picture();

private:
	
};

#endif // SAVE_PICTURE_H
