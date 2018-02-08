/********************************************************************************
** Form generated from reading UI file 'camera_play.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERA_PLAY_H
#define UI_CAMERA_PLAY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_camera_play
{
public:
    QLabel *label;
    QComboBox *filte_choice;
    QComboBox *size;
    QLabel *label_choice;
    QLabel *label_size_caption;
    QLineEdit *line_caption;
    QLabel *label_2;
    QLineEdit *X_;
    QLabel *label_3;
    QLineEdit *Y_;
    QComboBox *captions_color;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *size_resolution;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QWidget *camera_play)
    {
        if (camera_play->objectName().isEmpty())
            camera_play->setObjectName(QStringLiteral("camera_play"));
        camera_play->resize(400, 570);
        label = new QLabel(camera_play);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 0, 400, 400));
        filte_choice = new QComboBox(camera_play);
        filte_choice->setObjectName(QStringLiteral("filte_choice"));
        filte_choice->setGeometry(QRect(10, 440, 87, 22));
        filte_choice->setStyleSheet(QLatin1String("QPushButton {\n"
"    border: 2px solid rgba(125, 125, 125, 45);\n"
"    \n"
"}"));
        size = new QComboBox(camera_play);
        size->setObjectName(QStringLiteral("size"));
        size->setGeometry(QRect(140, 440, 87, 22));
        size->setStyleSheet(QLatin1String("QPushButton {\n"
"    border: 2px solid rgb(255, 0, 0)\n"
"    \n"
"}"));
        label_choice = new QLabel(camera_play);
        label_choice->setObjectName(QStringLiteral("label_choice"));
        label_choice->setGeometry(QRect(10, 410, 72, 15));
        label_choice->setStyleSheet(QLatin1String("QPushButton {\n"
"    border: 2px solid rgba(125, 125, 125, 45);\n"
"    \n"
"}"));
        label_size_caption = new QLabel(camera_play);
        label_size_caption->setObjectName(QStringLiteral("label_size_caption"));
        label_size_caption->setGeometry(QRect(140, 410, 72, 15));
        label_size_caption->setStyleSheet(QLatin1String("QPushButton {\n"
"    border: 2px solid rgba(125, 125, 125, 45);\n"
"    \n"
"}"));
        line_caption = new QLineEdit(camera_play);
        line_caption->setObjectName(QStringLiteral("line_caption"));
        line_caption->setGeometry(QRect(10, 515, 87, 21));
        line_caption->setStyleSheet(QLatin1String("QPushButton {\n"
"    border: 2px solid rgba(125, 125, 125, 45);\n"
"    \n"
"}"));
        label_2 = new QLabel(camera_play);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(140, 515, 15, 15));
        X_ = new QLineEdit(camera_play);
        X_->setObjectName(QStringLiteral("X_"));
        X_->setGeometry(QRect(152, 515, 30, 21));
        label_3 = new QLabel(camera_play);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(190, 515, 15, 15));
        Y_ = new QLineEdit(camera_play);
        Y_->setObjectName(QStringLiteral("Y_"));
        Y_->setGeometry(QRect(200, 515, 30, 21));
        captions_color = new QComboBox(camera_play);
        captions_color->setObjectName(QStringLiteral("captions_color"));
        captions_color->setGeometry(QRect(275, 515, 87, 22));
        captions_color->setStyleSheet(QLatin1String("QPushButton {\n"
"    border: 2px solid rgba(125, 125, 125, 45);\n"
"    \n"
"}"));
        label_4 = new QLabel(camera_play);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 480, 72, 15));
        label_5 = new QLabel(camera_play);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(140, 480, 72, 15));
        label_6 = new QLabel(camera_play);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(275, 480, 72, 15));
        size_resolution = new QLineEdit(camera_play);
        size_resolution->setObjectName(QStringLiteral("size_resolution"));
        size_resolution->setGeometry(QRect(140, 440, 87, 21));
        pushButton = new QPushButton(camera_play);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(275, 440, 93, 28));
        pushButton_2 = new QPushButton(camera_play);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(10, 515, 93, 28));

        retranslateUi(camera_play);

        QMetaObject::connectSlotsByName(camera_play);
    } // setupUi

    void retranslateUi(QWidget *camera_play)
    {
        camera_play->setWindowTitle(QApplication::translate("camera_play", "camera_play", 0));
        label->setText(QApplication::translate("camera_play", "TextLabel", 0));
        size->clear();
        size->insertItems(0, QStringList()
         << QApplication::translate("camera_play", "10", 0)
         << QApplication::translate("camera_play", "15", 0)
         << QApplication::translate("camera_play", "20", 0)
         << QApplication::translate("camera_play", "25", 0)
         << QApplication::translate("camera_play", "30", 0)
         << QApplication::translate("camera_play", "35", 0)
         << QApplication::translate("camera_play", "40", 0)
         << QApplication::translate("camera_play", "45", 0)
         << QApplication::translate("camera_play", "50", 0)
         << QApplication::translate("camera_play", "55", 0)
         << QApplication::translate("camera_play", "60", 0)
         << QApplication::translate("camera_play", "65", 0)
         << QApplication::translate("camera_play", "70", 0)
         << QApplication::translate("camera_play", "75", 0)
         << QApplication::translate("camera_play", "80", 0)
         << QApplication::translate("camera_play", "85", 0)
         << QApplication::translate("camera_play", "90", 0)
         << QApplication::translate("camera_play", "95", 0)
         << QApplication::translate("camera_play", "100", 0)
        );
        label_choice->setText(QApplication::translate("camera_play", "TextLabel", 0));
        label_size_caption->setText(QApplication::translate("camera_play", "TextLabel", 0));
        label_2->setText(QApplication::translate("camera_play", "X", 0));
        label_3->setText(QApplication::translate("camera_play", "Y", 0));
        label_4->setText(QApplication::translate("camera_play", "TextLabel", 0));
        label_5->setText(QApplication::translate("camera_play", "TextLabel", 0));
        label_6->setText(QApplication::translate("camera_play", "TextLabel", 0));
        pushButton->setText(QApplication::translate("camera_play", "PushButton", 0));
        pushButton_2->setText(QApplication::translate("camera_play", "PushButton", 0));
    } // retranslateUi

};

namespace Ui {
    class camera_play: public Ui_camera_play {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERA_PLAY_H
