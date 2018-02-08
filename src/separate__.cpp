#include "separate__.h"
#include <Windows.h>
extern QString outPutPath;
separate__::separate__(QObject *parent)
: commom_signal(parent)
{

}
void separate__::seek_stream(int64_t i)
{
	int p;
	int64_t ii = i - 1;
	AVPacket packet; //= { .data = NULL, .size = 0 };
	packet.data = NULL;
	packet.size = 0;

	if ((p = av_seek_frame(ifmt_ctx, -1, ii * AV_TIME_BASE, AVSEEK_FLAG_ANY)) < 0)
	{
		fprintf(stderr, "%s: error while seeking/n", "wrong");
	}
	int iA = 10;
	while (iA--)
	{
		av_read_frame(ifmt_ctx, &packet);
		int stream__ = packet.stream_index;
		if (stream__ == 0)
		{
			if (packet.pts == AV_NOPTS_VALUE) continue;
			duration = packet.pts;
		}
	}
	emit length_all_merge_video_(duration);
	if ((p = av_seek_frame(ifmt_ctx, -1, 0, AVSEEK_FLAG_ANY)) < 0)
	{
		fprintf(stderr, "%s: error while seeking/n", "wrong");
	}
}
void separate__::get_file_name(QString &strr)
{
	strr = file_inputname;
}
void separate__::handle_audio_video_name(QString strr)
{
	int h = strr.indexOf(".");
	//int all = strr.size();
	//int h1 = all - h - 1;
	QString before = strr.left(h);
	audio_name = outPutPath + "/" + before + ".aac";
	video_name = outPutPath + "/" + before + ".mkv";
}

