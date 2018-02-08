#ifndef MERGE_AUDIO_H
#define MERGE_AUDIO_H

#include <QObject>
extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavfilter/avfiltergraph.h"
#include "libavfilter/avcodec.h"
#include "libavfilter/buffersink.h"
#include "libavfilter/buffersrc.h"
#include "libavutil/avutil.h"
#include "libavutil/opt.h"
#include "libavutil/pixdesc.h"
};
#include "commom_signal.h"
class merge_audio : public commom_signal
{
	Q_OBJECT

public:
	merge_audio(QObject *parent);
	~merge_audio();
	int start();
	void set_file(QString file_name_1, QString file_name_2);
	void get_fileName_(QString &str);
private:
	void seek_stream(int64_t, int);
	QString file_audio_1, file_audio_2, out_path;
	int init_output(char *file_name);
	int open_input_file2(const char*filename);
	int open_input_file(const char*filename);
	AVFormatContext *ifmt_ctx;
	AVFormatContext *ifmt_ctx2;
	AVFormatContext *ofmt_ctx;
	int64_t pts = 0;
	AVStream * out_stream;
	int audio_index;
	int if_cut;
	int64_t duration_1, duration_2;
	int64_t current_pts;
	int64_t begin_pointt, end_pointt;

};

#endif // MERGE_AUDIO_H
