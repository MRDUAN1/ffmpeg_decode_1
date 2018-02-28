#include "merge_audio.h"
#include <qfileinfo.h>
#include <Windows.h>
extern QString outPutPath; //输出文件名
merge_audio::merge_audio(QObject *parent)
: commom_signal(parent)
{

}
void merge_audio::seek_stream(int64_t duration, int num)
{
	AVFormatContext *tem;
	if (num == 1) tem = ifmt_ctx;
	else tem = ifmt_ctx2;
	int p;
	
	int64_t ii = duration - 1;
	AVPacket packet; //= { .data = NULL, .size = 0 };
	packet.data = NULL;
	packet.size = 0;

	if ((p = av_seek_frame(tem, -1, ii * AV_TIME_BASE, AVSEEK_FLAG_ANY)) < 0)
	{
		fprintf(stderr, "%s: error while seeking/n", "wrong");
	}

	int i = 10;
	while (i--)
	{
		av_read_frame(tem, &packet);
		av_packet_rescale_ts(&packet,
			tem->streams[0]->time_base,
			tem->streams[0]->codec->time_base);
		int stream__ = packet.stream_index;
		if (stream__ == 0)
		{
			if (packet.pts == AV_NOPTS_VALUE) continue;
			if (num == 1)
			duration_1 = packet.pts;
			else duration_2 = packet.pts;
		}
	}
	if ((p = av_seek_frame(tem, -1, 0, AVSEEK_FLAG_ANY)) < 0)
	{
		fprintf(stderr, "%s: error while seeking/n", "wrong");
	}

}
void merge_audio::set_file(QString file_name_1, QString file_name_2)
{
	input_name__ = file_audio_1 = file_name_1;
	file_audio_2 = file_name_2;
	QFileInfo info(file_audio_1);
	QString path = info.fileName();
	out_path = outPutPath + "/" + path;
}
void merge_audio::get_fileName_(QString &str)
{
	str = file_audio_1;
}
merge_audio::~merge_audio()
{

}
int merge_audio::open_input_file(const char*filename)
{
	int ret;
	unsigned int i;
	ifmt_ctx = NULL;
	if ((ret = avformat_open_input(&ifmt_ctx, filename, NULL, NULL)) < 0) {
		av_log(NULL, AV_LOG_ERROR, "Cannot open input file\n");
		return ret;
	}
	if ((ret = avformat_find_stream_info(ifmt_ctx, NULL)) < 0) {
		av_log(NULL, AV_LOG_ERROR, "Cannot find stream information\n");
		return ret;
	}
	
	for (i = 0; i < ifmt_ctx->nb_streams; i++) {
		AVStream *stream;
		AVCodecContext *codec_ctx;
		stream = ifmt_ctx->streams[i];
		codec_ctx = stream->codec;
		/* Reencode video & audio and remux subtitles etc. */
		if (codec_ctx->codec_type == AVMEDIA_TYPE_VIDEO
			|| codec_ctx->codec_type == AVMEDIA_TYPE_AUDIO) {
			/* Open decoder */
			ret = avcodec_open2(codec_ctx,
				avcodec_find_decoder(codec_ctx->codec_id), NULL);
			if (ret < 0) {
				av_log(NULL, AV_LOG_ERROR, "Failed to open decoder for stream #%u\n", i);
				return ret;
			}
		}
	}
	seek_stream(ifmt_ctx->duration / AV_TIME_BASE, 1);
	av_dump_format(ifmt_ctx, 0, filename, 0);
	return 0;
}

