/********************************************************************************
** Form generated from reading UI file 'ffmpeg_interface.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FFMPEG_INTERFACE_H
#define UI_FFMPEG_INTERFACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ffmpeg_interfaceClass
{
public:
    QPushButton *OUT_PUT;
    QPushButton *OPTION;
    QPushButton *REMOVE;
    QPushButton *REMOVE_ALL;
    QPushButton *START;

    void setupUi(QWidget *ffmpeg_interfaceClass)
    {
        if (ffmpeg_interfaceClass->objectName().isEmpty())
            ffmpeg_interfaceClass->setObjectName(QStringLiteral("ffmpeg_interfaceClass"));
        ffmpeg_interfaceClass->resize(733, 400);
        ffmpeg_interfaceClass->setStyleSheet(QStringLiteral("background-color:rgb(255, 255, 255)"));
        OUT_PUT = new QPushButton(ffmpeg_interfaceClass);
        OUT_PUT->setObjectName(QStringLiteral("OUT_PUT"));
        OUT_PUT->setGeometry(QRect(20, 30, 93, 28));
        OPTION = new QPushButton(ffmpeg_interfaceClass);
        OPTION->setObjectName(QStringLiteral("OPTION"));
        OPTION->setGeometry(QRect(150, 30, 93, 28));
        REMOVE = new QPushButton(ffmpeg_interfaceClass);
        REMOVE->setObjectName(QStringLiteral("REMOVE"));
        REMOVE->setGeometry(QRect(290, 30, 93, 28));
        REMOVE_ALL = new QPushButton(ffmpeg_interfaceClass);
        REMOVE_ALL->setObjectName(QStringLiteral("REMOVE_ALL"));
        REMOVE_ALL->setGeometry(QRect(430, 30, 93, 28));
        START = new QPushButton(ffmpeg_interfaceClass);
        START->setObjectName(QStringLiteral("START"));
        START->setGeometry(QRect(570, 30, 93, 28));

        retranslateUi(ffmpeg_interfaceClass);

        QMetaObject::connectSlotsByName(ffmpeg_interfaceClass);
    } // setupUi

    void retranslateUi(QWidget *ffmpeg_interfaceClass)
    {
        ffmpeg_interfaceClass->setWindowTitle(QApplication::translate("ffmpeg_interfaceClass", "ffmpeg_interface", 0));
        OUT_PUT->setText(QApplication::translate("ffmpeg_interfaceClass", "PushButton", 0));
        OPTION->setText(QApplication::translate("ffmpeg_interfaceClass", "PushButton", 0));
        REMOVE->setText(QApplication::translate("ffmpeg_interfaceClass", "PushButton", 0));
        REMOVE_ALL->setText(QApplication::translate("ffmpeg_interfaceClass", "PushButton", 0));
        START->setText(QApplication::translate("ffmpeg_interfaceClass", "PushButton", 0));
    } // retranslateUi

};

namespace Ui {
    class ffmpeg_interfaceClass: public Ui_ffmpeg_interfaceClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FFMPEG_INTERFACE_H
