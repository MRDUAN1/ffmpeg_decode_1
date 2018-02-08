//截取某一段视频，视频只有一段
#ifndef CUT_VIDEO_2_H
#define CUT_VIDEO_2_H

#include <QObject>
//#include "commom_signal.h"
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
#include "commom_signal.h"
class cut_video_2 : public commom_signal
{
	Q_OBJECT

public:
	cut_video_2(QObject *parent);
	~cut_video_2();
	int start();
	void set_filename(QString str, int from, int to);
	void get_filename(QString &str);
private:
	int from, to;
	QString strer;
	QString str_separate;
	void deal_with(QString&);
	AVFormatContext *ofmt1_ctx = NULL;
	AVStream *out1_vstream = NULL, *out1_astream = NULL;
	int inVideo_StreamIndex = -1, inAudio_StreamIndex = -1;
	int ret;
	AVFormatContext *ifmt_ctx = NULL;
	int64_t ps_a, ds_a, ps_v, ds_v;
	void seek_stream();

};

#endif // CUT_VIDEO_2_H
