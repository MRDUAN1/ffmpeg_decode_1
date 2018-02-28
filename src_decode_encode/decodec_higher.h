#ifndef DECODEC_HIGHER_H
#define DECODEC_HIGHER_H

#include <QObject>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#define USEFILTER 1
#define snprintf _snprintf
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
#include <string>
#include "commom_signal.h"
using std::string;
class decodec_higher : public commom_signal
{
	Q_OBJECT

public:
	decodec_higher(QObject *parent = 0);
	~decodec_higher();
	void set_filter(int i);
	void get_input(QString input, QString out);
	int start();
private:
	AVFilterContext *buffersink_ctx;
	AVFilterContext *buffersrc_ctx;
	AVFilterGraph *filter_graph;
	AVFilter *buffersrc;
	AVFilter *buffersink;
	AVFrame* picref;
	std::string filter_;
	int apply_filters(AVFormatContext *ifmt_ctx);
	//QString filter_mirror1, filter_mirror12, filter_mirror3, filter_descr3, filter_watermark, filter_negate, filter_edge, filter_split4, filter_vintage;
	int flush_encoder(AVFormatContext *ifmt_ctx, AVFormatContext *ofmt_ctx, unsigned int stream_index, int framecnt);
	int flush_encoder_a(AVFormatContext *ifmt_ctx_a, AVFormatContext *ofmt_ctx, unsigned int stream_index, int nb_samples);
	QString in_filename, out_filename;
	int open_input_file(const char*filename);
	AVFormatContext *ifmt_ctx = NULL;
	AVFormatContext *ifmt_ctx_a = NULL;
	AVFormatContext *ofmt_ctx;
	AVInputFormat* ifmt;
	AVStream* video_st;
	AVStream* audio_st;
	AVCodecContext* pCodecCtx;
	AVCodecContext* pCodecCtx_a;
	AVCodec* pCodec;
	AVCodec* pCodec_a;
};

#endif // DECODEC_HIGHER_H
