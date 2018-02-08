/*=========================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : video.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2016/10/07
* Description  :
* Function list: 1.
*                2.
*                3.
* History      :
\*=========================================================================*/
#include "stdafx.h"
/*-----------------------------------------------------------*
 * 头文件                                                    *
 *-----------------------------------------------------------*/
#include "video.h"
#include "global.h"
#include <string>
AVFormatContext* pFormatCtx_jpg;
AVOutputFormat* fmt_jpg;
AVStream* video_st_jpg;
AVCodecContext* pCodecCtx_jpg;
AVCodec* pCodec_jpg;
AVFrame save_pictures;
uint8_t* picture_buf;
PlayerState *psa;
/*======================================================================\
* Author     (作者): i.sshe
* Date       (日期): 2016/10/07
* Others     (其他): 一些准备工作
\*=======================================================================*/
int prepare_video(PlayerState *ps)
{
	
	psa = ps;
     ps->pvideo_stream = ps->pformat_ctx->streams[ps->video_stream_index];
     ps->pvideo_codec_ctx = ps->pvideo_stream->codec;
     ps->pvideo_codec = avcodec_find_decoder(ps->pvideo_codec_ctx->codec_id);
    if (ps->pvideo_codec == NULL)
    {
        fprintf(ERR_STREAM, "Couldn't find video decoder\n");
        return (-1);
    }

    //打开解码器
    if (avcodec_open2(ps->pvideo_codec_ctx, ps->pvideo_codec, NULL) < 0)
    {
         fprintf(ERR_STREAM, "Couldn't open video decoder\n");
         return -1;
    }

    return 0;
}

/*======================================================================\
* Author     (作者): i.sshe
* Date       (日期): 2016/10/07
* Others     (其他): 其实这里还算准备工作，开窗口什么的
\*=======================================================================*/
int play_video(PlayerState *ps)
{
     ps->pixel_w    = ps->pvideo_codec_ctx->width;
     ps->pixel_h    = ps->pvideo_codec_ctx->height;
     ps->window_w   = ps->pixel_w;
     ps->window_h   = ps->pixel_h;

     ps->pixfmt  = AV_PIX_FMT_YUV420P;
     ps->out_frame.format  = AV_PIX_FMT_YUV420P;
     ps->out_frame.width   = ps->pixel_w;
     ps->out_frame.height  = ps->pixel_h;

     //
     ps->video_buf = (uint8_t *)av_malloc(
              avpicture_get_size(ps->pixfmt,
                  ps->out_frame.width, ps->out_frame.height)
             );

     //用av_image_fill_arrays代替。
     //根据所给参数和提供的数据设置data指针和linesizes。
     avpicture_fill((AVPicture *)&ps->out_frame, ps->video_buf,
             ps->pixfmt,
             ps->out_frame.width, ps->out_frame.height);

     //使用sws_scale之前要用这个函数进行相关转换操作。
     //分配和返回一个 SwsContext.
     //sws_freeContext(ps->psws_ctx); 需要用这个函数free内存。
     //现在因为只用了一次sws_getContext()所以，这个内存在main释放。
     //因为一直输出格式什么都一样，所以没有放在靠近sws_scale的地方。
     ps->psws_ctx = sws_getContext(ps->pixel_w,
             ps->pixel_h, ps->pvideo_codec_ctx->pix_fmt,
             ps->out_frame.width, ps->out_frame.height,
             ps->pixfmt,
             SWS_BILINEAR, NULL, NULL, NULL);

     ps->sdl_rect.x = 0;
     ps->sdl_rect.y = 0;

    //创建窗口
    //SDL_WINDOW_RESIZABLE: 使窗口可以拉伸
   /* ps->pwindow = SDL_CreateWindow("Isshe Video Player!",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            ps->window_w, ps->window_h,
            SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);*/
    if (ps->pwindow == NULL)
    {
         fprintf(ERR_STREAM, "Couldn't Create Window\n");
         exit(-1);        //
    }

    //新建一个渲染器
    ps->prenderer = SDL_CreateRenderer(ps->pwindow, -1, 0);
    ps->ptexture  = SDL_CreateTexture(ps->prenderer,
            SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STREAMING,
            ps->pixel_w, ps->pixel_h);
	//新建线程运行刷新函数
	SDL_CreateThread(refresh_fun, "refresh func", ps);
	return 0;
}



/*======================================================================\
* Author     (作者): i.sshe
* Date       (日期): 2016/10/08
* Others     (其他): 刷新函数
\*=======================================================================*/
int refresh_fun(void *arg)
{
	SDL_Event event;
	PlayerState *ps = (PlayerState*) arg;

	while(ps->quit == 0)
	{
		event.type = ISSHE_REFRESH_EVENT;
		SDL_PushEvent(&event);

		SDL_Delay(ps->delay);
	}
	return 0;
}

