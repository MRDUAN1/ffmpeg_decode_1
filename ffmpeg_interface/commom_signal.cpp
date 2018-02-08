#include "commom_signal.h"
#include "ffmpeg_interface.h"
extern ffmpeg_interface *interface_;
commom_signal::commom_signal(QObject *parent)
	: QObject(parent)
{
	connect(this, SIGNAL(length_all_merge_video_(int64_t)), interface_, SLOT(length_all(int64_t)), Qt::QueuedConnection);
	connect(this, SIGNAL(length_onect_merge_video_(int64_t)), interface_, SLOT(change_once_(int64_t)), Qt::QueuedConnection);
}
void commom_signal::get_file_name(QString &_input)
{
	_input = input_name__;
}
commom_signal::~commom_signal()
{

}
