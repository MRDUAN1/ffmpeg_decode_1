/********************************************************************************
** Form generated from reading UI file 'merge_gui.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MERGE_GUI_H
#define UI_MERGE_GUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_merge_gui
{
public:
    QPushButton *ok;
    QPushButton *cancel;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QPushButton *video_pushbutton;
    QPushButton *audio_pushbutton;

    void setupUi(QWidget *merge_gui)
    {
        if (merge_gui->objectName().isEmpty())
            merge_gui->setObjectName(QStringLiteral("merge_gui"));
        merge_gui->resize(329, 132);
        ok = new QPushButton(merge_gui);
        ok->setObjectName(QStringLiteral("ok"));
        ok->setGeometry(QRect(40, 100, 93, 28));
        ok->setStyleSheet(QLatin1String("QPushButton {\n"
"    border: 2px solid #8f8f91;\n"
"    border-radius: 6px;\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #f6f7fa, stop: 1 #dadbde);\n"
"    min-width: 80px;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #dadbde, stop: 1 #f6f7fa);\n"
"}\n"
"\n"
"QPushButton:flat {\n"
"    border: none; /* no border for a flat push button */\n"
"}\n"
"\n"
"QPushButton:default {\n"
"    border-color: rgb(255, 255, 255); /* make the default button prominent */\n"
"}"));
        cancel = new QPushButton(merge_gui);
        cancel->setObjectName(QStringLiteral("cancel"));
        cancel->setGeometry(QRect(190, 100, 93, 28));
        cancel->setStyleSheet(QLatin1String("QPushButton {\n"
"    border: 2px solid #8f8f91;\n"
"    border-radius: 6px;\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #f6f7fa, stop: 1 #dadbde);\n"
"    min-width: 80px;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #dadbde, stop: 1 #f6f7fa);\n"
"}\n"
"\n"
"QPushButton:flat {\n"
"    border: none; /* no border for a flat push button */\n"
"}\n"
"\n"
"QPushButton:default {\n"
"    border-color: rgb(255, 255, 255); /* make the default button prominent */\n"
"}"));
        lineEdit = new QLineEdit(merge_gui);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(120, 10, 200, 30));
        lineEdit->setStyleSheet(QLatin1String("QLineEdit {\n"
"    border: 2px solid gray;\n"
"    border-radius: 10px;\n"
"    padding: 0 8px;\n"
"    background: rgb(232,245,252);\n"
"    selection-background-color: darkgray;\n"
"}"));
        lineEdit_2 = new QLineEdit(merge_gui);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(120, 50, 200, 30));
        lineEdit_2->setStyleSheet(QLatin1String("QLineEdit {\n"
"    border: 2px solid gray;\n"
"    border-radius: 10px;\n"
"    padding: 0 8px;\n"
"    background: rgb(232,245,252);\n"
"    selection-background-color: darkgray;\n"
"}"));
        video_pushbutton = new QPushButton(merge_gui);
        video_pushbutton->setObjectName(QStringLiteral("video_pushbutton"));
        video_pushbutton->setGeometry(QRect(10, 10, 93, 28));
        video_pushbutton->setStyleSheet(QLatin1String("QPushButton {\n"
"    border: 2px solid #8f8f91;\n"
"    border-radius: 6px;\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #f6f7fa, stop: 1 #dadbde);\n"
"    min-width: 80px;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #dadbde, stop: 1 #f6f7fa);\n"
"}\n"
"\n"
"QPushButton:flat {\n"
"    border: none; /* no border for a flat push button */\n"
"}\n"
"\n"
"QPushButton:default {\n"
"    border-color: rgb(255, 255, 255); /* make the default button prominent */\n"
"}"));
        audio_pushbutton = new QPushButton(merge_gui);
        audio_pushbutton->setObjectName(QStringLiteral("audio_pushbutton"));
        audio_pushbutton->setGeometry(QRect(10, 50, 93, 28));
        audio_pushbutton->setStyleSheet(QLatin1String("QPushButton {\n"
"    border: 2px solid #8f8f91;\n"
"    border-radius: 6px;\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #f6f7fa, stop: 1 #dadbde);\n"
"    min-width: 80px;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #dadbde, stop: 1 #f6f7fa);\n"
"}\n"
"\n"
"QPushButton:flat {\n"
"    border: none; /* no border for a flat push button */\n"
"}\n"
"\n"
"QPushButton:default {\n"
"    border-color: rgb(255, 255, 255); /* make the default button prominent */\n"
"}"));

        retranslateUi(merge_gui);

        QMetaObject::connectSlotsByName(merge_gui);
    } // setupUi

    void retranslateUi(QWidget *merge_gui)
    {
        merge_gui->setWindowTitle(QApplication::translate("merge_gui", "merge_gui", 0));
        ok->setText(QApplication::translate("merge_gui", "PushButton", 0));
        cancel->setText(QApplication::translate("merge_gui", "PushButton", 0));
        video_pushbutton->setText(QApplication::translate("merge_gui", "PushButton", 0));
        audio_pushbutton->setText(QApplication::translate("merge_gui", "PushButton", 0));
    } // retranslateUi

};

namespace Ui {
    class merge_gui: public Ui_merge_gui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MERGE_GUI_H
