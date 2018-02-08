#include "decode_transform_video.h"
#include <Windows.h>
#include <qprogressbar.h>
#include <stdio.h>
#include "ffmpeg_interface.h"
extern ffmpeg_interface *interface_;
static int64_t maxx; //含义为最大pts量
void decode_transform_video::seek_stream(int64_t begin_point, int64_t end_point, AVFormatContext *ifmt_ctx)
{
	int p;
	
	if ((p = av_seek_frame(ifmt_ctx, -1, end_point * AV_TIME_BASE, AVSEEK_FLAG_ANY)) < 0)
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
	maxx = 0;
	int64_t current_pts_;
	int got_frame = 0;
	while (1)
	{
		int io = av_read_frame(ifmt_ctx, &packet);
		int stream__ = packet.stream_index;
		if (stream__ == 0 && !is_audio) continue;
		maxx = packet.pts;
		break;
	}
	if ((p = av_seek_frame(ifmt_ctx, -1, begin_point * AV_TIME_BASE, AVSEEK_FLAG_ANY)) < 0)
	{
		fprintf(stderr, "%s: error while seeking/n", "wrong");
	}
	emit length_all_merge_video_(maxx / AV_TIME_BASE);
}
void decode_transform_video::get_file_name(QString &file_name)
{
	file_name = input_name__;
}
decode_transform_video::decode_transform_video(QObject *parent)
: commom_signal(0)
{
}

decode_transform_video::~decode_transform_video()
{

}
int decode_transform_video::start()
{
	
	AVBitStreamFilterContext * vbsf = NULL;
	//cl = new clas;
	AVOutputFormat *ofmt = NULL;
	//输入对应一个AVFormatContext，输出对应一个AVFormatContext
	//（Input AVFormatContext and Output AVFormatContext）
	AVFormatContext *ifmt_ctx = NULL, *ofmt_ctx = NULL;
	AVPacket pkt;
	int ret, i;
	av_register_all();

	//输入（Input）
	if ((ret = avformat_open_input(&ifmt_ctx, in_filename.toLocal8Bit().data(), 0, 0)) < 0) {
		printf("Could not open input file.");
		goto end;
	}
	if ((ret = avformat_find_stream_info(ifmt_ctx, 0)) < 0) {
		printf("Failed to retrieve input stream information");
		goto end;
	}
	is_audio = false;
	if (ifmt_ctx->nb_streams <= 1)
		is_audio = true;
	av_dump_format(ifmt_ctx, 0, in_filename.toLocal8Bit().data(), 0);
	//输出（Output）
	avformat_alloc_output_context2(&ofmt_ctx, NULL, NULL, out_filename.toLocal8Bit().data());
	if (!ofmt_ctx) {
		printf("Could not create output context\n");
		ret = AVERROR_UNKNOWN;
		goto end;
	}
	ofmt = ofmt_ctx->oformat;
	for (i = 0; i < ifmt_ctx->nb_streams; i++) {
		//根据输入流创建输出流（Create output AVStream according to input AVStream）
		AVStream *in_stream = ifmt_ctx->streams[i];
		AVStream *out_stream = avformat_new_stream(ofmt_ctx, in_stream->codec->codec);
		if (!out_stream) {
			printf("Failed allocating output stream\n");
			ret = AVERROR_UNKNOWN;
			goto end;
		}
		//复制AVCodecContext的设置（Copy the settings of AVCodecContext）
		ret = avcodec_copy_context(out_stream->codec, in_stream->codec);
		if (ret < 0) {
			printf("Failed to copy context from input to output stream codec context\n");
			goto end;
		}
		out_stream->codec->codec_tag = 0;
		if (ofmt_ctx->oformat->flags & AVFMT_GLOBALHEADER)
			out_stream->codec->flags |= CODEC_FLAG_GLOBAL_HEADER;
	}
	//输出一下格式------------------
	//打开输出文件（Open output file）
	if (!(ofmt->flags & AVFMT_NOFILE)) {
		ret = avio_open(&ofmt_ctx->pb, out_filename.toLocal8Bit().data(), AVIO_FLAG_WRITE);
		if (ret < 0) {
			printf("Could not open output file '%s'", out_filename);
			goto end;
		}
	}
	//写文件头（Write file header）
	ret = avformat_write_header(ofmt_ctx, NULL);
	if (ret < 0) {
		printf("Error occurred when opening output file\n");
		goto end;
	}
	seek_stream(0, (ifmt_ctx->duration) / 1000000 - 2, ifmt_ctx);
	vbsf = av_bitstream_filter_init("h264_mp4toannexb");
	input_name = in_filename;
	int frame_index = 0;
	static int len = 0;
	while (1) {
		AVStream *in_stream, *out_stream;
		//获取一个AVPacket（Get an AVPacket）
		ret = av_read_frame(ifmt_ctx, &pkt);
		if (ret < 0)
			break;
		in_stream = ifmt_ctx->streams[pkt.stream_index];
		out_stream = ofmt_ctx->streams[pkt.stream_index];
		if (pkt.pts == AV_NOPTS_VALUE) pkt.pts = pkt.dts;
		if (is_audio)
		{
			len++;
			if (len == 10)
			{
				emit length_onect_merge_video_(pkt.pts / AV_TIME_BASE);
				len = 0;
			}
		}
		if (pkt.stream_index == 1)
		{
			len++;
			if (len == 10)
			{
				emit length_onect_merge_video_(pkt.pts / AV_TIME_BASE);
				len = 0;
			}
		}
		if (pkt.pts == AV_NOPTS_VALUE)
			pkt.pts = pkt.dts;
		pkt.pts = av_rescale_q_rnd(pkt.pts, in_stream->time_base, out_stream->time_base, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
		pkt.dts = av_rescale_q_rnd(pkt.dts, in_stream->time_base, out_stream->time_base, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
		pkt.duration = av_rescale_q(pkt.duration, in_stream->time_base, out_stream->time_base);
		pkt.pos = -1;
		
		if (pkt.stream_index == 0) {

			AVPacket fpkt = pkt;
			int a = av_bitstream_filter_filter(vbsf,
				out_stream->codec, NULL, &fpkt.data, &fpkt.size,
				pkt.data, pkt.size, pkt.flags & AV_PKT_FLAG_KEY);
			pkt.data = fpkt.data;
			pkt.size = fpkt.size;

		}
		
		//写入（Write）
		ret = av_write_frame(ofmt_ctx, &pkt);
		
		if (ret < 0) {
			printf("Error muxing packet\n");
			break;
		}
		//printf("Write %8d frames to output file\n", frame_index);
		av_free_packet(&pkt);
		//frame_index++;
	}
	//写文件尾（Write file trailer）
	av_write_trailer(ofmt_ctx);
	Sleep(200);
end:
	avformat_close_input(&ifmt_ctx);
	/* close output */
	if (ofmt_ctx && !(ofmt->flags & AVFMT_NOFILE))
		avio_close(ofmt_ctx->pb);
	avformat_free_context(ofmt_ctx);
	if (ret < 0 && ret != AVERROR_EOF) {
		printf("Error occurred.\n");
		return -1;
	}
	//if (!cl) delete cl;
	return 0;
}
void decode_transform_video::get_input(QString input_name, QString output_name)
{
	in_filename = input_name;
	input_name__ = input_name;
	out_filename = output_name;
}
