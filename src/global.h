#pragma once
#include <qstring.h>
#include <vector>
#include <map>
#include <string>
using std::string;
using std::vector;
struct tree_file;
class format_progam_3;
struct panel_list_data{
	QString file_name;
	QString full_name;
	QString file_dir;
	QString size;
	QString last_time;
	QString resolution_rate;
	QString format;
	bool is_picture;
	bool is_over;
	bool is_failure;
	bool is_separate;
	/*********merge_video_audio******************/
	bool is_merge_video;
	QString audio_url;
	QString video_url;
	/*********merge_music******************/
	bool is_merge_music;
	QString audio_path;
	int from;
	int to;
	/************************************/
	bool is_merge_audio;
	QString audio_path_1;
	QString audio_path_2;
	/***********cut视频**********************/
	bool is_cut_video;
	bool is_cut_video_2;
	QString cut_video;
	int from_video, to_video;
	/************合并视频*********************/
	bool merge_videos;
};
struct tree_file{
	int i; //i代表第几个滤镜功能
	string string_filter;
};
class global
{
public:
	global();
	static std::map<string, tree_file*>& return_decode_detail();
	static std::vector<panel_list_data*>& return_panel_list_data();
	static format_progam_3*& return_format();
	static void set_format(format_progam_3*&);
	static void set_camera_status(bool &);
	static bool& return_bool();
	~global();
};


