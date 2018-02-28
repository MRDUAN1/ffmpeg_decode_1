#include "merge_music__.h"
#include "ffmpeg_interface.h"

#include <qfileinfo.h>
#include <qevent.h>
#include <Windows.h>
extern QString outPutPath;
extern int64_t now_length;
extern int64_t progressbar_length;
extern ffmpeg_interface *interface_;
merge_music__::merge_music__(QObject *parent)
: commom_signal(0)
{
	qRegisterMetaType<int64_t>("int64_t");
}

merge_music__::~merge_music__()
{

}
void merge_music__::seek_stream(int64_t begin_point, int64_t end_point)
{
	int p;
	enum AVMediaType type;
	begin_pointt = begin_point;
	end_pointt = end_point;
	if ((p = av_seek_frame(in_fmt_ctx, -1, end_point * AV_TIME_BASE, AVSEEK_FLAG_ANY)) < 0)
	{
		fprintf(stderr, "%s: error while seeking/n", "wrong");
	}
	AVPacket packet; //= { .data = NULL, .size = 0 };
	packet.data = NULL;
	packet.size = 0;
	int ret;
	AVFrame *frame;
	frame = av_frame_alloc();
	if (!frame) {
		ret = AVERROR(ENOMEM);
	}
	int64_t current_pts_;
	int got_frame;
	//int64_t max = 0;
	static int j = 0;
	int(*dec_func)(AVCodecContext *, AVFrame *, int*, const AVPacket *);

	int io = av_read_frame(in_fmt_ctx, &packet);
	int stream__ = packet.stream_index;
	type = in_fmt_ctx->streams[packet.stream_index]->codec->codec_type;
	av_packet_rescale_ts(&packet,
		in_fmt_ctx->streams[stream__]->time_base,
		in_fmt_ctx->streams[stream__]->codec->time_base);
	current_pts_ = packet.pts;
	
	if (current_pts_ > max) max = current_pts_;

	if ((p = av_seek_frame(in_fmt_ctx, -1, begin_point * AV_TIME_BASE, AVSEEK_FLAG_ANY)) < 0)
	{
		fprintf(stderr, "%s: error while seeking/n", "wrong");
	}
	io = av_read_frame(in_fmt_ctx, &packet);
	av_packet_rescale_ts(&packet,
		in_fmt_ctx->streams[stream__]->time_base,
		in_fmt_ctx->streams[stream__]->codec->time_base);
	first_pts = current_pts_ = packet.pts;
	size = max - current_pts_;
	emit length_all_merge_video_(size);
	
}
void merge_music__::get_fileName(QString &str)
{
	str = file_name_;
}
void merge_music__::set_file(QString file_name, int from, int to)
{
	input_name__ = file_name_ = file_name;
	QFileInfo file(file_name_);
	QString name = file.fileName();
	fileNameOutPut = outPutPath + "/cut_" + name;
	from_ = from;
	to_ = to;
}
int merge_music__::start()
{
	AVFrame *frame;
	AVPacket pkt_in, pkt_out;
	int audio_index = -1;
	int ret;
	
	av_register_all();
	avfilter_register_all();
	//input
	if (avformat_open_input(&in_fmt_ctx, file_name_.toLocal8Bit().data(), NULL, NULL) < 0)
	{
		printf("can not open input file context");
		return 0;
	}
	if (avformat_find_stream_info(in_fmt_ctx, NULL) < 0)
	{
		printf("can not find input stream info!\n");
	}

	//output
	avformat_alloc_output_context2(&out_fmt_ctx, NULL, NULL, fileNameOutPut.toLocal8Bit().data());
	if (!out_fmt_ctx)
	{
		printf("can not alloc output context!\n");
		return 0;
	}
	//open decoder & new out stream & open encoder
	for (int i = 0; i < in_fmt_ctx->nb_streams; i++)
	{
		if (in_fmt_ctx->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO)
		{
			//open decoder
			if (0 > avcodec_open2(in_fmt_ctx->streams[i]->codec, avcodec_find_decoder(in_fmt_ctx->streams[i]->codec->codec_id), NULL))
			{
				printf("can not find or open decoder!\n");
				return 0;
			}
			audio_index = i;
			//new stream
			out_stream = avformat_new_stream(out_fmt_ctx, NULL);
			if (!out_stream)
			{
				printf("can not new stream for output!\n");
			}

			//set codec context param			
			//use default audio encoder
			out_stream->codec->codec = avcodec_find_encoder(out_fmt_ctx->oformat->audio_codec);
			//use the input audio encoder
			//out_stream->codec->codec = avcodec_find_encoder(ifmt_ctx->streams[i]->codec->codec_id);

			out_stream->codec->sample_rate = in_fmt_ctx->streams[i]->codec->sample_rate;
			out_stream->codec->channel_layout = in_fmt_ctx->streams[i]->codec->channel_layout;
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

			if (out_fmt_ctx->oformat->flags & AVFMT_GLOBALHEADER)
				out_stream->codec->flags |= CODEC_FLAG_GLOBAL_HEADER;
			break;
		}
	}
	if (-1 == audio_index)
	{
		printf("found no audio stream in input file!\n");
		return 0;
	}
	if (!(out_fmt_ctx->oformat->flags & AVFMT_NOFILE))
	{
		if (avio_open(&out_fmt_ctx->pb, fileNameOutPut.toLocal8Bit().data(), AVIO_FLAG_WRITE) < 0)
		{
			printf("can not open output file handle!\n");
			return 0;
		}
	}
	if (avformat_write_header(out_fmt_ctx, NULL) < 0)
	{
		printf("can not write the header of the output file!\n");
		return 0;
	}
	av_init_packet(&pkt_out);

	int got_frame, got_picture;
	int frame_index = 0;
	int i = 0;
	seek_stream(from_, to_);
	int current_pts;
	int first_frame_pts, num = 0;

	for (int i = 0;; i++)
	{
		av_init_packet(&pkt_out);
		pkt_in.data = NULL;
		pkt_in.size = 0;

		got_frame = -1;
		got_picture = -1;

		if (av_read_frame(in_fmt_ctx, &pkt_in) < 0)
		{
			break;
		}
		num++;

		av_packet_rescale_ts(&pkt_in,
			in_fmt_ctx->streams[0]->time_base,
			in_fmt_ctx->streams[0]->codec->time_base);
		emit length_onect_merge_video_(pkt_in.pts - first_pts);
		if (num == 1) first_frame_pts = pkt_in.pts;
		current_pts = pkt_in.pts;
		pkt_in.pts = pkt_in.dts = current_pts - first_frame_pts;
		if (current_pts > max) break;
		in_stream = in_fmt_ctx->streams[1];
		out_stream = out_fmt_ctx->streams[1];
		/* copy packet */
		//×ª»»PTS/DTS£¨Convert PTS/DTS£©
		/*pkt_out.pts = av_rescale_q_rnd(pkt_in.pts, in_stream->time_base, out_stream->time_base, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
		pkt_out.dts = av_rescale_q_rnd(pkt_in.dts, in_stream->time_base, out_stream->time_base, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
		pkt_out.duration = av_rescale_q(pkt_in.duration, in_stream->time_base, out_stream->time_base);
		pkt_out.pos = -1;*/
		ret = av_write_frame(out_fmt_ctx, &pkt_in);
		if (ret < 0) {
			printf("Error muxing packet\n");
			return 0;
			break;
		}
		av_free_packet(&pkt_out);
	}
	//Ð´ÎÄ¼þÎ²£¨Write file trailer£©
	av_write_trailer(out_fmt_ctx);
	Sleep(200);
	return 1;
}