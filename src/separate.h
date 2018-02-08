//“Ù ”∆µ∫œ≤¢
#ifndef SEPARATE_H
#define SEPARATE_H

#include <QObject>
#pragma once
#include <qobject.h>
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
#include "commom_signal.h"
class separate : public commom_signal
{
	Q_OBJECT

public:
	separate(QObject *parent);
	~separate();

	int start();
	void get_file_name(QString &str);
	void set_filename(QString audio_url, QString video_url);
private:
	void seek_stream(int64_t);
	QString file_inputname;
	int64_t duration_;
	QString audio_name;
	AVFormatContext *ifmt_ctx_v, *ifmt_ctx_a, *ofmt_ctx;
	QString video_name;
	
};

#endif // SEPARATE_H
