#include "cut_video_2.h"
//#include "commom_signal.h"

#include <qfileinfo.h>
extern QString outPutPath;
cut_video_2::cut_video_2(QObject *parent)
: commom_signal(parent)
{

}
void cut_video_2::deal_with(QString &str)
{
	int j = str.count('\\');
	int h = 0;
	while (j--)
	{
		h = str.indexOf('\\', h);
		str.replace(h, 1, '/');
	}

}
//Ωÿ»°ƒ≥“ª∂Œ ”∆µ
void cut_video_2::seek_stream()
{
	int p;
	int64_t dur_1, dur_2;
	AVPacket packet; //= { .data = NULL, .size = 0 };
	packet.data = NULL;
	packet.size = 0;

	if ((p = av_seek_frame(ifmt_ctx, -1, to * AV_TIME_BASE, AVSEEK_FLAG_ANY)) < 0)
	{
		fprintf(stderr, "%s: error while seeking/n", "wrong");
	}
	
	while (1)
	{
		av_read_frame(ifmt_ctx, &packet);
		if (packet.stream_index == 0)
		{
			dur_2 = packet.pts;
			break;
		}
	}
	if ((p = av_seek_frame(ifmt_ctx, -1, from * AV_TIME_BASE, AVSEEK_FLAG_ANY)) < 0)
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
			dur_1 = ps_v = packet.pts;
			ds_v = packet.dts;
		}
		else
		{
			ds_a = ps_a = packet.pts;
		}
	}
	emit length_all_merge_video_((dur_2 - dur_1));
}
void cut_video_2::set_filename(QString str1, int from_, int to_)
{
	input_name__ = str1;
	from = from_;
	to = to_;
	QFileInfo filo(input_name__);
	QString ss = filo.fileName();
	str_separate = outPutPath + "/" +  "_separate_" + ss;
}
void cut_video_2::get_filename(QString &str1)
{
	str1 = input_name__;
}
int cut_video_2::start()
{
	ifmt_ctx = NULL;
	av_register_all();
	if ((ret = avformat_open_input(&ifmt_ctx, input_name__.toLocal8Bit().data(), NULL, NULL)) < 0)
	{
		printf("can not open the in put file format context!\n");
		return -1;
	}
	if ((ret = avformat_find_stream_info(ifmt_ctx, NULL)) < 0)
	{
		printf("can not find the input stream info!\n");
		goto end;
	}

	avformat_alloc_output_context2(&ofmt1_ctx, NULL, NULL, str_separate.toLocal8Bit().data());
	if (!ofmt1_ctx)
	{
		printf("Could not create output1 context\n");
		ret = AVERROR_UNKNOWN;
		goto end;
	}
	for (int i = 0; i < ifmt_ctx->nb_streams; i++)
	{
		if (ifmt_ctx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			inVideo_StreamIndex = i;
			out1_vstream = avformat_new_stream(ofmt1_ctx, NULL);


			//open decoder
			if (0 > avcodec_open2(ifmt_ctx->streams[i]->codec, avcodec_find_decoder(ifmt_ctx->streams[i]->codec->codec_id), NULL))
			{
				printf("can not find or open video decoder!\n");
				goto end;
			}

			if (!out1_vstream)
			{
				printf("Failed allocating output1 video stream\n");
				ret = AVERROR_UNKNOWN;
				goto end;
			}
			else
			{
				//copy the settings of AVCodecContext;
				if (avcodec_copy_context(out1_vstream->codec, ifmt_ctx->streams[i]->codec) < 0)
				{
					printf("Failed to copy context from input to output stream codec context\n");
					goto end;
				}
				out1_vstream->codec->codec_tag = 0;
				if (ofmt1_ctx->oformat->flags & AVFMT_GLOBALHEADER)
				{
					out1_vstream->codec->flags |= CODEC_FLAG_GLOBAL_HEADER;
				}
			}
		}
		else if (ifmt_ctx->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO)
		{
			inAudio_StreamIndex = i;
			out1_astream = avformat_new_stream(ofmt1_ctx, NULL);
			if (!out1_astream)
			{
				printf("Failed allocating output1 video stream\n");
				ret = AVERROR_UNKNOWN;
				goto end;
			}
			else
			{
				//copy the settings of AVCodecContext;
				if (avcodec_copy_context(out1_astream->codec, ifmt_ctx->streams[i]->codec) < 0)
				{
					printf("Failed to copy context from input to output stream codec context\n");
					goto end;
				}
				out1_astream->codec->codec_tag = 0;
				if (ofmt1_ctx->oformat->flags & AVFMT_GLOBALHEADER)
				{
					out1_astream->codec->flags |= CODEC_FLAG_GLOBAL_HEADER;
				}
			}
		}
	}
	int p1;
	//open output1 file+		str_separate	E:\outPut/_separate_222.mp4	QString
	deal_with(str_separate);
	if (!(ofmt1_ctx->oformat->flags & AVFMT_NOFILE))
	{
		p1 = avio_open(&ofmt1_ctx->pb, str_separate.toLocal8Bit().data(), AVIO_FLAG_WRITE);
		if (p1 < 0 )
		{
			goto end;
		}
	}
	//write out 1 file header
	if (avformat_write_header(ofmt1_ctx, NULL) < 0)
	{
		printf("Error occurred when opening video output file\n");
		goto end;
	}
	int videoIndex = 0;//the real video index
	
	bool is_first_video = true, is_first_audio = true;
	seek_stream();
	AVPacket pkt;
	while (1)
	{
		AVFormatContext *ofmt_ctx;
		AVStream *in_stream, *out_stream;

		if (av_read_frame(ifmt_ctx, &pkt) < 0)
		{
			break;
		}
		in_stream = ifmt_ctx->streams[pkt.stream_index];

		if (pkt.stream_index == 0)
		{
			emit length_onect_merge_video_((pkt.pts - ps_v));
			videoIndex++;
			int time;
			if (pkt.pts == AV_NOPTS_VALUE)
			{

				time = pkt.dts * (((float)in_stream->time_base.num) / ((float)in_stream->time_base.den));
				pkt.pts = pkt.dts;
			}
			else
				time = pkt.pts * (((float)in_stream->time_base.num) / ((float)in_stream->time_base.den));
			if (time > to)
			{
				break;
			}
			else
			{
				if (pkt.dts == pkt.pts)
				{
					if (pkt.pts <= ps_v || pkt.dts <= ds_v)
						continue;
					pkt.pts = pkt.pts - ps_v;
					pkt.dts = pkt.dts - ds_v;
					if (pkt.pts < pkt.dts)
						continue;
				}
				else
				{
					if (pkt.pts <= ps_v || pkt.dts <= ds_v)
						continue;
					pkt.pts = pkt.pts - ps_v;
					pkt.dts = pkt.dts - ds_v;
				}
				
				out_stream = ofmt1_ctx->streams[pkt.stream_index];
				ofmt_ctx = ofmt1_ctx;
			}
		}
		else if (pkt.stream_index == 1)
		{

			int time = pkt.pts * (((float)in_stream->time_base.num) / ((float)in_stream->time_base.den));
			if (time > to)
			{
				break;
			}
			else
			{
				pkt.pts = pkt.pts - ps_a;
				pkt.dts = pkt.dts - ds_a;
				out_stream = ofmt1_ctx->streams[pkt.stream_index];
				ofmt_ctx = ofmt1_ctx;
			}
		}
		
		pkt.pts = av_rescale_q_rnd(pkt.pts, in_stream->time_base, out_stream->time_base, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
		if (pkt.stream_index == 0)
			pkt.dts = av_rescale_q_rnd(pkt.dts, in_stream->time_base, out_stream->time_base, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
		else pkt.dts = av_rescale_q_rnd(pkt.dts, in_stream->time_base, out_stream->time_base, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
		pkt.duration = av_rescale_q(pkt.duration, in_stream->time_base, out_stream->time_base);
		pkt.pos = -1;
		int hh = 0;
		int64_t u = pkt.pts;
		hh = av_interleaved_write_frame(ofmt_ctx, &pkt);
		if (hh < 0)
		{
			printf("Error muxing packet\n");
			break;
		}
		av_free_packet(&pkt);
	}

	av_write_trailer(ofmt1_ctx);
	int64_t ii = ofmt1_ctx->duration / AV_TIME_BASE;

end:
	avformat_close_input(&ifmt_ctx);

	/* close output */
	if (ofmt1_ctx && !(ofmt1_ctx->oformat->flags & AVFMT_NOFILE))
		avio_close(ofmt1_ctx->pb);

	avformat_free_context(ofmt1_ctx);

	return 0;
}
cut_video_2::~cut_video_2()
{

}
