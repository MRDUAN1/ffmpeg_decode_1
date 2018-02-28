////“Ù∆µ∑÷∏Ó
#ifndef MERGE_MUSIC___H
#define MERGE_MUSIC___H

#include <QObject>
extern"C"
{
#include "libavutil/time.h"
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavfilter/avfiltergraph.h>
#include <libavfilter/avcodec.h>
#include <libavfilter/buffersink.h>
#include <libavfilter/buffersrc.h>
#include <libavutil/opt.h>
#include <libavutil/pixdesc.h>
}
#include "commom_signal.h"
#pragma comment(lib, "avutil.lib")
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avformat.lib")

#pragma comment(lib, "avdevice.lib")
#pragma comment(lib, "swresample.lib")
//#pragma comment(lib, "postproc.lib")
#pragma comment(lib, "avfilter.lib")
#pragma comment(lib, "swscale.lib")
class merge_music__ : public commom_signal
{
	Q_OBJECT

public:
	merge_music__(QObject *parent = 0);
	~merge_music__();
	int start();
	void set_file(QString file_name, int from, int to);
	void get_fileName(QString &str);
private:
	int from_, to_;
	QString file_name_, fileNameOutPut;
	void seek_stream(int64_t begin_point, int64_t end_point);
	AVStream  *in_stream;

	AVStream *out_stream = NULL;
	AVFormatContext *in_fmt_ctx = NULL, *out_fmt_ctx = NULL;
	int64_t current_pts;
	int64_t begin_pointt, end_pointt;
	bool if_cut;
	int64_t max = 0;
	int64_t size;
	int64_t first_pts;

};

#endif // MERGE_MUSIC___H
