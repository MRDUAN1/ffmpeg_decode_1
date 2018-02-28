#include "decodec_higher.h"
#include <qstring.h>
#include <qevent.h>
#include "global.h"
#include "ffmpeg_interface.h"
static bool exit_thread = 0;
static int64_t maxxx; //最大的数据数据量
extern ffmpeg_interface *interface_;
decodec_higher::decodec_higher(QObject *parent)
: commom_signal(parent)
{

}
void seek_streamm(int64_t begin_point, int64_t end_point, AVFormatContext *ifmt_ctx)
{
	int p;
	enum AVMediaType type;

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
	maxxx = 0;
	int64_t current_pts_;
	int got_frame = 0;
	//int64_t max = 0;
	static int j = 0;
	int(*dec_func)(AVCodecContext *, AVFrame *, int*, const AVPacket *);
	while (1)
	{
		int io = av_read_frame(ifmt_ctx, &packet);
		if (packet.stream_index == 0) continue;
		int stream__ = packet.stream_index;
		int64_t current_pts_ = packet.pts;

		j++;
		if (j == 10) break;

		if (current_pts_ > maxxx) maxxx = current_pts_;
	}
	if ((p = av_seek_frame(ifmt_ctx, -1, begin_point * AV_TIME_BASE, AVSEEK_FLAG_ANY)) < 0)
	{
		fprintf(stderr, "%s: error while seeking/n", "wrong");
	}

}
decodec_higher::~decodec_higher()
{

}
void decodec_higher::get_input(QString input, QString out)
{
	input_name__ = in_filename = input;
	
	out_filename = out;
}

int decodec_higher::open_input_file(const char*filename)
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
char *dup_wchar_to_utf8(const wchar_t *w)
{
	char *s = NULL;
	int l = WideCharToMultiByte(CP_UTF8, 0, w, -1, 0, 0, 0, 0);
	s = (char *)av_malloc(l);
	if (s)
		WideCharToMultiByte(CP_UTF8, 0, w, -1, s, l, 0, 0);
	return s;
}

int flush_encoder(AVFormatContext *ifmt_ctx, AVFormatContext *ofmt_ctx, unsigned int stream_index, int framecnt);
int flush_encoder_a(AVFormatContext *ifmt_ctx_a, AVFormatContext *ofmt_ctx, unsigned int stream_index, int nb_samples);
int decodec_higher::apply_filters(AVFormatContext *ifmt_ctx)
{
	char args[512];
	int ret;
	AVFilterInOut *outputs = avfilter_inout_alloc();
	if (!outputs)
	{
		printf("Cannot alloc output\n");
		return -1;
	}
	AVFilterInOut *inputs = avfilter_inout_alloc();
	if (!inputs)
	{
		printf("Cannot alloc input\n");
		return -1;
	}

	if (filter_graph)
		avfilter_graph_free(&filter_graph);
	filter_graph = avfilter_graph_alloc();
	if (!filter_graph)
	{
		printf("Cannot create filter graph\n");
		return -1;
	}

	/* buffer video source: the decoded frames from the decoder will be inserted here. */
	snprintf(args, sizeof(args),
		"video_size=%dx%d:pix_fmt=%d:time_base=%d/%d:pixel_aspect=%d/%d",
		ifmt_ctx->streams[0]->codec->width, ifmt_ctx->streams[0]->codec->height, ifmt_ctx->streams[0]->codec->pix_fmt,
		ifmt_ctx->streams[0]->time_base.num, ifmt_ctx->streams[0]->time_base.den,
		ifmt_ctx->streams[0]->codec->sample_aspect_ratio.num, ifmt_ctx->streams[0]->codec->sample_aspect_ratio.den);

	ret = avfilter_graph_create_filter(&buffersrc_ctx, buffersrc, "in",
		args, NULL, filter_graph);
	if (ret < 0) {
		printf("Cannot create buffer source\n");
		return ret;
	}

	/* buffer video sink: to terminate the filter chain. */
	ret = avfilter_graph_create_filter(&buffersink_ctx, buffersink, "out",
		NULL, NULL, filter_graph);
	if (ret < 0) {
		printf("Cannot create buffer sink\n");
		return ret;
	}

	/* Endpoints for the filter graph. */
	outputs->name = av_strdup("in");
	outputs->filter_ctx = buffersrc_ctx;
	outputs->pad_idx = 0;
	outputs->next = NULL;

	inputs->name = av_strdup("out");
	inputs->filter_ctx = buffersink_ctx;
	inputs->pad_idx = 0;
	inputs->next = NULL;

	if ((ret = avfilter_graph_parse_ptr(filter_graph, filter_.data(),
		&inputs, &outputs, NULL)) < 0)
		return ret;

	if ((ret = avfilter_graph_config(filter_graph, NULL)) < 0)
		return ret;

	avfilter_inout_free(&inputs);
	avfilter_inout_free(&outputs);

	return 0;
}

