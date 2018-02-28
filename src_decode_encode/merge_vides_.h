#ifndef MERGE_VIDES__H
#define MERGE_VIDES__H

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
class merge_vides_ : public commom_signal
{
	Q_OBJECT

public:
	merge_vides_(QObject *parent);
	~merge_vides_();
	int start();
	void set_filename(QString str, QString);
	void get_filename(QString &str);
	
private:
	int64_t duration_1, duration_2;
	void seek_stream(int64_t, int64_t);
	int open_input_file2(const char*filename);
	int open_input_file(const char*filename);
	int open(const char*filename);
	int open_output_file(const char*filename);
	AVFormatContext *ifmt_ctx;
	AVFormatContext *ifmt_ctx2;
	AVFormatContext *ofmt_ctx;
	//static AVFormatContext *ofmt_ctx2;

	int64_t current_pts;
	int64_t video_pts, audio_pts;
	int64_t video_dts, audio_dts;
	AVBitStreamFilterContext *vbsf = NULL;
	AVBitStreamFilterContext* aacbsfc;
	AVInputFormat* ifmt;
	AVStream* video_st;
	AVStream* audio_st;
	AVCodecContext* pCodecCtx;
	AVCodecContext* pCodecCtx_a;
	AVCodec* pCodec;
	AVCodec* pCodec_a;
	QString str_1, str_2, str_out;

};

#endif // MERGE_VIDES__H
