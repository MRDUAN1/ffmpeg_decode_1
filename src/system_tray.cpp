#include "system_tray.h"
#include "ffmpeg_interface.h"
extern ffmpeg_interface *interface_;
system_tray::system_tray(QWidget *parent)
: QWidget(parent)
{
	qApp->setWindowIcon(QIcon("./imag/grape_icon.ico"));
	
	is_login = false;
	QIcon icon = QIcon("./imag/grape.png");
	trayIcon = new QSystemTrayIcon(this);
	QObject::connect(trayIcon, SIGNAL(triggered()), this, SLOT(showNormal()));
	trayIcon->setIcon(icon);
	trayIcon->setToolTip(tr("仿格式工厂_1.0"));
	trayIcon->show();
	connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
		this, SLOT(trayiconActivated(QSystemTrayIcon::ActivationReason)));
	minimizeAction = new QAction(tr("最小化 (&I)"), this);
	minimizeAction->setIcon(QIcon("./imag/mini1.png"));
	connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide_()));
	restoreAction = new QAction(tr("还原 (&R)"), this);
	restoreAction->setIcon(QIcon("./imag/reeee.png"));
	connect(restoreAction, SIGNAL(triggered()), this, SLOT(show_normal()));
	quitAction = new QAction(tr("退出 (&Q)"), this);
	quitAction->setIcon(QIcon("./imag/extt.png"));
	open_ = new QAction(tr("打开主面板 (&C)"), this);
	open_->setIcon(QIcon("./imag/exit31"));
	connect(open_, SIGNAL(triggered()), this, SLOT(show_normal()));
	connect(quitAction, SIGNAL(triggered()), this, SLOT(quit_()));
	help = new QAction(tr("帮助(&H)"), this);
	help->setIcon(QIcon("./imag/hp.png"));
	connect(help, SIGNAL(triggered()), this, SLOT(help_slot()));
	trayIconMenu = new QMenu(this);
	trayIconMenu->addAction(minimizeAction);
	trayIconMenu->addAction(restoreAction);
	trayIconMenu->addAction(open_);

	trayIconMenu->addSeparator();
	trayIconMenu->addAction(help);
	trayIconMenu->addAction(quitAction);
	trayIcon->setContextMenu(trayIconMenu);
}
void system_tray::help_slot()
{
	
}
system_tray::~system_tray()
{

}
void system_tray::login_success()
{
	is_login = true;
	QIcon icon("./friend_head/qq.png");
	trayIcon->setIcon(icon);
}
void system_tray::exit_success()
{
	is_login = false;
	QIcon icon("./friend_head/gray_qq.png");
	trayIcon->setIcon(icon);
}
void system_tray::trayiconActivated(QSystemTrayIcon::ActivationReason reason)
{
	switch (reason)
	{
	case QSystemTrayIcon::Trigger:

	case QSystemTrayIcon::DoubleClick:
		//双击托盘图标
		this->showNormal();
		this->raise();
		break;
	default:
		break;
	}
}
void system_tray::show_normal()
{

	interface_->showNormal();
}
void system_tray::quit_()
{
	exit(0);
}
void system_tray::hide_()
{
	interface_->showMinimized();
}