void decodec_higher::set_filter(int i)
{

}
int decodec_higher::start()
{
	filter_graph = NULL;
	auto tree_file_ = global::return_decode_detail().find(in_filename.toLocal8Bit().data());
	if (tree_file_ == global::return_decode_detail().end())
		filter_ = "null";
	else
	{
		tree_file *temp_tree = tree_file_->second;
		filter_ = temp_tree->string_filter;
	}
	AVPacket *dec_pkt, enc_pkt;
	AVPacket *dec_pkt_a, enc_pkt_a;
	AVFrame *pframe, *pFrameYUV;
	struct SwsContext *img_convert_ctx;
	struct SwrContext *aud_convert_ctx;
	int framecnt = 0;
	int nb_samples = 0;
	int videoindex = 0;
	int audioindex = 1;
	int i;
	int ret;
	HANDLE  hThread;
	int dec_got_frame, enc_got_frame;
	int dec_got_frame_a, enc_got_frame_a;

	int aud_next_pts = 0;
	int vid_next_pts = 0;
	int encode_video = 1, encode_audio = 1;

	AVRational time_base_q = { 1, AV_TIME_BASE };
	AVBitStreamFilterContext *vbsf = av_bitstream_filter_init("h264_mp4toannexb");
	av_register_all();
	//Register Device
	avdevice_register_all();
	avformat_network_init();
	open_input_file(in_filename.toLocal8Bit().data());
#if USEFILTER
	//Register Filter
	avfilter_register_all();
	buffersrc = avfilter_get_by_name("buffer");
	buffersink = avfilter_get_by_name("buffersink");
#endif
	avformat_alloc_output_context2(&ofmt_ctx, NULL, NULL, out_filename.toLocal8Bit().data());
	//output video encoder initialize
	pCodec = avcodec_find_encoder(AV_CODEC_ID_H264);
	if (!pCodec){
		printf("Can not find output video encoder! (没有找到合适的编码器！)\n");
		return -1;
	}
	pCodecCtx = avcodec_alloc_context3(pCodec);
	pCodecCtx->pix_fmt = PIX_FMT_YUV420P;
	pCodecCtx->width = ifmt_ctx->streams[videoindex]->codec->width;
	pCodecCtx->height = ifmt_ctx->streams[videoindex]->codec->height;
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
	pCodecCtx_a->sample_rate = ifmt_ctx->streams[audioindex]->codec->sample_rate;
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
	if (avio_open(&ofmt_ctx->pb, out_filename.toLocal8Bit().data(), AVIO_FLAG_READ_WRITE) < 0){
		printf("Failed to open output file! (输出文件打开失败！)\n");
		return -1;
	}
	//int iy = av_opt_set(ofmt_ctx->priv_data, "localport", "5555", AV_OPT_SEARCH_CHILDREN);
	//Write File Header
	avformat_write_header(ofmt_ctx, NULL);

	//prepare before decode and encode
	dec_pkt = (AVPacket *)av_malloc(sizeof(AVPacket));

	//#if USEFILTER
	//#else
	//camera data may has a pix fmt of RGB or sth else,convert it to YUV420
	img_convert_ctx = sws_getContext(ifmt_ctx->streams[videoindex]->codec->width, ifmt_ctx->streams[videoindex]->codec->height,
		ifmt_ctx->streams[videoindex]->codec->pix_fmt, pCodecCtx->width, pCodecCtx->height, PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);

	// Initialize the resampler to be able to convert audio sample formats
	aud_convert_ctx = swr_alloc_set_opts(NULL,
		av_get_default_channel_layout(pCodecCtx_a->channels),
		pCodecCtx_a->sample_fmt,
		pCodecCtx_a->sample_rate,
		av_get_default_channel_layout(ifmt_ctx->streams[audioindex]->codec->channels),
		ifmt_ctx->streams[audioindex]->codec->sample_fmt,
		ifmt_ctx->streams[audioindex]->codec->sample_rate,
		0, NULL);
	swr_init(aud_convert_ctx);


	//#endif
	//Initialize the buffer to store YUV frames to be encoded.
	pFrameYUV = av_frame_alloc();
	uint8_t *out_buffer = (uint8_t *)av_malloc(avpicture_get_size(PIX_FMT_YUV420P, pCodecCtx->width, pCodecCtx->height));
	avpicture_fill((AVPicture *)pFrameYUV, out_buffer, PIX_FMT_YUV420P, pCodecCtx->width, pCodecCtx->height);

	//Initialize the FIFO buffer to store audio samples to be encoded. 
	AVAudioFifo *fifo = NULL;
	fifo = av_audio_fifo_alloc(pCodecCtx_a->sample_fmt, pCodecCtx_a->channels, 1);

	//Initialize the buffer to store converted samples to be encoded.
	uint8_t **converted_input_samples = NULL;
	/**
	* Allocate as many pointers as there are audio channels.
	* Each pointer will later point to the audio samples of the corresponding
	* channels (although it may be NULL for interleaved formats).
	*/
	if (!(converted_input_samples = (uint8_t**)calloc(pCodecCtx_a->channels,
		sizeof(**converted_input_samples)))) {
		printf("Could not allocate converted input sample pointers\n");
		return AVERROR(ENOMEM);
	}
	seek_streamm(0, (ifmt_ctx->duration) / 1000000 - 2, ifmt_ctx);
	int64_t start_time = av_gettime();
	//input_name = in_filename.toLocal8Bit();
	int len = 0;
	emit length_all_merge_video_(maxxx - 10000);
	while (1)
	{
		if ((ret = av_read_frame(ifmt_ctx, dec_pkt)) < 0)
			break;
		if (exit_thread)
			break;
		if (dec_pkt->stream_index == 0)
		{
			av_bitstream_filter_filter(vbsf, ifmt_ctx->streams[videoindex]->codec, NULL, &dec_pkt->data, &dec_pkt->size, dec_pkt->data, dec_pkt->size, 0);
			av_log(NULL, AV_LOG_DEBUG, "Going to reencode the frame\n");
			pframe = av_frame_alloc();
			if (!pframe) {
				ret = AVERROR(ENOMEM);
				return ret;
			}
			ret = avcodec_decode_video2(ifmt_ctx->streams[dec_pkt->stream_index]->codec, pframe,
				&dec_got_frame, dec_pkt);
			if (ret < 0) {
				av_frame_free(&pframe);
				av_log(NULL, AV_LOG_ERROR, "Decoding failed\n");
				break;
			}
			if (dec_got_frame){
#if USEFILTER
				pframe->pts = av_frame_get_best_effort_timestamp(pframe);
				apply_filters(ifmt_ctx);
				//filter_change = 0;
				/* push the decoded frame into the filtergraph */
				if (av_buffersrc_add_frame(buffersrc_ctx, pframe) < 0) {
					printf("Error while feeding the filtergraph\n");
					break;
				}
				picref = av_frame_alloc();

				/* pull filtered pictures from the filtergraph */
				while (1) {
					ret = av_buffersink_get_frame_flags(buffersink_ctx, picref, 0);
					if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
						break;
					if (ret < 0)
						return ret;

					if (picref) {
						img_convert_ctx = sws_getContext(picref->width, picref->height, (AVPixelFormat)picref->format, pCodecCtx->width, pCodecCtx->height, AV_PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);
						sws_scale(img_convert_ctx, (const uint8_t* const*)picref->data, picref->linesize, 0, pCodecCtx->height, pFrameYUV->data, pFrameYUV->linesize);
						sws_freeContext(img_convert_ctx);
						pFrameYUV->width = picref->width;
						pFrameYUV->height = picref->height;
						pFrameYUV->format = PIX_FMT_YUV420P;
#else
				sws_scale(img_convert_ctx, (const uint8_t* const*)pframe->data, pframe->linesize, 0, pCodecCtx->height, pFrameYUV->data, pFrameYUV->linesize);
				pFrameYUV->width = pframe->width;
				pFrameYUV->height = pframe->height;
				pFrameYUV->format = PIX_FMT_YUV420P;
#endif					
				enc_pkt.data = NULL;
				enc_pkt.size = 0;
				av_init_packet(&enc_pkt);
				ret = avcodec_encode_video2(pCodecCtx, &enc_pkt, pFrameYUV, &enc_got_frame);
				av_frame_free(&pframe);
				if (enc_got_frame == 1){
					//printf("Succeed to encode frame: %5d\tsize:%5d\n", framecnt, enc_pkt.size);
					framecnt++;
					enc_pkt.stream_index = video_st->index;
					
					//Write PTS
					AVRational time_base = ofmt_ctx->streams[0]->time_base;//{ 1, 1000 };
					AVRational r_framerate1 = ifmt_ctx->streams[videoindex]->r_frame_rate;//{ 50, 2 }; 
					//Duration between 2 frames (us)
					int64_t calc_duration = (double)(AV_TIME_BASE)*(1 / av_q2d(r_framerate1));	//内部时间戳
					//Parameters
					// enc_pkt.pts = (double)(framecnt*calc_duration)*(double)(av_q2d(time_base_q)) / (double)(av_q2d(time_base));
					enc_pkt.pts = av_rescale_q(framecnt*calc_duration, time_base_q, time_base);
					enc_pkt.dts = enc_pkt.pts;
					enc_pkt.duration = av_rescale_q(calc_duration, time_base_q, time_base); //(double)(calc_duration)*(double)(av_q2d(time_base_q)) / (double)(av_q2d(time_base));
					enc_pkt.pos = -1;
					//printf("video pts : %d\n", enc_pkt.pts);

					vid_next_pts = framecnt*calc_duration; //general timebase

					//Delay
					int64_t pts_time = av_rescale_q(enc_pkt.pts, time_base, time_base_q);
					int64_t now_time = av_gettime() - start_time;
					if ((pts_time > now_time) && ((vid_next_pts + pts_time - now_time) < aud_next_pts))
						av_usleep(pts_time - now_time);

					ret = av_interleaved_write_frame(ofmt_ctx, &enc_pkt);
					av_free_packet(&enc_pkt);
				}
#if USEFILTER
				av_frame_unref(picref);
			}
		}
#endif
	}
	else {
		av_frame_free(&pframe);
	}
	av_free_packet(dec_pkt);
}


	else if (dec_pkt->stream_index == 1)
	{
		//audio trancoding here
		
			len++;
			if (len == 10)
			{

				//now_length = dec_pkt->pts;

				//input_name = in_filename.toLocal8Bit();
				emit length_onect_merge_video_(dec_pkt->pts);
				//QApplication::postEvent(interface_, new QEvent(update_length));
				len = 0;
			
		}
		const int output_frame_size = pCodecCtx_a->frame_size;

		if (exit_thread)
			break;

		/**
		* Make sure that there is one frame worth of samples in the FIFO
		* buffer so that the encoder can do its work.
		* Since the decoder's and the encoder's frame size may differ, we
		* need to FIFO buffer to store as many frames worth of input samples
		* that they make up at least one frame worth of output samples.
		*/
		while (av_audio_fifo_size(fifo) < output_frame_size) {
			/**
			* Decode one frame worth of audio samples, convert it to the
			* output sample format and put it into the FIFO buffer.
			*/
			AVFrame *input_frame = av_frame_alloc();
			if (!input_frame)
			{
				ret = AVERROR(ENOMEM);
				return ret;
			}
			if ((ret = avcodec_decode_audio4(ifmt_ctx->streams[audioindex]->codec, input_frame,
				&dec_got_frame_a, dec_pkt)) < 0) {
				printf("Could not decode audio frame\n");
				return ret;
			}
			av_packet_unref(dec_pkt);
			/** If there is decoded data, convert and store it */
			if (dec_got_frame_a) {
				/**
				* Allocate memory for the samples of all channels in one consecutive
				* block for convenience.
				*/
				if ((ret = av_samples_alloc(converted_input_samples, NULL,
					pCodecCtx_a->channels,
					input_frame->nb_samples,
					pCodecCtx_a->sample_fmt, 0)) < 0) {
					printf("Could not allocate converted input samples\n");
					av_freep(&(*converted_input_samples)[0]);
					free(*converted_input_samples);
					return ret;
				}

				/**
				* Convert the input samples to the desired output sample format.
				* This requires a temporary storage provided by converted_input_samples.
				*/
				/** Convert the samples using the resampler. */
				if ((ret = swr_convert(aud_convert_ctx,
					converted_input_samples, input_frame->nb_samples,
					(const uint8_t**)input_frame->extended_data, input_frame->nb_samples)) < 0) {
					printf("Could not convert input samples\n");
					return ret;
				}

				/** Add the converted input samples to the FIFO buffer for later processing. */
				/**
				* Make the FIFO as large as it needs to be to hold both,
				* the old and the new samples.
				*/
				if ((ret = av_audio_fifo_realloc(fifo, av_audio_fifo_size(fifo) + input_frame->nb_samples)) < 0) {
					printf("Could not reallocate FIFO\n");
					return ret;
				}

				/** Store the new samples in the FIFO buffer. */
				if (av_audio_fifo_write(fifo, (void **)converted_input_samples,
					input_frame->nb_samples) < input_frame->nb_samples) {
					printf("Could not write data to FIFO\n");
					return AVERROR_EXIT;
				}
			}
			av_frame_unref(input_frame);
		}

		/**
		* If we have enough samples for the encoder, we encode them.
		* At the end of the file, we pass the remaining samples to
		* the encoder.
		*/
		if (av_audio_fifo_size(fifo) >= output_frame_size)
			/**
			* Take one frame worth of audio samples from the FIFO buffer,
			* encode it and write it to the output file.
			*/
		{
			/** Temporary storage of the output samples of the frame written to the file. */
			AVFrame *output_frame = av_frame_alloc();
			if (!output_frame)
			{
				ret = AVERROR(ENOMEM);
				return ret;
			}
			/**
			* Use the maximum number of possible samples per frame.
			* If there is less than the maximum possible frame size in the FIFO
			* buffer use this number. Otherwise, use the maximum possible frame size
			*/
			const int frame_size = FFMIN(av_audio_fifo_size(fifo),
				pCodecCtx_a->frame_size);

			/** Initialize temporary storage for one output frame. */
			/**
			* Set the frame's parameters, especially its size and format.
			* av_frame_get_buffer needs this to allocate memory for the
			* audio samples of the frame.
			* Default channel layouts based on the number of channels
			* are assumed for simplicity.
			*/
			output_frame->nb_samples = frame_size;
			output_frame->channel_layout = pCodecCtx_a->channel_layout;
			output_frame->format = pCodecCtx_a->sample_fmt;
			output_frame->sample_rate = pCodecCtx_a->sample_rate;

			/**
			* Allocate the samples of the created frame. This call will make
			* sure that the audio frame can hold as many samples as specified.
			*/
			if ((ret = av_frame_get_buffer(output_frame, 0)) < 0) {
				printf("Could not allocate output frame samples\n");
				av_frame_free(&output_frame);
				return ret;
			}

			/**
			* Read as many samples from the FIFO buffer as required to fill the frame.
			* The samples are stored in the frame temporarily.
			*/
			if (av_audio_fifo_read(fifo, (void **)output_frame->data, frame_size) < frame_size) {
				printf("Could not read data from FIFO\n");
				return AVERROR_EXIT;
			}

			/** Encode one frame worth of audio samples. */
			/** Packet used for temporary storage. */
			AVPacket output_packet;
			av_init_packet(&output_packet);
			output_packet.data = NULL;
			output_packet.size = 0;

			/** Set a timestamp based on the sample rate for the container. */
			if (output_frame) {
				nb_samples += output_frame->nb_samples;
			}

			/**
			* Encode the audio frame and store it in the temporary packet.
			* The output audio stream encoder is used to do this.
			*/
			if ((ret = avcodec_encode_audio2(pCodecCtx_a, &output_packet,
				output_frame, &enc_got_frame_a)) < 0) {
				printf("Could not encode frame\n");
				av_packet_unref(&output_packet);
				return ret;
			}

			/** Write one audio frame from the temporary packet to the output file. */
			if (enc_got_frame_a) {

				output_packet.stream_index = 1;

				AVRational time_base = ofmt_ctx->streams[1]->time_base;
				AVRational r_framerate1 = { ifmt_ctx->streams[audioindex]->codec->sample_rate, 1 };// { 44100, 1};  
				int64_t calc_duration = (double)(AV_TIME_BASE)*(1 / av_q2d(r_framerate1));  //内部时间戳  

				output_packet.pts = av_rescale_q(nb_samples*calc_duration, time_base_q, time_base);
				output_packet.dts = output_packet.pts;
				output_packet.duration = output_frame->nb_samples;

				//printf("audio pts : %d\n", output_packet.pts);
				aud_next_pts = nb_samples*calc_duration;

				int64_t pts_time = av_rescale_q(output_packet.pts, time_base, time_base_q);
				int64_t now_time = av_gettime() - start_time;
				if ((pts_time > now_time) && ((aud_next_pts + pts_time - now_time)<vid_next_pts))
					av_usleep(pts_time - now_time);
				Sleep(10);
				if ((ret = av_interleaved_write_frame(ofmt_ctx, &output_packet)) < 0) {
					printf("Could not write frame\n");
					av_packet_unref(&output_packet);
					return ret;
				}

				av_packet_unref(&output_packet);
			}
			av_frame_free(&output_frame);
		}
	}
	else if (ret == AVERROR_EOF)
	{

		encode_video = 0;
		continue;
	}
	else
	{
		break;
		printf("Could not read video frame\n");
		return ret;
	}
  }


  //Flush Encoder
  /*ret = flush_encoder(ifmt_ctx, ofmt_ctx, 0, framecnt);
  if (ret < 0) {
	  printf("Flushing encoder failed\n");
	  return -1;
  }
  ret = flush_encoder_a(ifmt_ctx, ofmt_ctx, 1, nb_samples);
  if (ret < 0) {
	  printf("Flushing encoder failed\n");
	  return -1;
  }*/



  //Write file trailer
  av_write_trailer(ofmt_ctx);
  return 0;
cleanup:
  //Clean
#if USEFILTER
  if (filter_graph)
	  avfilter_graph_free(&filter_graph);
#endif
  if (video_st)
	  avcodec_close(video_st->codec);
  if (audio_st)
	  avcodec_close(audio_st->codec);
  av_free(out_buffer);
  if (converted_input_samples) {
	  av_freep(&converted_input_samples[0]);
	  //free(converted_input_samples);
  }
  if (fifo)
	  av_audio_fifo_free(fifo);
  avio_close(ofmt_ctx->pb);
  //avformat_free_context(ifmt_ctx);
  avformat_free_context(ifmt_ctx);
  avformat_free_context(ofmt_ctx);
 
  return 0;
}