int merge_audio::open_input_file2(const char*filename)
{
	int ret;
	unsigned int i;
	ifmt_ctx2 = NULL;
	if ((ret = avformat_open_input(&ifmt_ctx2, filename, NULL, NULL)) < 0) {
		av_log(NULL, AV_LOG_ERROR, "Cannot open input file\n");
		return ret;
	}
	if ((ret = avformat_find_stream_info(ifmt_ctx2, NULL)) < 0) {
		av_log(NULL, AV_LOG_ERROR, "Cannot find stream information\n");
		return ret;
	}
	
	for (i = 0; i < ifmt_ctx2->nb_streams; i++) {
		AVStream *stream;
		AVCodecContext *codec_ctx;
		stream = ifmt_ctx2->streams[i];
		codec_ctx = stream->codec;
		/* Reencode video & audio and remux subtitles etc. */
		if (codec_ctx->codec_type == AVMEDIA_TYPE_VIDEO
			|| codec_ctx->codec_type == AVMEDIA_TYPE_AUDIO) {
			/* Open decoder */
			ret = avcodec_open2(codec_ctx,
				avcodec_find_decoder(codec_ctx->codec_id), NULL);
			if (ret < 0) {
				av_log(NULL, AV_LOG_ERROR, "Failed to open decoder for stream #%u\n", i);
				return ret;
			}
		}
	}
	seek_stream(ifmt_ctx2->duration / AV_TIME_BASE, 2);
	av_dump_format(ifmt_ctx2, 0, filename, 0);
	return 0;
}
int merge_audio::init_output(char *file_name)
{
	avformat_alloc_output_context2(&ofmt_ctx, NULL, NULL, file_name);
	if (!ofmt_ctx)
	{
		printf("can not alloc output context!\n");
	}
	//open decoder & new out stream & open encoder
	for (int i = 0; i < ifmt_ctx->nb_streams; i++)
	{
		if (ifmt_ctx->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO)
		{

			//open decoder
			if (0 > avcodec_open2(ifmt_ctx->streams[i]->codec, avcodec_find_decoder(ifmt_ctx->streams[i]->codec->codec_id), NULL))
			{
				printf("can not find or open decoder!\n");
			}
			audio_index = i;
			//new stream
			out_stream = avformat_new_stream(ofmt_ctx, NULL);
			if (!out_stream)
			{
				printf("can not new stream for output!\n");
			}

			//set codec context param			
			//use default audio encoder
			out_stream->codec->codec = avcodec_find_encoder(ofmt_ctx->oformat->audio_codec);
			//use the input audio encoder
			//out_stream->codec->codec = avcodec_find_encoder(ifmt_ctx->streams[i]->codec->codec_id);

			out_stream->codec->sample_rate = ifmt_ctx->streams[i]->codec->sample_rate;
			out_stream->codec->channel_layout = ifmt_ctx->streams[i]->codec->channel_layout;
			out_stream->codec->channels = av_get_channel_layout_nb_channels(out_stream->codec->channel_layout);
			// take first format from list of supported formats
			out_stream->codec->sample_fmt = out_stream->codec->codec->sample_fmts[0];
			AVRational time_base = { 1, out_stream->codec->sample_rate };
			out_stream->codec->time_base = time_base;

			//open encoder
			if (!out_stream->codec->codec)
			{
				printf("can not find the encoder!\n");
			}
			if ((avcodec_open2(out_stream->codec, out_stream->codec->codec, NULL)) < 0)
			{
				printf("can not open the encoder\n");
			}

			if (ofmt_ctx->oformat->flags & AVFMT_GLOBALHEADER)
				out_stream->codec->flags |= CODEC_FLAG_GLOBAL_HEADER;
			break;
		}
	}
	if (!(ofmt_ctx->oformat->flags & AVFMT_NOFILE))
	{
		if (avio_open(&ofmt_ctx->pb, out_path.toLocal8Bit().data(), AVIO_FLAG_WRITE) < 0)
		{
			printf("can not open output file handle!\n");
		}
	}
	if (avformat_write_header(ofmt_ctx, NULL) < 0)
	{
		printf("can not write the header of the output file!\n");
	}
	return 1;
}
int merge_audio::start()
{
	int ret;
	int64_t u;
	if_cut = false;
	AVPacket packet; //= { .data = NULL, .size = 0 };
	packet.data = NULL;
	packet.size = 0;
	AVFrame *frame = NULL;
	enum AVMediaType type;
	unsigned int stream_index;
	unsigned int i;
	int got_frame;
	int(*dec_func)(AVCodecContext *, AVFrame *, int*, const AVPacket *);
	av_register_all();
	avfilter_register_all();
	if ((ret = open_input_file(file_audio_1.toLocal8Bit().data())) < 0)
		goto end;
	if ((ret = open_input_file2(file_audio_2.toLocal8Bit().data())) < 0)
		goto end;
	if ((ret = init_output(out_path.toLocal8Bit().data())) < 0)
		goto end;
	int hh = (duration_1 + duration_2);
	emit length_all_merge_video_((duration_1 + duration_2));
	while (1) {

		if ((ret = av_read_frame(ifmt_ctx, &packet)) < 0)
			break;
		u = packet.pts;
		av_packet_rescale_ts(&packet,
			ifmt_ctx->streams[0]->time_base,
			ifmt_ctx->streams[0]->codec->time_base);
		pts = packet.pts;
		if (packet.stream_index == 0)
			emit length_onect_merge_video_(pts);
		av_write_frame(ofmt_ctx, &packet);
		av_free_packet(&packet);
	}
	while (1) {

		if ((ret = av_read_frame(ifmt_ctx2, &packet)) < 0)
			break;
		
		av_packet_rescale_ts(&packet,
			ifmt_ctx2->streams[0]->time_base,
			ifmt_ctx2->streams[0]->codec->time_base);
		int64_t now_pts = packet.pts;
		packet.pts = now_pts + pts;
		
		packet.dts = packet.pts;
		if (packet.stream_index == 0)
			emit length_onect_merge_video_(packet.pts);
		av_write_frame(ofmt_ctx, &packet);
		av_free_packet(&packet);
	}
	Sleep(200);
end:
	av_free_packet(&packet);
	av_frame_free(&frame);
	for (i = 0; i < ifmt_ctx->nb_streams; i++) {
		avcodec_close(ifmt_ctx->streams[i]->codec);
		if (ofmt_ctx && ofmt_ctx->nb_streams > i && ofmt_ctx->streams[i] && ofmt_ctx->streams[i]->codec)
			avcodec_close(ofmt_ctx->streams[i]->codec);
	}
	avformat_close_input(&ifmt_ctx);
	if (ofmt_ctx && !(ofmt_ctx->oformat->flags & AVFMT_NOFILE))
		avio_closep(&ofmt_ctx->pb);
	avformat_free_context(ofmt_ctx);
	return ret ? 1 : 0;
}

