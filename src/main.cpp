#include "ffmpeg_interface.h"
#include <qtextcodec.h>
#include <QtWidgets/QApplication>
#include "include\SDL2\SDL_main.h"
int main(int argc, char *argv[])
{
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("gb180130"));

	QApplication a(argc, argv);
	ffmpeg_interface w;
	
	printf("jjjjjjjjjjjjjjj");
	w.show();
	return a.exec();
}