int decodec_higher::flush_encoder(AVFormatContext *ifmt_ctx, AVFormatContext *ofmt_ctx, unsigned int stream_index, int framecnt){
	int ret;
	int got_frame;
	AVPacket enc_pkt;
	if (!(ofmt_ctx->streams[stream_index]->codec->codec->capabilities &
		CODEC_CAP_DELAY))
		return 0;
	while (1) {
		enc_pkt.data = NULL;
		enc_pkt.size = 0;
		av_init_packet(&enc_pkt);
		ret = avcodec_encode_video2(ofmt_ctx->streams[stream_index]->codec, &enc_pkt,
			NULL, &got_frame);
		av_frame_free(NULL);
		if (ret < 0)
			break;
		if (!got_frame){
			ret = 0;
			break;
		}
		printf("Flush Encoder: Succeed to encode 1 frame!\tsize:%5d\n", enc_pkt.size);
		framecnt++;
		//Write PTS
		AVRational time_base = ofmt_ctx->streams[stream_index]->time_base;//{ 1, 1000 };
		AVRational r_framerate1 = ifmt_ctx->streams[0]->r_frame_rate;// { 50, 2 };
		AVRational time_base_q = { 1, AV_TIME_BASE };
		//Duration between 2 frames (us)
		int64_t calc_duration = (double)(AV_TIME_BASE)*(1 / av_q2d(r_framerate1));	//内部时间戳
		//Parameters
		enc_pkt.pts = av_rescale_q(framecnt*calc_duration, time_base_q, time_base);
		enc_pkt.dts = enc_pkt.pts;
		enc_pkt.duration = av_rescale_q(calc_duration, time_base_q, time_base);

		/* copy packet*/
		//转换PTS/DTS（Convert PTS/DTS）
		enc_pkt.pos = -1;

		//ofmt_ctx->duration = enc_pkt.duration * framecnt;

		/* mux encoded frame */
		ret = av_interleaved_write_frame(ofmt_ctx, &enc_pkt);
		if (ret < 0)
			break;
	}
	return ret;
}

