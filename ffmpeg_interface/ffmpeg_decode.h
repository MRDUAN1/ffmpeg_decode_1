#pragma once
#include <string>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswresample/swresample.h>
#include <libswscale/swscale.h>
#include <libavutil/time.h>
#include <SDL2/SDL.h>
using namespace std;
class ffmpeg_decode
{
public:
	ffmpeg_decode();
	int start();
	void set_input_output_name(string input_name, string out_name);
	char *in_filename, *out_filename;
	char in_filename[100], out_filename[100];
	~ffmpeg_decode();
};

