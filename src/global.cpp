#include "global.h"
#include "format_progam_3.h"
#include <map>
#include <string>
#include <vector>
using std::string;
static format_progam_3 *format;
string string_filter;
static bool is_save_picture;
static std::map<string, tree_file*>decode_detail; //插不插入滤镜，第一个参数为文件名，第二个参数为滤镜
static std::vector<panel_list_data*>list_data;
global::global()
{
}
std::vector<panel_list_data*>& global::return_panel_list_data()
{
	return list_data;
}
std::map<string, tree_file*>& global::return_decode_detail()
{
	return decode_detail;
}
format_progam_3*& global::return_format()
{
	return format;
}
void global::set_format(format_progam_3*&forma)
{
	format = forma;
}
bool& global::return_bool()
{
	return is_save_picture;
}
void global::set_camera_status(bool &bol)
{
	is_save_picture = bol;
}
global::~global()
{
}