void save_jpeg()
{
	bool temp = false;
	global::set_camera_status(temp);
	av_register_all();
	int in_w = 640, in_h = 480;                                  //宽高
	char buf[100] = { '\0' };                  //输出文件路径
	int hp = 0;
	sprintf(buf, "cuc_view_encode.jpg", hp);
	//方法1.组合使用几个函数
	pFormatCtx_jpg = avformat_alloc_context();
	//猜格式。用MJPEG编码
	fmt_jpg = av_guess_format("mjpeg", NULL, NULL);
	pFormatCtx_jpg->oformat = fmt_jpg;
	//注意：输出路径
	if (avio_open(&pFormatCtx_jpg->pb, buf, AVIO_FLAG_READ_WRITE) < 0)
	{
		printf("输出文件打开失败");
		return;
	}
	video_st_jpg = avformat_new_stream(pFormatCtx_jpg, 0);
	//video_st_jpg = av_new_stream(pFormatCtx_jpg, 0);
	if (video_st_jpg == NULL)
	{
		return;
	}
	pCodecCtx_jpg = video_st_jpg->codec;
	pCodecCtx_jpg->codec_id = fmt_jpg->video_codec;
	pCodecCtx_jpg->codec_type = AVMEDIA_TYPE_VIDEO;
	pCodecCtx_jpg->pix_fmt = PIX_FMT_YUVJ420P;
	pCodecCtx_jpg->width = psa->window_w;
	pCodecCtx_jpg->height = psa->window_h;
	pCodecCtx_jpg->time_base.num = 1;
	pCodecCtx_jpg->time_base.den = 25;
	//输出格式信息
	av_dump_format(pFormatCtx_jpg, 0, buf, 1);
	pCodec_jpg = avcodec_find_encoder(pCodecCtx_jpg->codec_id);
	if (!pCodec_jpg)
	{
		printf("没有找到合适的编码器！");
		return;
	}
	if (avcodec_open2(pCodecCtx_jpg, pCodec_jpg, NULL) < 0)
	{
		//printf("编码器打开失败！");
		return ;
	}
	AVPacket pkt;
	int picture_size = avpicture_get_size(pCodecCtx_jpg->pix_fmt, pCodecCtx_jpg->width, pCodecCtx_jpg->height);
	av_new_packet(&pkt, picture_size);
	int got_picture;
	avformat_write_header(pFormatCtx_jpg, NULL);
	int ret = avcodec_encode_video2(pCodecCtx_jpg, &pkt, &save_pictures, &got_picture);
	if (got_picture == 1)
	{
		pkt.stream_index = video_st_jpg->index;
		ret = av_write_frame(pFormatCtx_jpg, &pkt);
	}
	av_free_packet(&pkt);
	//写文件尾
	av_write_trailer(pFormatCtx_jpg);
	if (video_st_jpg)
	{
		avcodec_close(video_st_jpg->codec);
		//	av_free();
		av_free(picture_buf);
	}
	avio_close(pFormatCtx_jpg->pb);
	avformat_free_context(pFormatCtx_jpg);
	/*string file_image;
	FILE *file;
	char buff[1025 * 30] = { '\0' };
	static int io = 0;
	++io;
	if (io % 3 == 0)
		return;
	if ((file = fopen(buf, "rb+")) == NULL)
	{
		perror("file open");
		return;
	}
	int len_ = fread(buff, 1, 1024 * 30, file);
	fclose(file);*/

}
/*======================================================================\
* Author     (作者): i.sshe
* Date       (日期): 2016/10/07
* Others     (其他):
\*=======================================================================*/
int decode_and_show(void *arg)
{
     PlayerState *ps = (PlayerState *)arg;
     AVPacket packet ;
     AVFrame *pframe = av_frame_alloc();
     AVFrame *tempframe = av_frame_alloc();
     double pts = 0.0;
     int ret = 0;
     // ...
      if (ps->quit == 1)
          return 0;

      if (ps->video_packet_queue.nb_packets == 0)
      {
          return 0;
      }

      //从packet队列取一个packet出来解码
     ret = packet_queue_get(&ps->video_packet_queue, &packet, 1);
      if (ret < 0)
      {
          fprintf(ERR_STREAM, "Get video packet error\n");
          return -1;     //
      }

	  int got_picture = 0;
	  ret = avcodec_decode_video2(ps->pvideo_codec_ctx, pframe, &got_picture, &packet);
	  if(ret < 0){
				printf("Decode Error.\n");
				return -1;
		}
     //下面三句实现音视频同步，还有一句在audio部分。
     //获取pts
     pts = get_frame_pts(ps, pframe);
     //ps中用cur_frame_pts是为了减少get_delay()的参数
     ps->cur_frame_pts = pts; //*(double *)pframe.opaque;
     ps->delay = get_delay(ps) * 1000 + 0.5 - 5;
     //这个函数看了手册也不大理解
     sws_scale(ps->psws_ctx, (uint8_t const *const *)pframe->data,
            pframe->linesize, 0, ps->pixel_h,
            ps->out_frame.data, ps->out_frame.linesize);
	 if (global::return_bool())
	 {
		 save_pictures = *pframe;
		 save_jpeg();
	 }
	 
     ps->sdl_rect.w = ps->window_w;
     ps->sdl_rect.h = ps->window_h;

     SDL_UpdateTexture(ps->ptexture, NULL,
             ps->out_frame.data[0], ps->out_frame.linesize[0]);
     SDL_RenderClear(ps->prenderer);
     SDL_RenderCopy(ps->prenderer, ps->ptexture, NULL, &ps->sdl_rect);
     SDL_RenderPresent(ps->prenderer);


     av_frame_free(&pframe);
	 av_free_packet(&packet);
     return 0;
}