int decodec_higher::flush_encoder_a(AVFormatContext *ifmt_ctx_a, AVFormatContext *ofmt_ctx, unsigned int stream_index, int nb_samples){
	int ret;
	int got_frame;
	AVPacket enc_pkt;
	if (!(ofmt_ctx->streams[stream_index]->codec->codec->capabilities &
		CODEC_CAP_DELAY))
		return 0;
	while (1) {
		enc_pkt.data = NULL;
		enc_pkt.size = 0;
		av_init_packet(&enc_pkt);
		ret = avcodec_encode_audio2(ofmt_ctx->streams[stream_index]->codec, &enc_pkt,
			NULL, &got_frame);
		av_frame_free(NULL);
		if (ret < 0)
			break;
		if (!got_frame){
			ret = 0;
			break;
		}
		printf("Flush Encoder: Succeed to encode 1 frame!\tsize:%5d\n", enc_pkt.size);
		nb_samples += 1024;
		//Write PTS
		AVRational time_base = ofmt_ctx->streams[stream_index]->time_base;//{ 1, 1000 };
		AVRational r_framerate1 = { ifmt_ctx->streams[0]->codec->sample_rate, 1 };
		AVRational time_base_q = { 1, AV_TIME_BASE };
		//Duration between 2 frames (us)
		int64_t calc_duration = (double)(AV_TIME_BASE)*(1 / av_q2d(r_framerate1));	//内部时间戳
		//Parameters
		enc_pkt.pts = av_rescale_q(nb_samples*calc_duration, time_base_q, time_base);
		enc_pkt.dts = enc_pkt.pts;
		enc_pkt.duration = 1024;

		/* copy packet*/
		//转换PTS/DTS（Convert PTS/DTS）
		enc_pkt.pos = -1;

		//ofmt_ctx->duration = enc_pkt.duration * nb_samples;

		/* mux encoded frame */
		ret = av_interleaved_write_frame(ofmt_ctx, &enc_pkt);
		if (ret < 0)
			break;
	}
	return ret;
}
