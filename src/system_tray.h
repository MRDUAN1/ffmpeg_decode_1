#ifndef SYSTEM_TRAY_H
#define SYSTEM_TRAY_H

#include <QWidget>
#include <qaction.h>
#include <qsystemtrayicon.h>
#include <qmenu.h>
# pragma execution_character_set("utf-8")
class system_tray : public QWidget
{
	Q_OBJECT



public:
	system_tray(QWidget *parent = 0);
	void login_success();
	void exit_success();
	~system_tray();
protected:
	void trayiconActivated(QSystemTrayIcon::ActivationReason reason);

private:
	QSystemTrayIcon *trayIcon;
	QAction *minimizeAction;
	QAction *restoreAction;
	QAction *open_;
	QAction *quitAction;
	QAction *help;
	QMenu   *trayIconMenu;
	bool is_login;
	public slots:
	void show_normal();
	void quit_();
	void help_slot();
	void hide_();
};

#endif // SYSTEM_TRAY_H
