#include "save_picture.h"
#include <stdlib.h>  
#include <stdio.h>  
#include <string.h>
#include <fstream>
#include <string>
extern "C"{
#include <libavformat/avformat.h>  
#include <libavcodec/avcodec.h>  
#include <libavdevice/avdevice.h>  
#include <libswscale/swscale.h>  

#include <windows.h>  

#include <time.h>  
#pragma comment(lib, "avutil.lib")
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avformat.lib")
#pragma comment(lib, "avdevice.lib")
#pragma comment(lib, "swresample.lib")
#pragma comment(lib, "postproc.lib")
#pragma comment(lib, "avfilter.lib")

#pragma comment(lib, "swscale.lib")
}
save_picture::save_picture(QObject *parent)
	: QObject(parent)
{

}
int save_picture::start()
{
	return 1;
}
save_picture::~save_picture()
{

}