/*======================================================================\
* Author     (作者): i.sshe
* Date       (日期): 2016/10/08
* Others     (其他): 获取延迟时间
\*=======================================================================*/
double get_delay(PlayerState *ps)
{
	double 		ret_delay = 0.0;
	double 		frame_delay = 0.0;
	double 		cur_audio_clock = 0.0;
	double 		compare = 0.0;
	double  	threshold = 0.0;

	//这里的delay是秒为单位， 化为毫秒：*1000
	frame_delay = ps->cur_frame_pts - ps->pre_frame_pts;
	if (frame_delay <= 0 || frame_delay >= 1.0)
	{
		frame_delay = ps->pre_cur_frame_delay;
	}
	//两帧之间的延时
	ps->pre_cur_frame_delay = frame_delay;
	ps->pre_frame_pts = ps->cur_frame_pts;

	cur_audio_clock = get_audio_clock(ps);

	//compare < 0 说明慢了， > 0说明快了
	compare = ps->cur_frame_pts - cur_audio_clock;

	//设置一个阀值, 是一个正数
	//这里设阀值为两帧之间的延迟，
	threshold = frame_delay;
	//SYNC_THRESHOLD ? frame_delay : SYNC_THRESHOLD;


	if (compare <= -threshold) 		//慢， 加快速度
	{
		ret_delay = frame_delay / 2;
	}
	else if (compare >= threshold) 	//快了，就在上一帧延时的基础上加长延时
	{
		ret_delay = frame_delay * 2;
	}
	else
	{
		//
		ret_delay = frame_delay;//frame_delay;
	}
/*
	printf("获取delay里：cur_frame_pts = %lf, cur_audio_clock = %lf\n"
			"ret_delay = %lf, frame_delay = %lf\n",
			ps->cur_frame_pts, cur_audio_clock, ret_delay, frame_delay);
	printf("获取delay里：frame_delay = %lf, ps->pre_frame_pts = %lf"
			"compare = %lf, threshold = %lf\n",
			frame_delay,ps->pre_frame_pts, compare, threshold);
*/

/*	//这部分可能用了更准确之类的，但是这次没用，也没测试过
	ps->frame_timer += ret_delay/1000; 	//考虑要不要,注意这里是秒单位
	int64_t cur_time = av_gettime()/1000000; 	//av_gettime()返回微秒
	double real_delay = ps->frame_timer - cur_time;
	 if (real_delay <= 0.010)
	 {
	 	  read_delay = 0.010;
	 }
	 ret_delay = actual_delay * 1000 + 0.5;
*/
	return ret_delay;
}
/*======================================================================\
* Author     (作者): i.sshe
* Date       (日期): 2016/10/08
* Others     (其他): 获取音频的当前时间
\*=======================================================================*/
double get_audio_clock(PlayerState *ps)
{
	long long bytes_per_sec = 0;
	double cur_audio_clock = 0.0;
	double cur_buf_pos = ps->audio_buf_index;

	//每个样本占2bytes。16bit
	bytes_per_sec = ps->paudio_stream->codec->sample_rate
	 			* ps->paudio_codec_ctx->channels * 2;

	cur_audio_clock = ps->audio_clock +
	 				cur_buf_pos / (double)bytes_per_sec;
/*
	printf("cur_buf_pos = %lf, bytes_per_sec = %lld, "
	 		"cur_audio_clock = %lf, audio_clock = %lf\n",
	 		cur_buf_pos, bytes_per_sec, cur_audio_clock, ps->audio_clock);
*/
	return cur_audio_clock;
}


/*======================================================================\
* Author     (作者): i.sshe
* Date       (日期): 2016/10/08
* Others     (其他): 获取一个帧的pts
\*=======================================================================*/
double get_frame_pts(PlayerState *ps, AVFrame *pframe)
{
	double pts = 0.0;
	double frame_delay = 0.0;

	pts = av_frame_get_best_effort_timestamp(pframe);
	if (pts == AV_NOPTS_VALUE) 		//???
	{
		pts = 0;
	}

	pts *= av_q2d(ps->pvideo_stream->time_base);

	if (pts != 0)
	{
		ps->video_clock = pts; 		//video_clock貌似没有什么实际用处
	}
	else
	{
		pts = ps->video_clock;
	}

	//更新video_clock, 这里不理解
	//这里用的是AVCodecContext的time_base
	//extra_delay = repeat_pict / (2*fps), 这个公式是在ffmpeg官网手册看的
	frame_delay = av_q2d(ps->pvideo_stream->codec->time_base);
	frame_delay += pframe->repeat_pict / (frame_delay * 2);
	ps->video_clock += frame_delay;

	return pts;
}

