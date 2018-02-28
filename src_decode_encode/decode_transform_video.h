#ifndef DECODE_TRANSFORM_VIDEO_H
#define DECODE_TRANSFORM_VIDEO_H

#include <QObject>
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
#pragma comment(lib, "lib/avutil.lib")
#pragma comment(lib, "lib/avcodec.lib")
#pragma comment(lib, "lib/avformat.lib")

#pragma comment(lib, "lib/avdevice.lib")
#pragma comment(lib, "lib/swresample.lib")
//#pragma comment(lib, "postproc.lib")
#pragma comment(lib, "lib/avfilter.lib")
#pragma comment(lib, "lib/swscale.lib")
#include "commom_signal.h"
class decode_transform_video : public commom_signal
{
	Q_OBJECT

public:
	decode_transform_video(QObject *parent = 0);
	~decode_transform_video();
	virtual int start();
	virtual void get_file_name(QString &);
	void get_input(QString input_name, QString output_name);
	void seek_stream(int64_t begin_point, int64_t end_point, AVFormatContext *ifmt_ctx);
private:
	QString input_name;
	QString in_filename, out_filename;
	void set_connect();
	bool is_audio;
signals:
	void progressbar_length_slot();
};

#endif // DECODE_TRANSFORM_VIDEO_H
