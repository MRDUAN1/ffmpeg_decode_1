//摄像头播放的类
#ifndef CAMERA_SPECIFICS_H
#define CAMERA_SPECIFICS_H

#include <QObject>
#define USEFILTER 1
//#include <WinSock2.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <string>
#define snprintf _snprintf
extern "C"
{
#include "SDL2/SDL.h"
#include "libavutil/opt.h"
#include "libavutil/time.h"
#include "libavutil/mathematics.h"
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavdevice/avdevice.h"
#include "libswscale/swscale.h"
#include "libswresample/swresample.h"
#include "libavutil/audio_fifo.h"

//#include "sdl1/sdl/SDL.h"
#if USEFILTER
#include "libavfilter/avfiltergraph.h"
#include "libavfilter/buffersink.h"
#include "libavfilter/buffersrc.h"
#endif
};
#pragma comment(lib, "avutil.lib")
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avformat.lib")
#pragma comment(lib, "avdevice.lib")
#pragma comment(lib, "swresample.lib")
#pragma comment(lib, "avfilter.lib")
#pragma comment(lib, "SDL2main.lib")
//#pragma comment(lib, "SDL.lib")
#pragma comment(lib, "swscale.lib")
using std::string;
class camera_specifics : public QObject
{
	Q_OBJECT

public:
	camera_specifics(QObject *parent = 0);
	~camera_specifics();
	int start();
	//设置视频退出
	void set_exit();
	int apply_filters();
	void set_filter_change(string change, HWND wind);
	void set_hwnd(HWND widd);
	void copy_out_path(QString str);
private:
	HWND wid;
	/*********滤镜*************/
	const char *filter_mirror1 = "scale=320:240";
	const char *filter_mirror3 = "transpose=2";
	const char *filter_descr3 = "drawtext=fontfile=FreeSans.ttf:fontcolor=green:fontsize=30:text='Hello'";
	const char *filter_descr2 = "scale=iw/2:ih/2";
	const char *filter_descr = "null";
	const char *filter_mirror = "crop=iw/2:ih:0:0,split[left][tmp];[tmp]hflip[right]; \																										                                                                                                                                                                                                                                												[left]pad=iw*2[a];[a][right]overlay=w";
	const char *filter_watermark = "movie=test.jpg[wm];[in][wm]overlay=5:5[out]";
	const char *filter_negate = "negate[out]";
	const char *filter_edge = "edgedetect[out]";
	const char *filter_split4 = "scale=iw/2:ih/2[in_tmp];[in_tmp]split=4[in_1][in_2][in_3][in_4];[in_1]pad=iw*2:ih*2[a];[a][in_2]overlay=w[b];[b][in_3]overlay=0:h[d];[d][in_4]overlay=w:h[out]";
	const char *filter_vintage = "curves=vintage";
	/*********滤镜*************/
	static void  fill_audio(void *udata, Uint8 *stream, int len);
	int init_audio();
	unsigned char samples[192000 * 3 / 2];
	unsigned char *buf;
	static int camera_specifics::sfp_refresh_thread(void *opaque);
#define SFM_REFRESH_EVENT  (SDL_USEREVENT + 1)
#define SFM_BREAK_EVENT  (SDL_USEREVENT + 2)
	int sdl_init();
	string filter_change_str;
	AVFormatContext *ifmt_ctx_video;
	AVFormatContext *ifmt_ctx_a;
	int pixel_w;
	int pixel_h;
	int window_w;
	int window_h;
	uint8_t *video_buf;
	string out_path;
	//static void MyThreadFunction(void *);
	int flush_encoder(AVFormatContext *ifmt_ctx, AVFormatContext *ofmt_ctx, unsigned int stream_index, int framecnt);
	int flush_encoder_a(AVFormatContext *ifmt_ctx_a, AVFormatContext *ofmt_ctx, unsigned int stream_index, int nb_samples);
	typedef enum{
		FILTER_NULL = 48,
		FILTER_MIRROR,
		FILTER_WATERMATK,
		FILTER_NEGATE,
		FILTER_EDGE,
		FILTER_SPLIT4,
		FILTER_VINTAGE
	}FILTERS;
	AVFilterContext *buffersink_ctx;
	AVFilterContext *buffersrc_ctx;
	AVFilterGraph *filter_graph;
	AVFilter *buffersrc;
	AVFilter *buffersink;
	AVFrame* picref;
	SDL_Window         *pwindow;
	SDL_Renderer       *prenderer;
	SDL_Texture        *ptexture;
	SDL_Rect           sdl_rect;
};
#endif // CAMERA_SPECIFICS_H
