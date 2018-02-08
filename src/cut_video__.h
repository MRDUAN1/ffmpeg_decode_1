//切割视频，处理后的视频有两段
#ifndef CUT_VIDEO___H
#define CUT_VIDEO___H

#include <QObject>
#include <QObject>
#include <qstring.h>
#include "commom_signal.h"
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

class cut_video__ : public commom_signal
{
	Q_OBJECT

public:
	cut_video__(QObject *parent);
	~cut_video__();
	int start();
	void set_file_name(QString str, int from, int to);
	//void get_file_name(QString &str);
private:
	//QString str;
	void seek_stream(int64_t);
	void deal_with(QString &str);
	int64_t duration_1;
	int64_t begin_, end_;
	int64_t last_dts_a = 0, last_dts_pre_a = 0;
	int64_t last_dts_v = 0, last_dts_pre_v = 0;
	QString cut_video_1, cut_video_2;
	int inVideo_StreamIndex = -1, inAudio_StreamIndex = -1;
	int ret;
	int splitPtsV = 0;//the real split video pts
	int splitDtsV = 0;
	int splitPtsA = 0;//the real split audio pts
	int splitDtsA = 0;
	int videoIndex = 0;//the real video index
	bool is_second = false;
	int splitTime;//the split time (sec)
	bool is_first_video = true, is_first_audio = true;
	AVPacket pkt;
	AVFormatContext *ifmt_ctx = NULL, *ofmt1_ctx = NULL, *ofmt2_ctx = NULL;
	AVStream *out1_vstream = NULL, *out1_astream = NULL;
	AVStream *out2_vstream = NULL, *out2_astream = NULL;

};

#endif // CUT_VIDEO___H
