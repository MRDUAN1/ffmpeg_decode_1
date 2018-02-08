#include "merge_vides_.h"
#include <qfileinfo.h>
extern QString outPutPath;
merge_vides_::merge_vides_(QObject *parent)
: commom_signal(parent)
{

}
void merge_vides_::set_filename(QString str2, QString strr)
{
	input_name__ = str_1 = str2;
	str_2 = strr;
	QFileInfo file(str_1);
	QString ss = file.fileName();
	int i = ss.indexOf(".");
	QString sp = ss.left(i);
	str_out = outPutPath + "/merge_" + sp + ".mkv";
}
void merge_vides_::get_filename(QString &str)
{
	str = str_1;
}
void merge_vides_::seek_stream(int64_t first, int64_t second)
{
	int p;
	if ((p = av_seek_frame(ifmt_ctx, -1, first * AV_TIME_BASE, AVSEEK_FLAG_ANY)) < 0)
	{
		fprintf(stderr, "%s: error while seeking/n", "wrong");
	}
	AVPacket packet; //= { .data = NULL, .size = 0 };
	packet.data = NULL;
	packet.size = 0;
	while (1)
	{
		av_read_frame(ifmt_ctx, &packet);
		if (packet.stream_index == 0)
		{
			if (packet.pts == AV_NOPTS_VALUE) continue;
			duration_1 = packet.pts;
			break;
		}
	}
	if ((p = av_seek_frame(ifmt_ctx, -1, 0 * AV_TIME_BASE, AVSEEK_FLAG_ANY)) < 0)
	{
		fprintf(stderr, "%s: error while seeking/n", "wrong");
	}
	if ((p = av_seek_frame(ifmt_ctx2, -1, second * AV_TIME_BASE, AVSEEK_FLAG_ANY)) < 0)
	{
		fprintf(stderr, "%s: error while seeking/n", "wrong");
	}
	packet.data = NULL;
	packet.size = 0;
	while (1)
	{
		av_read_frame(ifmt_ctx2, &packet);
		if (packet.stream_index == 0)
		{
			if (packet.pts == AV_NOPTS_VALUE) continue;
			duration_2 = packet.pts;
			break;
		}
	}
	if ((p = av_seek_frame(ifmt_ctx2, -1, 0 * AV_TIME_BASE, AVSEEK_FLAG_ANY)) < 0)
	{
		fprintf(stderr, "%s: error while seeking/n", "wrong");
	}
	emit length_all_merge_video_((duration_1 + duration_2));
}
int merge_vides_::start()
{
	int ret;
	int framecnt = 0, framecnt1 = 0;
	int vid_next_pts = 0;
	AVRational time_base_q = { 1, AV_TIME_BASE };
	int64_t last_dts_video, last_dts_audio;
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
	if ((ret = open_input_file(str_1.toLocal8Bit().data())) < 0)
		goto end;
	if ((ret = open_input_file2(str_2.toLocal8Bit().data())) < 0)
		goto end;
	seek_stream(ifmt_ctx->duration / AV_TIME_BASE - 1, ifmt_ctx2->duration/ AV_TIME_BASE - 1);
	//if ((ret = open_input_file2("Forrest_Gump_IMAX.mp4")) < 0)
	//	goto end;
	if ((ret = open_output_file(str_out.toLocal8Bit().data())) < 0)
		goto end;
	AVFrame *pframe;
	int dec_got_frame, enc_got_frame;
	AVPacket enc_pkt;
	int64_t start_time = av_gettime();
	int64_t ii;
	while (1) {
		AVStream *in_stream = NULL;
		AVStream *out_stream = NULL;

		ret = av_read_frame(ifmt_ctx, &packet);
		if (ret < 0) {
			av_log(NULL, AV_LOG_ERROR, "read frame error %d bbs.chinaffmpeg.com 孙悟空\n", ret);
			break;
		}
		pframe = av_frame_alloc();
		/******************************************************************/
		if (packet.stream_index == 0)
		{
			if (packet.pts == AV_NOPTS_VALUE) continue;
			
			else {emit length_onect_merge_video_(packet.pts);
			ii = packet.pts;

			}
			ret = avcodec_decode_video2(ifmt_ctx->streams[packet.stream_index]->codec, pframe,
				&dec_got_frame, &packet);
			if (dec_got_frame)
			{
				pframe->pts = av_frame_get_best_effort_timestamp(pframe);
				enc_pkt.data = NULL;
				enc_pkt.size = 0;
				av_init_packet(&enc_pkt);

				ret = avcodec_encode_video2(pCodecCtx, &enc_pkt, pframe, &enc_got_frame);
				if (enc_got_frame)
				{
					framecnt++;
					enc_pkt.stream_index = video_st->index;

					//Write PTS
					AVRational time_base = ofmt_ctx->streams[0]->time_base;//{ 1, 1000 };
					AVRational r_framerate1 = ifmt_ctx->streams[0]->r_frame_rate;//{ 50, 2 }; 
					//Duration between 2 frames (us)
					int64_t calc_duration = (double)(AV_TIME_BASE)*(1 / av_q2d(r_framerate1));	//内部时间戳
					//Parameters
					// enc_pkt.pts = (double)(framecnt*calc_duration)*(double)(av_q2d(time_base_q)) / (double)(av_q2d(time_base));
					enc_pkt.pts = av_rescale_q(framecnt*calc_duration, time_base_q, time_base);
					enc_pkt.dts = enc_pkt.pts;
					enc_pkt.duration = av_rescale_q(calc_duration, time_base_q, time_base); //(double)(calc_duration)*(double)(av_q2d(time_base_q)) / (double)(av_q2d(time_base));
					enc_pkt.pos = -1;
					//printf("video pts : %d\n", enc_pkt.pts);

					//vid_next_pts = framecnt*calc_duration; //general timebas
				}
				av_frame_free(&pframe);
			}
			else
				continue;
		}
		else
		{
			enc_pkt.data = NULL;
			enc_pkt.size = 0;
			av_init_packet(&enc_pkt);

			enc_pkt = packet;
		}
		/******************************************************************/
		if (enc_pkt.pts == AV_NOPTS_VALUE) {
			enc_pkt.pts = enc_pkt.dts;

		}

		in_stream = ifmt_ctx->streams[enc_pkt.stream_index];
		out_stream = ofmt_ctx->streams[enc_pkt.stream_index];

		enc_pkt.pts = av_rescale_q_rnd(enc_pkt.pts, in_stream->time_base, out_stream->time_base, AV_ROUND_NEAR_INF);
		enc_pkt.dts = av_rescale_q_rnd(enc_pkt.dts, in_stream->time_base, out_stream->time_base, AV_ROUND_NEAR_INF);
		enc_pkt.duration = av_rescale_q(enc_pkt.duration, in_stream->time_base, out_stream->time_base);
		enc_pkt.pos = -1;
		if (enc_pkt.stream_index == 0)
		{
			video_pts = enc_pkt.pts;
			video_dts = enc_pkt.dts;
		}
		else

		{
			audio_pts = enc_pkt.pts;
			audio_dts = enc_pkt.dts;
		}
		if (enc_pkt.stream_index == 0)
		{
			last_dts_video = enc_pkt.dts;
		}
		else last_dts_audio = enc_pkt.dts;
		ret = av_write_frame(ofmt_ctx, &enc_pkt);
		av_free_packet(&enc_pkt);
		//ret = av_write_frame(ofmt_ctx, &packet);
		if (ret < 0) {
			av_log(NULL, AV_LOG_ERROR, "bbs.chinaffmpeg.com 孙悟空 Muxing Error\n");
			break;
		}
	}
	//av_write_trailer(ofmt_ctx);
	//ofmt_ctx->duration = ifmt_ctx->duration;
	//return 1;
	int vid;
	int ps, ds, durationn;
	while (1) {
		AVStream *in_stream = NULL;
		AVStream *out_stream = NULL;

		ret = av_read_frame(ifmt_ctx2, &packet);

		if (ret < 0) {
			av_log(NULL, AV_LOG_ERROR, "read frame error %d bbs.chinaffmpeg.com 孙悟空\n", ret);
			break;
		}
		/******************************************************************/
		pframe = av_frame_alloc();
		if (packet.stream_index == 0)
		{
			if (packet.pts == AV_NOPTS_VALUE) continue;
			else emit length_onect_merge_video_((packet.pts + ii));
			ps = packet.pts;
			ds = packet.dts;
			durationn = packet.duration;
			ret = avcodec_decode_video2(ifmt_ctx2->streams[packet.stream_index]->codec, pframe,
				&dec_got_frame, &packet);
			if (dec_got_frame)
			{
				pframe->pts = av_frame_get_best_effort_timestamp(pframe);
				enc_pkt.data = NULL;
				enc_pkt.size = 0;
				av_init_packet(&enc_pkt);

				ret = avcodec_encode_video2(pCodecCtx, &enc_pkt, pframe, &enc_got_frame);
				if (enc_got_frame)
				{
					enc_pkt.duration = durationn;
					enc_pkt.dts = ds;
					enc_pkt.pts = ps;
					enc_pkt.pos = -1;
					/*framecnt1++;
					enc_pkt.stream_index = video_st->index;

					//Write PTS
					AVRational time_base = ofmt_ctx->streams[0]->time_base;//{ 1, 1000 };
					AVRational r_framerate1 = ifmt_ctx2->streams[0]->r_frame_rate;//{ 50, 2 };
					//Duration between 2 frames (us)
					int64_t calc_duration = (double)(AV_TIME_BASE)*(1 / av_q2d(r_framerate1));	//内部时间戳
					//Parameters
					// enc_pkt.pts = (double)(framecnt*calc_duration)*(double)(av_q2d(time_base_q)) / (double)(av_q2d(time_base));
					enc_pkt.pts = av_rescale_q(framecnt1*calc_duration, time_base_q, time_base);
					enc_pkt.dts = enc_pkt.pts;
					enc_pkt.duration = av_rescale_q(calc_duration, time_base_q, time_base); //(double)(calc_duration)*(double)(av_q2d(time_base_q)) / (double)(av_q2d(time_base));
					enc_pkt.pos = -1;
					vid_next_pts = framecnt1*calc_duration; //general timebas
					//Delay
					/*int64_t pts_time = av_rescale_q(enc_pkt.pts, time_base, time_base_q);
					int64_t now_time = av_gettime() - start_time;
					if ((pts_time > now_time) && ((vid_next_pts + pts_time - now_time) < aud_next_pts))
					av_usleep(pts_time - now_time);*/
				}
				av_frame_free(&pframe);
			}
			else
				continue;
		}
		else
		{

			enc_pkt.data = NULL;
			enc_pkt.size = 0;
			av_init_packet(&enc_pkt);

			enc_pkt = packet;
		}
		/******************************************************************/
		if (enc_pkt.pts == AV_NOPTS_VALUE) {
			enc_pkt.pts = enc_pkt.dts;

		}

		in_stream = ifmt_ctx2->streams[enc_pkt.stream_index];
		out_stream = ofmt_ctx->streams[enc_pkt.stream_index];

		vid = enc_pkt.pts = av_rescale_q_rnd(enc_pkt.pts, in_stream->time_base, out_stream->time_base, AV_ROUND_NEAR_INF);
		enc_pkt.dts = av_rescale_q_rnd(enc_pkt.dts, in_stream->time_base, out_stream->time_base, AV_ROUND_NEAR_INF);
		//packet.dts = packet.pts;
		enc_pkt.duration = av_rescale_q(enc_pkt.duration, in_stream->time_base, out_stream->time_base);
		enc_pkt.pos = -1;
		if (enc_pkt.stream_index == 0)
		{
			if (enc_pkt.pts < 0 || enc_pkt.dts < 0)
				continue;
			enc_pkt.pts = video_pts + vid;
			if (last_dts_video >= enc_pkt.dts + video_dts)
				enc_pkt.dts = enc_pkt.dts + video_dts + 1;
			else
				enc_pkt.dts = enc_pkt.dts + video_dts;
			if (enc_pkt.pts <= enc_pkt.dts)
				continue;
		}
		else
		{

			if (enc_pkt.pts < 0 || enc_pkt.dts < 0)
				continue;
			enc_pkt.dts = enc_pkt.pts = audio_pts + vid;

		}
		ret = av_interleaved_write_frame(ofmt_ctx, &enc_pkt);
		if (ret < 0) {
			av_log(NULL, AV_LOG_ERROR, "bbs.chinaffmpeg.com 孙悟空 Muxing Error\n");
			break;
		}
		av_free_packet(&enc_pkt);
		//av_free_packet(&packet);
	}
	//decode();
	av_write_trailer(ofmt_ctx);
	ofmt_ctx->duration = ifmt_ctx->duration + ifmt_ctx2->duration;
	

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

merge_vides_::~merge_vides_()
{

}
int merge_vides_::open_input_file2(const char*filename)
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
	av_dump_format(ifmt_ctx2, 0, filename, 0);
	return 0;
}

