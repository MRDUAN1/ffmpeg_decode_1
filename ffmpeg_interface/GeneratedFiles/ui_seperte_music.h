/********************************************************************************
** Form generated from reading UI file 'seperte_music.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEPERTE_MUSIC_H
#define UI_SEPERTE_MUSIC_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_seperte_music
{
public:
    QPushButton *ok;
    QLineEdit *lineEdit;
    QPushButton *cancel;
    QPushButton *choice_file;
    QLineEdit *lineEdit_2;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit_3;

    void setupUi(QWidget *seperte_music)
    {
        if (seperte_music->objectName().isEmpty())
            seperte_music->setObjectName(QStringLiteral("seperte_music"));
        seperte_music->resize(334, 139);
        ok = new QPushButton(seperte_music);
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
        lineEdit = new QLineEdit(seperte_music);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(120, 10, 200, 30));
        lineEdit->setStyleSheet(QLatin1String("QLineEdit {\n"
"    border: 2px solid gray;\n"
"    border-radius: 10px;\n"
"    padding: 0 8px;\n"
"    background: rgb(232,245,252);\n"
"    selection-background-color: darkgray;\n"
"}"));
        cancel = new QPushButton(seperte_music);
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
        choice_file = new QPushButton(seperte_music);
        choice_file->setObjectName(QStringLiteral("choice_file"));
        choice_file->setGeometry(QRect(10, 10, 93, 28));
        choice_file->setStyleSheet(QLatin1String("QPushButton {\n"
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
        lineEdit_2 = new QLineEdit(seperte_music);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(120, 50, 80, 30));
        lineEdit_2->setStyleSheet(QLatin1String("QLineEdit {\n"
"    border: 2px solid gray;\n"
"    border-radius: 10px;\n"
"    padding: 0 8px;\n"
"    background: rgb(232,245,252);\n"
"    selection-background-color: darkgray;\n"
"}"));
        label = new QLabel(seperte_music);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 60, 72, 15));
        label_2 = new QLabel(seperte_music);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(213, 57, 30, 15));
        lineEdit_3 = new QLineEdit(seperte_music);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(240, 50, 80, 30));
        lineEdit_3->setStyleSheet(QLatin1String("QLineEdit {\n"
"    border: 2px solid gray;\n"
"    border-radius: 10px;\n"
"    padding: 0 8px;\n"
"    background: rgb(232,245,252);\n"
"    selection-background-color: darkgray;\n"
"}"));

        retranslateUi(seperte_music);

        QMetaObject::connectSlotsByName(seperte_music);
    } // setupUi

    void retranslateUi(QWidget *seperte_music)
    {
        seperte_music->setWindowTitle(QApplication::translate("seperte_music", "seperte_music", 0));
        ok->setText(QApplication::translate("seperte_music", "PushButton", 0));
        cancel->setText(QApplication::translate("seperte_music", "PushButton", 0));
        choice_file->setText(QApplication::translate("seperte_music", "PushButton", 0));
        label->setText(QApplication::translate("seperte_music", "TextLabel", 0));
        label_2->setText(QApplication::translate("seperte_music", "--", 0));
    } // retranslateUi

};

namespace Ui {
    class seperte_music: public Ui_seperte_music {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEPERTE_MUSIC_H