void separate__::set_filename(QString file_name, QString strr)
{
	input_name__ = file_inputname = file_name;
	handle_audio_video_name(strr);
}
separate__::~separate__()
{

}
int separate__::start()
{
	ofmt_a = NULL, ofmt_v = NULL;
	//£¨Input AVFormatContext and Output AVFormatContext£©
	ifmt_ctx = NULL, ofmt_ctx_a = NULL, ofmt_ctx_v = NULL;
	AVPacket pkt;
	int ret, i;
	int videoindex = -1, audioindex = -1;
	int frame_index = 0;



	av_register_all();
	//Input
	if ((ret = avformat_open_input(&ifmt_ctx, file_inputname.toLocal8Bit().data(), 0, 0)) < 0) {
		printf("Could not open input file.");
		goto end;
	}
	if ((ret = avformat_find_stream_info(ifmt_ctx, 0)) < 0) {
		printf("Failed to retrieve input stream information");
		goto end;
	}
	seek_stream(ifmt_ctx->duration / AV_TIME_BASE);
	//Output
	avformat_alloc_output_context2(&ofmt_ctx_v, NULL, NULL, video_name.toLocal8Bit().data());
	if (!ofmt_ctx_v) {
		printf("Could not create output context\n");
		ret = AVERROR_UNKNOWN;
		goto end;
	}
	ofmt_v = ofmt_ctx_v->oformat;

	avformat_alloc_output_context2(&ofmt_ctx_a, NULL, NULL, audio_name.toLocal8Bit().data());
	if (!ofmt_ctx_a) {
		printf("Could not create output context\n");
		ret = AVERROR_UNKNOWN;
		goto end;
	}
	ofmt_a = ofmt_ctx_a->oformat;

	for (i = 0; i < ifmt_ctx->nb_streams; i++) {
		//Create output AVStream according to input AVStream
		AVFormatContext *ofmt_ctx;
		AVStream *in_stream = ifmt_ctx->streams[i];
		AVStream *out_stream = NULL;

		if (ifmt_ctx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO){
			videoindex = i;
			out_stream = avformat_new_stream(ofmt_ctx_v, in_stream->codec->codec);
			ofmt_ctx = ofmt_ctx_v;
		}
		else if (ifmt_ctx->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO){
			audioindex = i;
			out_stream = avformat_new_stream(ofmt_ctx_a, in_stream->codec->codec);
			ofmt_ctx = ofmt_ctx_a;
		}
		else{
			break;
		}

		if (!out_stream) {
			printf("Failed allocating output stream\n");
			ret = AVERROR_UNKNOWN;
			goto end;
		}
		//Copy the settings of AVCodecContext
		if (avcodec_copy_context(out_stream->codec, in_stream->codec) < 0) {
			printf("Failed to copy context from input to output stream codec context\n");
			goto end;
		}
		out_stream->codec->codec_tag = 0;

		if (ofmt_ctx->oformat->flags & AVFMT_GLOBALHEADER)
			out_stream->codec->flags |= CODEC_FLAG_GLOBAL_HEADER;
	}


	//Open output file
	if (!(ofmt_v->flags & AVFMT_NOFILE)) {
		if (avio_open(&ofmt_ctx_v->pb, video_name.toLocal8Bit().data(), AVIO_FLAG_WRITE) < 0) {
			//printf("Could not open output file '%s'", out_filename_v);
			goto end;
		}
	}

	if (!(ofmt_a->flags & AVFMT_NOFILE)) {
		if (avio_open(&ofmt_ctx_a->pb, audio_name.toLocal8Bit().data(), AVIO_FLAG_WRITE) < 0) {
			//printf("Could not open output file '%s'", out_filename_a);
			goto end;
		}
	}

	//Write file header
	if (avformat_write_header(ofmt_ctx_v, NULL) < 0) {
		printf("Error occurred when opening video output file\n");
		goto end;
	}
	if (avformat_write_header(ofmt_ctx_a, NULL) < 0) {
		printf("Error occurred when opening audio output file\n");
		goto end;
	}

#if USE_H264BSF
	AVBitStreamFilterContext* h264bsfc = av_bitstream_filter_init("h264_mp4toannexb");
#endif

	while (1) {
		AVFormatContext *ofmt_ctx;
		AVStream *in_stream, *out_stream;
		//Get an AVPacket
		if (av_read_frame(ifmt_ctx, &pkt) < 0)
			break;
		in_stream = ifmt_ctx->streams[pkt.stream_index];


		if (pkt.stream_index == videoindex){
			if (pkt.pts != AV_NOPTS_VALUE)
			emit length_onect_merge_video_(pkt.pts);
			out_stream = ofmt_ctx_v->streams[0];
			ofmt_ctx = ofmt_ctx_v;
			printf("Write Video Packet. size:%d\tpts:%lld\n", pkt.size, pkt.pts);
#if USE_H264BSF
			av_bitstream_filter_filter(h264bsfc, in_stream->codec, NULL, &pkt.data, &pkt.size, pkt.data, pkt.size, 0);
#endif
		}
		else if (pkt.stream_index == audioindex){
			out_stream = ofmt_ctx_a->streams[0];
			ofmt_ctx = ofmt_ctx_a;
			printf("Write Audio Packet. size:%d\tpts:%lld\n", pkt.size, pkt.pts);
		}
		else{
			continue;
		}


		//Convert PTS/DTS
		pkt.pts = av_rescale_q_rnd(pkt.pts, in_stream->time_base, out_stream->time_base, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
		pkt.dts = av_rescale_q_rnd(pkt.dts, in_stream->time_base, out_stream->time_base, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
		pkt.duration = av_rescale_q(pkt.duration, in_stream->time_base, out_stream->time_base);
		pkt.pos = -1;
		pkt.stream_index = 0;
		//Write
		if (av_interleaved_write_frame(ofmt_ctx, &pkt) < 0) {
			printf("Error muxing packet\n");
			break;
		}
		//printf("Write %8d frames to output file\n",frame_index);
		av_free_packet(&pkt);
		frame_index++;
	}

#if USE_H264BSF
	av_bitstream_filter_close(h264bsfc);
#endif
	Sleep(200);
	//Write file trailer
	av_write_trailer(ofmt_ctx_a);
	av_write_trailer(ofmt_ctx_v);
	return 1;
end:
	avformat_close_input(&ifmt_ctx);
	/* close output */
	if (ofmt_ctx_a && !(ofmt_a->flags & AVFMT_NOFILE))
		avio_close(ofmt_ctx_a->pb);

	if (ofmt_ctx_v && !(ofmt_v->flags & AVFMT_NOFILE))
		avio_close(ofmt_ctx_v->pb);

	avformat_free_context(ofmt_ctx_a);
	avformat_free_context(ofmt_ctx_v);


	if (ret < 0 && ret != AVERROR_EOF) {
		printf("Error occurred.\n");
		return -1;
	}
	return 0;
}

