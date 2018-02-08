#include "camera_specifics.h"
#include <process.h>
#include "DS_AudioVideoDevices.h"
#include <vector>
using std::string;
static bool exit_thread = 0;
static bool filter_change = 1;
static SDL_Event event1;
static SDL_AudioSpec wanted_spec;
static Uint8  *audio_chunk;
static Uint32  audio_len;
static Uint8  *audio_pos;
static bool thread_exit;
int camera_specifics::init_audio()
{
	uint64_t out_channel_layout = AV_CH_LAYOUT_STEREO;
	int out_nb_samples = 1024;
	AVSampleFormat out_sample_fmt = AV_SAMPLE_FMT_S16;
	int out_sample_rate = 44100;
	int out_channels = av_get_channel_layout_nb_channels(out_channel_layout);
	//Out Buffer Size
	int out_buffer_size = av_samples_get_buffer_size(NULL, out_channels, out_nb_samples, out_sample_fmt, 1);
	uint8_t *out_buffer1 = (uint8_t *)av_malloc(192000 * 2);

	wanted_spec.freq = out_sample_rate;
	wanted_spec.format = AUDIO_S16SYS;
	wanted_spec.channels = out_channels;
	wanted_spec.silence = 0;
	wanted_spec.samples = out_nb_samples;
	wanted_spec.callback = fill_audio;
	wanted_spec.userdata = ifmt_ctx_a->streams[0]->codec;
	if (SDL_OpenAudio(&wanted_spec, NULL)<0){
		printf("can't open audio.\n");
		return -1;
	}
	int index = 0;
}
//设置退出
void camera_specifics::set_exit()
{
	thread_exit = 1;
}
int camera_specifics::sfp_refresh_thread(void *opaque){
	thread_exit = 0;
	while (!thread_exit) {
		SDL_Event event;
		event.type = SFM_REFRESH_EVENT;
		SDL_PushEvent(&event);
		SDL_Delay(0);
	}
	SDL_Event event;
	event.type = SFM_BREAK_EVENT;
	SDL_PushEvent(&event);
	return 0;
}
void camera_specifics::fill_audio(void *udata, Uint8 *stream, int len)
{
	if (audio_len == 0)		/*  Only  play  if  we  have  data  left  */
		return;
	len = (len>audio_len ? audio_len : len);	/*  Mix  as  much  data  as  possible  */

	SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME);
	audio_pos += len;
	audio_len -= len;
}
int camera_specifics::sdl_init()
{
	
	HWND i = wid;
	
	AVFrame	*pFrame, *pFrameYUV;
	pFrame = avcodec_alloc_frame();
	pFrameYUV = avcodec_alloc_frame();
	uint8_t *out_buffer = (uint8_t *)av_malloc(avpicture_get_size(PIX_FMT_YUV420P, ifmt_ctx_video->streams[0]->codec->width, ifmt_ctx_video->streams[0]->codec->height));
	avpicture_fill((AVPicture *)pFrameYUV, out_buffer, PIX_FMT_YUV420P, ifmt_ctx_video->streams[0]->codec->width, ifmt_ctx_video->streams[0]->codec->height);
	//SDL----------------------------
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
		printf("Could not initialize SDL - %s\n", SDL_GetError());
		return -1;
	}
	//int screen_w = 0, screen_h = 0;
	
	//HWND i = (HWND)->winId();
	pwindow = SDL_CreateWindowFrom((void*)wid);
	window_w = ifmt_ctx_video->streams[0]->codec->width;
	window_h = ifmt_ctx_video->streams[0]->codec->height;
	prenderer = SDL_CreateRenderer(pwindow, -1, 0);
	ptexture = SDL_CreateTexture(prenderer,
		SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STREAMING,
		window_w, window_h);
	//新建线程运行刷新函数
	SDL_CreateThread(sfp_refresh_thread, "refresh func", NULL);
}
void camera_specifics::set_hwnd(HWND widd)
{
	wid = widd;
}
camera_specifics::camera_specifics(QObject *parent)
	: QObject(parent)
{
	filter_graph = NULL;
	filter_change_str = "null";
	exit_thread = 0;
	filter_change = 1;
	buffersink_ctx = NULL;
	buffersrc_ctx = NULL;
	filter_graph = NULL;
	buffersrc = NULL;
	buffersink = NULL;
	thread_exit = 0;
	
}
void camera_specifics::set_filter_change(string change, HWND wind)
{
	filter_change_str = change;
	filter_change = 1;
	wid = wind;
}
void show_dshow_device(){
	AVFormatContext *pFmtCtx = avformat_alloc_context();
	AVDictionary* options = NULL;
	av_dict_set(&options, "list_devices", "true", 0);
	AVInputFormat *iformat = av_find_input_format("dshow");
	printf("Device Info=============\n");
	avformat_open_input(&pFmtCtx, "video=dummy", iformat, &options);
	printf("========================\n");
}
static void MyThreadFunction(void *)
{

}
camera_specifics::~camera_specifics()
{

}
int camera_specifics::apply_filters()
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
		ifmt_ctx_video->streams[0]->codec->width, ifmt_ctx_video->streams[0]->codec->height, ifmt_ctx_video->streams[0]->codec->pix_fmt,
		ifmt_ctx_video->streams[0]->time_base.num, ifmt_ctx_video->streams[0]->time_base.den,
		ifmt_ctx_video->streams[0]->codec->sample_aspect_ratio.num, ifmt_ctx_video->streams[0]->codec->sample_aspect_ratio.den);

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
	//+		filter_change_str	"movie=9302-106.jpg,colorkey=0x000000:0.1:0.4[wm];[in][wm]overlay=11:11[out]"	std::basic_string<char,std::char_traits<char>,std::allocator<char> >

	if ((ret = avfilter_graph_parse_ptr(filter_graph, filter_change_str.data(),
		&inputs, &outputs, NULL)) < 0)
	{
		
		return ret;
	}
	if ((ret = avfilter_graph_config(filter_graph, NULL)) < 0)
		return ret;

	avfilter_inout_free(&inputs);
	avfilter_inout_free(&outputs);

	return 0;
}
void camera_specifics::copy_out_path(QString str)
{
	out_path = str.toStdString();
}
int camera_specifics::start()
{
	SDL_Event event;
	int out_buffer_size;
	int out_channels = av_get_channel_layout_nb_channels(AV_CH_LAYOUT_STEREO);
	
	AVFormatContext *ifmt_ctx = NULL;
	ifmt_ctx_a = NULL;
	AVFormatContext *ofmt_ctx;
	AVInputFormat* ifmt;
	AVStream* video_st;
	AVStream* audio_st;
	AVCodecContext* pCodecCtx;
	AVCodecContext* pCodecCtx_a;
	AVCodec* pCodec;
	AVCodec* pCodec_a;
	AVPacket *dec_pkt, enc_pkt;
	AVPacket *dec_pkt_a, enc_pkt_a;
	AVFrame *pframe, *pFrameYUV;
	struct SwsContext *img_convert_ctx;
	struct SwrContext *aud_convert_ctx;

	
	char device_name[180] = { 0 };
	char device_name_a[180] = { 0 };
	int framecnt = 0;
	int nb_samples = 0;
	int videoindex;
	int audioindex;
	int i;
	int ret;
	HANDLE  hThread;

	
//	const char* out_path = "./fhjghf.mp4";
	
	int dec_got_frame, enc_got_frame;
	int dec_got_frame_a, enc_got_frame_a;

	int aud_next_pts = 0;
	int vid_next_pts = 0;
	int encode_video = 1, encode_audio = 1;

	AVRational time_base_q = { 1, AV_TIME_BASE };

	av_register_all();
	//Register Device
	avdevice_register_all();
	avformat_network_init();
#if USEFILTER
	//Register Filter
	avfilter_register_all();
	buffersrc = avfilter_get_by_name("buffer");
	buffersink = avfilter_get_by_name("buffersink");
#endif
	std::vector<TDeviceName>stdd;
	char temporary_video_str[180] = { '\0' };
	DS_GetAudioVideoInputDevices(stdd, CLSID_VideoInputDeviceCategory);
	//获取设备名
	WideCharToMultiByte(CP_ACP, 0, stdd[0].MonikerName, -1, device_name, 180, NULL, NULL);
	sprintf(temporary_video_str, "video=%s", device_name);
	string final_video_str(temporary_video_str);
//	int video_length_str = final_video_str.size();
	int video_now_length_str = 0;
	while (1)
	{
		video_now_length_str = final_video_str.find(':', video_now_length_str);
		if (video_now_length_str == -1) break;
		final_video_str[video_now_length_str] = '_';
	}
	stdd.clear();
	char audio[180] = { '\0' };
	DS_GetAudioVideoInputDevices(stdd, CLSID_AudioInputDeviceCategory);
	WideCharToMultiByte(CP_ACP, 0, stdd[0].MonikerName, -1, device_name_a, 180, NULL, NULL);
	sprintf(audio, "audio=%s", device_name_a);
	//memcpy(device_name_a, device_name_a, 99);
	string final_audio_str(audio);
	//int gg = str.size();
	int audio_now_length_str = 0;
	while (1)
	{
		audio_now_length_str = final_audio_str.find(':', audio_now_length_str);
		if (audio_now_length_str == -1) break;
		final_audio_str[audio_now_length_str] = '_';
	}
	ifmt = av_find_input_format("dshow");
	// Set device params
	AVDictionary *device_param = 0;
	if (avformat_open_input(&ifmt_ctx, final_video_str.data(), ifmt, &device_param) != 0){

		printf("Couldn't open input video stream.（无法打开输入流）\n");
		return -1;
	}
	if (avformat_open_input(&ifmt_ctx_a, final_audio_str.data(), ifmt, &device_param) != 0){

		printf("Couldn't open input audio stream.（无法打开输入流）\n");
		return -1;
	}
	//input video initialize
	if (avformat_find_stream_info(ifmt_ctx, NULL) < 0)
	{
		printf("Couldn't find video stream information.（无法获取流信息）\n");
		return -1;
	}
	videoindex = -1;
	for (i = 0; i < ifmt_ctx->nb_streams; i++)
	if (ifmt_ctx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
	{
		videoindex = i;
		break;
	}
	if (videoindex == -1)
	{
		printf("Couldn't find a video stream.（没有找到视频流）\n");
		return -1;
	}
	if (avcodec_open2(ifmt_ctx->streams[videoindex]->codec, avcodec_find_decoder(ifmt_ctx->streams[videoindex]->codec->codec_id), NULL) < 0)
	{
		printf("Could not open video codec.（无法打开解码器）\n");
		return -1;
	}
	ifmt_ctx_video = ifmt_ctx;
	//input audio initialize
	if (avformat_find_stream_info(ifmt_ctx_a, NULL) < 0)
	{
		printf("Couldn't find audio stream information.（无法获取流信息）\n");
		return -1;
	}
	audioindex = -1;
	for (i = 0; i < ifmt_ctx_a->nb_streams; i++)
	if (ifmt_ctx_a->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO)
	{
		audioindex = i;
		break;
	}
	if (audioindex == -1)
	{
		printf("Couldn't find a audio stream.（没有找到视频流）\n");
		return -1;
	}
	if (avcodec_open2(ifmt_ctx_a->streams[audioindex]->codec, avcodec_find_decoder(ifmt_ctx_a->streams[audioindex]->codec->codec_id), NULL) < 0)
	{
		printf("Could not open audio codec.（无法打开解码器）\n");
		return -1;
	}
	sdl_init();
	//init_audio();
	ofmt_ctx = NULL;
	avformat_alloc_output_context2(&ofmt_ctx, NULL, NULL, out_path.data());
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
	pCodecCtx_a->sample_rate = ifmt_ctx_a->streams[audioindex]->codec->sample_rate;
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
	if (avio_open(&ofmt_ctx->pb, out_path.data(), AVIO_FLAG_READ_WRITE) < 0){
		printf("Failed to open output file! (输出文件打开失败！)\n");
		return -1;
	}
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
		av_get_default_channel_layout(ifmt_ctx_a->streams[audioindex]->codec->channels),
		ifmt_ctx_a->streams[audioindex]->codec->sample_fmt,
		ifmt_ctx_a->streams[audioindex]->codec->sample_rate,
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

	int64_t start_time = av_gettime();
	
	while (encode_video || encode_audio)
	{
		if (thread_exit)
			break;
		SDL_WaitEvent(&event);
		if (encode_video &&
			(!encode_audio || av_compare_ts(vid_next_pts, time_base_q,
			aud_next_pts, time_base_q) <= 0))
		{
			if ((ret = av_read_frame(ifmt_ctx, dec_pkt)) >= 0){

				if (exit_thread)
					break;

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

					//if (filter_change)
						apply_filters();
				//	filter_change = 0;
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
							//if (event1.type == SFM_REFRESH_EVENT
								img_convert_ctx = sws_getContext(picref->width, picref->height, (AVPixelFormat)picref->format, pCodecCtx->width, pCodecCtx->height, AV_PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);
								sws_scale(img_convert_ctx, (const uint8_t* const*)picref->data, picref->linesize, 0, pCodecCtx->height, pFrameYUV->data, pFrameYUV->linesize);
								sws_freeContext(img_convert_ctx);
								pFrameYUV->width = picref->width;
								pFrameYUV->height = picref->height;
								pFrameYUV->format = PIX_FMT_YUV420P;
								SDL_UpdateTexture(ptexture, NULL, pFrameYUV->data[0], pFrameYUV->linesize[0]);
								SDL_RenderClear(prenderer);
								//SDL_RenderCopy( sdlRenderer, sdlTexture, &sdlRect, &sdlRect );  
								SDL_RenderCopy(prenderer, ptexture, NULL, NULL);
								SDL_RenderPresent(prenderer);
							//}
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
						if ((pts_time > now_time) && ((vid_next_pts + pts_time - now_time)<aud_next_pts))
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
	else
	if (ret == AVERROR_EOF)
		encode_video = 0;
	else
	{
		printf("Could not read video frame\n");
		return ret;
	}
}
	else
	{
		//audio trancoding here
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

			/** Decode one frame worth of audio samples. */
			/** Packet used for temporary storage. */
			AVPacket input_packet;
			av_init_packet(&input_packet);
			input_packet.data = NULL;
			input_packet.size = 0;

			/** Read one audio frame from the input file into a temporary packet. */
			if ((ret = av_read_frame(ifmt_ctx_a, &input_packet)) < 0) {
				/** If we are at the end of the file, flush the decoder below. */
				if (ret == AVERROR_EOF)
				{
					encode_audio = 0;
				}
				else
				{
					printf("Could not read audio frame\n");
					return ret;
				}
			}

			/**
			* Decode the audio frame stored in the temporary packet.
			* The input audio stream decoder is used to do this.
			* If we are at the end of the file, pass an empty packet to the decoder
			* to flush it.
			*/
			if ((ret = avcodec_decode_audio4(ifmt_ctx_a->streams[audioindex]->codec, input_frame,
				&dec_got_frame_a, &input_packet)) < 0) {
				printf("Could not decode audio frame\n");
				return ret;
			}
			av_packet_unref(&input_packet);
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
				
				/***************************SDL_AUDIO***************************/
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
			/***************************SDL_AUDIO***************************/
			/*if ((ret = swr_convert(aud_convert_ctx,
				converted_input_samples, output_frame->nb_samples,
				(const uint8_t**)output_frame->extended_data, output_frame->nb_samples)) < 0) {
				printf("Could not convert input samples\n");
				return ret;
			}
			if (wanted_spec.samples != output_frame->nb_samples){
				SDL_CloseAudio();
				int out_nb_samples = output_frame->nb_samples;
				out_buffer_size = av_samples_get_buffer_size(NULL, out_channels, out_nb_samples, AV_SAMPLE_FMT_S16, 1);
				wanted_spec.samples = out_nb_samples;
				SDL_OpenAudio(&wanted_spec, NULL);
			}
			audio_chunk = (Uint8 *)converted_input_samples;
			//Audio buffer length
			audio_len = out_buffer_size;

			audio_pos = audio_chunk;
			//Play
			SDL_PauseAudio(0);
			while (audio_len>0)//Wait until finish
				SDL_Delay(1);*/
			/************************************************/
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
				AVRational r_framerate1 = { ifmt_ctx_a->streams[audioindex]->codec->sample_rate, 1 };// { 44100, 1};  
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
  }
  av_write_trailer(ofmt_ctx);
  
  thread_exit = 0;
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
  avformat_close_input(&ifmt_ctx);
  avformat_close_input(&ifmt_ctx_a);
  avformat_free_context(ofmt_ctx);
  //CloseHandle(hThread);
  return 0;
}

