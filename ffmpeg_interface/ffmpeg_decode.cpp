#include "ffmpeg_decode.h"


ffmpeg_decode::ffmpeg_decode()
{
}
void ffmpeg_decode::set_input_output_name(string input_name, string out_name)
{
	memset(in_filename, 0, 100);
	memset(out_filename, 0, 100);
	memcpy(in_filename, input_name.data(), input_name.size());
	memcpy(out_filename, out_name.data(), out_name.size());
}

ffmpeg_decode::~ffmpeg_decode()
{
}
int ffmpeg_decode::start()
{
	AVOutputFormat *ofmt = NULL;
	//输入对应一个AVFormatContext，输出对应一个AVFormatContext
	//（Input AVFormatContext and Output AVFormatContext）
	AVFormatContext *ifmt_ctx = NULL, *ofmt_ctx = NULL;
	AVPacket pkt;
	int ret, i;
	av_register_all();
	//输入（Input）
	if ((ret = avformat_open_input(&ifmt_ctx, in_filename, 0, 0)) < 0) {
		printf("Could not open input file.");
		goto end;
	}
	if ((ret = avformat_find_stream_info(ifmt_ctx, 0)) < 0) {
		printf("Failed to retrieve input stream information");
		goto end;
	}
	av_dump_format(ifmt_ctx, 0, in_filename, 0);
	//输出（Output）
	avformat_alloc_output_context2(&ofmt_ctx, NULL, NULL, out_filename);
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
	av_dump_format(ofmt_ctx, 0, out_filename, 1);
	//打开输出文件（Open output file）
	if (!(ofmt->flags & AVFMT_NOFILE)) {
		ret = avio_open(&ofmt_ctx->pb, out_filename, AVIO_FLAG_WRITE);
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
	int frame_index = 0;
	while (1) {
		AVStream *in_stream, *out_stream;
		//获取一个AVPacket（Get an AVPacket）
		ret = av_read_frame(ifmt_ctx, &pkt);
		if (ret < 0)
			break;
		in_stream = ifmt_ctx->streams[pkt.stream_index];
		out_stream = ofmt_ctx->streams[pkt.stream_index];
		/* copy packet */
		//转换PTS/DTS（Convert PTS/DTS）
		pkt.pts = av_rescale_q_rnd(pkt.pts, in_stream->time_base, out_stream->time_base, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
		pkt.dts = av_rescale_q_rnd(pkt.dts, in_stream->time_base, out_stream->time_base, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
		pkt.duration = av_rescale_q(pkt.duration, in_stream->time_base, out_stream->time_base);
		pkt.pos = -1;
		//写入（Write）
		ret = av_interleaved_write_frame(ofmt_ctx, &pkt);
		if (ret < 0) {
			printf("Error muxing packet\n");
			break;
		}
		printf("Write %8d frames to output file\n", frame_index);
		av_free_packet(&pkt);
		frame_index++;
	}
	//写文件尾（Write file trailer）
	av_write_trailer(ofmt_ctx);
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
	return 0;
}
