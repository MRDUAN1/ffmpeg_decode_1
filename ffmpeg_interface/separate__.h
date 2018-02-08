#ifndef SEPARATE___H
#define SEPARATE___H

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
#include "commom_signal.h"
class separate__ : public commom_signal
{
	Q_OBJECT

public:
	separate__(QObject *parent = 0);
	~separate__();
	int start();
	void set_filename(QString file_name, QString strr);
	void get_file_name(QString &);
private:
	void seek_stream(int64_t);
	void handle_audio_video_name(QString strr);
	QString file_inputname;
	QString audio_name;
	QString video_name;
	int64_t duration;
	AVOutputFormat *ofmt_a, *ofmt_v = NULL;
	//£¨Input AVFormatContext and Output AVFormatContext£©
	AVFormatContext *ifmt_ctx, *ofmt_ctx_a, *ofmt_ctx_v;

};

#endif // SEPARATE___H