int merge_vides_::open_input_file(const char*filename)
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
	av_dump_format(ifmt_ctx, 0, filename, 0);
	return 0;
}
int merge_vides_::open(const char*filename){
	unsigned int i;
	int ret;
	ofmt_ctx = NULL;
	if (avformat_alloc_output_context2(&ofmt_ctx, NULL, NULL, filename) < 0) {
		av_log(NULL, AV_LOG_ERROR, "Cannot open the file %s bbs.chinaffmpeg.com 孙悟空\n", filename);
		return -ENOENT;
	}
	for (i = 0; i < ifmt_ctx->nb_streams; i++) {
		//根据输入流创建输出流（Create output AVStream according to input AVStream）
		AVStream *in_stream = ifmt_ctx->streams[i];
		AVStream *out_stream = avformat_new_stream(ofmt_ctx, in_stream->codec->codec);
		if (!out_stream) {
			printf("Failed allocating output stream\n");

		}
		//复制AVCodecContext的设置（Copy the settings of AVCodecContext）
		ret = avcodec_copy_context(out_stream->codec, in_stream->codec);
		if (ret < 0) {
			printf("Failed to copy context from input to output stream codec context\n");
			//goto end;
		}
		out_stream->codec->codec_tag = 0;
		if (ofmt_ctx->oformat->flags & AVFMT_GLOBALHEADER)
			out_stream->codec->flags |= CODEC_FLAG_GLOBAL_HEADER;
	}
	//输出一下格式------------------
	//av_dump_format(ofmt_ctx, 0, out_filename.data(), 1);
	//打开输出文件（Open output file）
	if (!(ofmt_ctx->flags & AVFMT_NOFILE)) {
		ret = avio_open(&ofmt_ctx->pb, filename, AVIO_FLAG_WRITE);
		if (ret < 0) {
			//printf("Could not open output file '%s'", out_filename);
			//goto end;
		}
	}
	//写文件头（Write file header）
	ret = avformat_write_header(ofmt_ctx, NULL);
	if (ret < 0) {
		printf("Error occurred when opening output file\n");
		//goto end;
	}
	return 1;
}
int merge_vides_::open_output_file(const char*filename)
{

	avformat_alloc_output_context2(&ofmt_ctx, NULL, NULL, filename);
	//output video encoder initialize
	pCodec = avcodec_find_encoder(AV_CODEC_ID_H264);
	if (!pCodec){
		printf("Can not find output video encoder! (没有找到合适的编码器！)\n");
		return -1;
	}
	pCodecCtx = avcodec_alloc_context3(pCodec);
	pCodecCtx->pix_fmt = PIX_FMT_YUV420P;
	pCodecCtx->width = /*ifmt_ctx->streams[0]->codec->width*/400;
	pCodecCtx->height = /*ifmt_ctx->streams[0]->codec->height*/200;
	pCodecCtx->time_base.num = 1;
	pCodecCtx->time_base.den = 25;
	pCodecCtx->bit_rate = 300000;
	pCodecCtx->gop_size = 250;
	/* Some formats want stream headers to be separate. */
	if (ofmt_ctx->oformat->flags & AVFMT_GLOBALHEADER)
		pCodecCtx->flags |= CODEC_FLAG_GLOBAL_HEADER;
	pCodecCtx->qmin = 10;
	pCodecCtx->qmax = 51;
	//Optional Param
	pCodecCtx->max_b_frames = 0;
	// Set H264 preset and tune
	AVDictionary *param = 0;
	av_dict_set(&param, "preset", "fast", 0);
	av_dict_set(&param, "tune", "zerolatency", 0);

	if (avcodec_open2(pCodecCtx, pCodec, &param) < 0){
		printf("Failed to open output video encoder! (编码器打开失败！)\n");
		return -1;
	}
	video_st = avformat_new_stream(ofmt_ctx, pCodec);
	if (video_st == NULL){
		return -1;
	}
	video_st->time_base.num = 1;
	video_st->time_base.den = 25;
	video_st->codec = pCodecCtx;
	pCodec_a = avcodec_find_encoder(AV_CODEC_ID_AAC);
	if (!pCodec_a){
		printf("Can not find output audio encoder! (没有找到合适的编码器！)\n");
		return -1;
	}
	pCodecCtx_a = avcodec_alloc_context3(pCodec_a);
	pCodecCtx_a->channels = 2;
	pCodecCtx_a->channel_layout = av_get_default_channel_layout(2);
	AVFormatContext * hh;
	if (ifmt_ctx->streams[1]->codec->sample_rate){
		hh = ifmt_ctx;
		pCodecCtx_a->sample_rate = hh->streams[1]->codec->sample_rate;
	}

	else if (ifmt_ctx2->streams[1]->codec->sample_rate){
		hh = ifmt_ctx2;
		pCodecCtx_a->sample_rate = hh->streams[1]->codec->sample_rate;
	}
	else
	{
		pCodecCtx_a->sample_rate = 44100;
	}
	//pCodecCtx_a->sample_rate = hh->streams[1]->codec->sample_rate;
	pCodecCtx_a->sample_fmt = pCodec_a->sample_fmts[0];
	pCodecCtx_a->bit_rate = 32000;
	pCodecCtx_a->time_base.num = 1;
	pCodecCtx_a->time_base.den = pCodecCtx_a->sample_rate;
	/** Allow the use of the experimental AAC encoder */
	pCodecCtx_a->strict_std_compliance = FF_COMPLIANCE_EXPERIMENTAL;
	/* Some formats want stream headers to be separate. */
	if (ofmt_ctx->oformat->flags & AVFMT_GLOBALHEADER)
		pCodecCtx_a->flags |= CODEC_FLAG_GLOBAL_HEADER;
	if (avcodec_open2(pCodecCtx_a, pCodec_a, NULL) < 0){
		printf("Failed to open ouput audio encoder! (编码器打开失败！)\n");
		return -1;
	}
	audio_st = avformat_new_stream(ofmt_ctx, pCodec_a);
	if (audio_st == NULL){
		return -1;
	}
	audio_st->time_base.num = 1;
	audio_st->time_base.den = pCodecCtx_a->sample_rate;
	audio_st->codec = pCodecCtx_a;

	//Open output URL,set before avformat_write_header() for muxing
	if (avio_open(&ofmt_ctx->pb, filename, AVIO_FLAG_READ_WRITE) < 0){
		printf("Failed to open output file! (输出文件打开失败！)\n");
		return -1;
	}
	//Write File Header
	avformat_write_header(ofmt_ctx, NULL);
	return 1;
}


