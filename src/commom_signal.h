//设置公共信号，用以发送总长度的signal
#ifndef COMMOM_SIGNAL_H
#define COMMOM_SIGNAL_H

#include <QObject>
#include <qstring.h>
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

class commom_signal : public QObject
{
	Q_OBJECT

public:
	commom_signal(QObject *parent = 0);
	~commom_signal();
	virtual int start() = 0;
	virtual void get_file_name(QString &);
signals:
	void length_all_merge_video_(int64_t); //发送视频全部长度
	void length_onect_merge_video_(int64_t); //发送视频进度条实时信息
protected:
	QString input_name__;
	

private:

	
};

#endif // COMMOM_SIGNAL_H
