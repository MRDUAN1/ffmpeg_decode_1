#include "cut_video__.h"
#include <qfileinfo.h>
extern QString outPutPath; //全局变量
cut_video__::cut_video__(QObject *parent)
: commom_signal(parent)
{
	
}
void cut_video__::deal_with(QString &str)
{
	int j = str.count('\\');
	int h = 0;
	while (j--)
	{
		h = str.indexOf('\\', h);
		str.replace(h, 1, '/');
	}

}

void cut_video__::set_file_name(QString str1, int from, int to)
{
	QFileInfo strr(str1);
	int i = strr.exists();
	QString st = strr.fileName();
	input_name__ = str1;
	deal_with(input_name__);
	from = splitTime;
	cut_video_1 = outPutPath + "/" + "_1" + st;
	cut_video_2 = outPutPath + "/" + "_2" + st;
}
void cut_video__::seek_stream(int64_t h)
{
	int p;
	h = h - 1;
	if ((p = av_seek_frame(ifmt_ctx, -1, h * AV_TIME_BASE, AVSEEK_FLAG_ANY)) < 0)
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
	emit length_all_merge_video_(duration_1);
	if ((p = av_seek_frame(ifmt_ctx, -1, 0 * AV_TIME_BASE, AVSEEK_FLAG_ANY)) < 0)
	{
		fprintf(stderr, "%s: error while seeking/n", "wrong");
	}
}
int cut_video__::start()
{
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
	seek_stream(ifmt_ctx->duration / AV_TIME_BASE);
	avformat_alloc_output_context2(&ofmt1_ctx, NULL, NULL, cut_video_1.toLocal8Bit().data());
	if (!ofmt1_ctx)
	{
		printf("Could not create output1 context\n");
		ret = AVERROR_UNKNOWN;
		goto end;
	}

	avformat_alloc_output_context2(&ofmt2_ctx, NULL, NULL, cut_video_2.toLocal8Bit().data());
	if (!ofmt2_ctx)
	{
		printf("Could not create output2 context\n");
		ret = AVERROR_UNKNOWN;
		goto end;
	}

	for (int i = 0; i < ifmt_ctx->nb_streams; i++)
	{
		if (ifmt_ctx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			inVideo_StreamIndex = i;
			out1_vstream = avformat_new_stream(ofmt1_ctx, NULL);
			out2_vstream = avformat_new_stream(ofmt2_ctx, NULL);

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

			if (!out2_vstream)
			{
				printf("Failed allocating output1 video stream\n");
				ret = AVERROR_UNKNOWN;
				goto end;
			}
			else
			{
				//copy the settings of AVCodecContext;
				if (avcodec_copy_context(out2_vstream->codec, ifmt_ctx->streams[i]->codec) < 0)
				{
					printf("Failed to copy context from input to output stream codec context\n");
					goto end;
				}
				out2_vstream->codec->codec_tag = 0;
				if (ofmt2_ctx->oformat->flags & AVFMT_GLOBALHEADER)
				{
					out2_vstream->codec->flags |= CODEC_FLAG_GLOBAL_HEADER;
				}
			}
		}
		else if (ifmt_ctx->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO)
		{
			inAudio_StreamIndex = i;
			out1_astream = avformat_new_stream(ofmt1_ctx, NULL);
			out2_astream = avformat_new_stream(ofmt2_ctx, NULL);

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


			if (!out2_astream)
			{
				printf("Failed allocating output1 video stream\n");
				ret = AVERROR_UNKNOWN;
				goto end;
			}
			else
			{
				//copy the settings of AVCodecContext;
				if (avcodec_copy_context(out2_astream->codec, ifmt_ctx->streams[i]->codec) < 0)
				{
					printf("Failed to copy context from input to output stream codec context\n");
					goto end;
				}
				out2_astream->codec->codec_tag = 0;
				if (ofmt2_ctx->oformat->flags & AVFMT_GLOBALHEADER)
				{
					out2_astream->codec->flags |= CODEC_FLAG_GLOBAL_HEADER;
				}
			}
		}
	}
	//open output1 file
	if (!(ofmt1_ctx->oformat->flags & AVFMT_NOFILE))
	{
		if (avio_open(&ofmt1_ctx->pb, cut_video_1.toLocal8Bit().data(), AVIO_FLAG_WRITE) < 0)
		{
			goto end;
		}
	}

	//open output2 file
	if (!(ofmt2_ctx->oformat->flags & AVFMT_NOFILE))
	{
		if (avio_open(&ofmt2_ctx->pb, cut_video_2.toLocal8Bit().data(), AVIO_FLAG_WRITE) < 0)
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

	//write out 2 file header
	if (avformat_write_header(ofmt2_ctx, NULL) < 0)
	{
		printf("Error occurred when opening video output file\n");
		goto end;
	}
	while (1)
	{
		AVFormatContext *ofmt_ctx;
		AVStream *in_stream, *out_stream;
		if (av_read_frame(ifmt_ctx, &pkt) < 0)
		{
			break;
		}
		if (pkt.stream_index == 0)
		{
			//emit length_onect_merge_video_(pkt.pts);
		}
		in_stream = ifmt_ctx->streams[pkt.stream_index];

		if (pkt.stream_index == inVideo_StreamIndex)
		{
			videoIndex++;
			int time;
			emit length_onect_merge_video_(pkt.pts);
			if (pkt.pts == AV_NOPTS_VALUE)
			{
			
				time = pkt.dts * (((float)in_stream->time_base.num) / ((float)in_stream->time_base.den));
				pkt.pts = pkt.dts;
			}
			else
				time = pkt.pts * (((float)in_stream->time_base.num) / ((float)in_stream->time_base.den));
			if (time < splitTime)
			{
				if (is_second)
					continue;
				splitPtsV = pkt.pts;
				splitDtsV = pkt.dts;
				out_stream = ofmt2_ctx->streams[pkt.stream_index];
				ofmt_ctx = ofmt2_ctx;
			}
			else
			{
				if (is_first_video)
				{
					last_dts_pre_v = 0;
					is_first_video = false;
				}
				is_second = true;
				if (pkt.dts == pkt.pts)
				{
					pkt.pts = pkt.pts - splitPtsV;
					pkt.dts = pkt.dts - splitPtsV;
					if (pkt.pts < pkt.dts)
						continue;
				}
				else
				{
					pkt.pts = pkt.pts - splitPtsV;
					pkt.dts = pkt.dts - splitDtsV;
				}

				out_stream = ofmt1_ctx->streams[pkt.stream_index];
				ofmt_ctx = ofmt1_ctx;
			}
		}
		else if (pkt.stream_index == inAudio_StreamIndex)
		{

			int time = pkt.pts * (((float)in_stream->time_base.num) / ((float)in_stream->time_base.den));
			if (time < splitTime)
			{
				if (is_second)
					continue;
				splitPtsA = pkt.pts;
				splitDtsA = pkt.dts;

				out_stream = ofmt2_ctx->streams[pkt.stream_index];
				ofmt_ctx = ofmt2_ctx;
			}
			else
			{
				if (is_first_audio)
				{
					last_dts_pre_a = 0;
					is_first_audio = false;
				}
				pkt.pts = pkt.pts - splitPtsA;
				pkt.dts = pkt.dts - splitDtsA;

				out_stream = ofmt1_ctx->streams[pkt.stream_index];
				ofmt_ctx = ofmt1_ctx;
			}
		}

		pkt.pts = av_rescale_q_rnd(pkt.pts, in_stream->time_base, out_stream->time_base, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
		if (pkt.stream_index == 0)
			last_dts_v = pkt.dts = av_rescale_q_rnd(pkt.dts, in_stream->time_base, out_stream->time_base, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
		else last_dts_a = pkt.dts = av_rescale_q_rnd(pkt.dts, in_stream->time_base, out_stream->time_base, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
		pkt.duration = av_rescale_q(pkt.duration, in_stream->time_base, out_stream->time_base);
		pkt.pos = -1;
		int hh = 0;
		if (pkt.stream_index == 0)
		{

			if (last_dts_v <= last_dts_pre_v)
				continue;
			else
				last_dts_pre_v = last_dts_v;
		}
		else
		{
			if (last_dts_a <= last_dts_pre_a)
				continue;
			else
				last_dts_pre_a = last_dts_a;
		}
		if (pkt.dts > pkt.pts)
			continue;

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
	av_write_trailer(ofmt2_ctx);
	int ttt = ofmt2_ctx->duration / AV_TIME_BASE;

end:
	avformat_close_input(&ifmt_ctx);

	/* close output */
	if (ofmt1_ctx && !(ofmt1_ctx->oformat->flags & AVFMT_NOFILE))
		avio_close(ofmt1_ctx->pb);

	avformat_free_context(ofmt1_ctx);

	/* close output */
	if (ofmt2_ctx && !(ofmt2_ctx->oformat->flags & AVFMT_NOFILE))
		avio_close(ofmt2_ctx->pb);

	avformat_free_context(ofmt2_ctx);

	return 0;
}
cut_video__::~cut_video__()
{

}
