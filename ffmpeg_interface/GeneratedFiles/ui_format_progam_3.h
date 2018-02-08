/********************************************************************************
** Form generated from reading UI file 'format_progam_3.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMAT_PROGAM_3_H
#define UI_FORMAT_PROGAM_3_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_format_progam_3
{
public:
    QFrame *frame;
    QSlider *horizontalSlider;
    QLabel *start_video;
    QLabel *end_video;
    QPushButton *start;
    QPushButton *break_;
    QPushButton *slow;
    QPushButton *quick;
    QPushButton *ok;
    QLineEdit *lineEdit;
    QFrame *frame_2;
    QPushButton *start_time_cut;
    QPushButton *end_cut_now;
    QPushButton *start_2;
    QPushButton *end_2;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLabel *cut_cut;
    QLabel *label_cut;
    QFrame *frame_3;
    QComboBox *filte_choice;
    QComboBox *size;
    QLabel *add_filter;
    QLabel *label_size_caption;
    QLabel *label_choice;
    QLineEdit *line_caption;
    QLineEdit *lineEdit_4;
    QLabel *label_size;
    QComboBox *captions_color;
    QCheckBox *checkBox;
    QPushButton *save_picture;

    void setupUi(QWidget *format_progam_3)
    {
        if (format_progam_3->objectName().isEmpty())
            format_progam_3->setObjectName(QStringLiteral("format_progam_3"));
        format_progam_3->resize(691, 562);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(format_progam_3->sizePolicy().hasHeightForWidth());
        format_progam_3->setSizePolicy(sizePolicy);
        frame = new QFrame(format_progam_3);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(10, 20, 400, 381));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalSlider = new QSlider(frame);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(10, 300, 160, 22));
        horizontalSlider->setOrientation(Qt::Horizontal);
        start_video = new QLabel(frame);
        start_video->setObjectName(QStringLiteral("start_video"));
        start_video->setGeometry(QRect(10, 330, 72, 15));
        end_video = new QLabel(frame);
        end_video->setObjectName(QStringLiteral("end_video"));
        end_video->setGeometry(QRect(140, 330, 72, 15));
        start = new QPushButton(frame);
        start->setObjectName(QStringLiteral("start"));
        start->setGeometry(QRect(250, 310, 30, 30));
        break_ = new QPushButton(frame);
        break_->setObjectName(QStringLiteral("break_"));
        break_->setGeometry(QRect(300, 310, 30, 30));
        slow = new QPushButton(frame);
        slow->setObjectName(QStringLiteral("slow"));
        slow->setGeometry(QRect(250, 350, 30, 30));
        quick = new QPushButton(frame);
        quick->setObjectName(QStringLiteral("quick"));
        quick->setGeometry(QRect(300, 350, 30, 30));
        ok = new QPushButton(format_progam_3);
        ok->setObjectName(QStringLiteral("ok"));
        ok->setGeometry(QRect(560, 50, 120, 40));
        lineEdit = new QLineEdit(format_progam_3);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(530, 120, 113, 21));
        frame_2 = new QFrame(format_progam_3);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setGeometry(QRect(10, 420, 400, 120));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        start_time_cut = new QPushButton(frame_2);
        start_time_cut->setObjectName(QStringLiteral("start_time_cut"));
        start_time_cut->setGeometry(QRect(0, 20, 100, 35));
        end_cut_now = new QPushButton(frame_2);
        end_cut_now->setObjectName(QStringLiteral("end_cut_now"));
        end_cut_now->setGeometry(QRect(210, 20, 100, 35));
        start_2 = new QPushButton(frame_2);
        start_2->setObjectName(QStringLiteral("start_2"));
        start_2->setGeometry(QRect(2, 80, 30, 30));
        end_2 = new QPushButton(frame_2);
        end_2->setObjectName(QStringLiteral("end_2"));
        end_2->setGeometry(QRect(210, 80, 30, 30));
        lineEdit_2 = new QLineEdit(frame_2);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(42, 80, 80, 30));
        lineEdit_3 = new QLineEdit(frame_2);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(250, 80, 80, 30));
        cut_cut = new QLabel(format_progam_3);
        cut_cut->setObjectName(QStringLiteral("cut_cut"));
        cut_cut->setGeometry(QRect(10, 410, 72, 15));
        label_cut = new QLabel(format_progam_3);
        label_cut->setObjectName(QStringLiteral("label_cut"));
        label_cut->setGeometry(QRect(430, 120, 72, 15));
        frame_3 = new QFrame(format_progam_3);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setGeometry(QRect(430, 190, 251, 201));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        filte_choice = new QComboBox(frame_3);
        filte_choice->setObjectName(QStringLiteral("filte_choice"));
        filte_choice->setGeometry(QRect(10, 50, 87, 22));
        filte_choice->setStyleSheet(QLatin1String("QPushButton {\n"
"    border: 2px solid rgba(125, 125, 125, 45);\n"
"    \n"
"}"));
        size = new QComboBox(frame_3);
        size->setObjectName(QStringLiteral("size"));
        size->setGeometry(QRect(140, 50, 87, 22));
        size->setStyleSheet(QLatin1String("QPushButton {\n"
"    border: 2px solid rgb(255, 0, 0)\n"
"    \n"
"}"));
        add_filter = new QLabel(frame_3);
        add_filter->setObjectName(QStringLiteral("add_filter"));
        add_filter->setGeometry(QRect(20, 20, 72, 15));
        add_filter->setStyleSheet(QLatin1String("QPushButton {\n"
"    border: 2px solid rgba(125, 125, 125, 45);\n"
"    \n"
"}"));
        label_size_caption = new QLabel(frame_3);
        label_size_caption->setObjectName(QStringLiteral("label_size_caption"));
        label_size_caption->setGeometry(QRect(140, 20, 72, 15));
        label_size_caption->setStyleSheet(QLatin1String("QPushButton {\n"
"    border: 2px solid rgba(125, 125, 125, 45);\n"
"    \n"
"}"));
        label_choice = new QLabel(frame_3);
        label_choice->setObjectName(QStringLiteral("label_choice"));
        label_choice->setGeometry(QRect(20, 90, 72, 15));
        label_choice->setStyleSheet(QLatin1String("QPushButton {\n"
"    border: 2px solid rgba(125, 125, 125, 45);\n"
"    \n"
"}"));
        line_caption = new QLineEdit(frame_3);
        line_caption->setObjectName(QStringLiteral("line_caption"));
        line_caption->setGeometry(QRect(10, 120, 87, 21));
        line_caption->setStyleSheet(QLatin1String("QPushButton {\n"
"    border: 2px solid rgba(125, 125, 125, 45);\n"
"    \n"
"}"));
        lineEdit_4 = new QLineEdit(frame_3);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(140, 120, 87, 21));
        lineEdit_4->setStyleSheet(QLatin1String("QPushButton {\n"
"    border: 2px solid rgba(125, 125, 125, 45);\n"
"    \n"
"}"));
        label_size = new QLabel(frame_3);
        label_size->setObjectName(QStringLiteral("label_size"));
        label_size->setGeometry(QRect(140, 90, 72, 15));
        label_size->setStyleSheet(QLatin1String("QPushButton {\n"
"    border: 2px solid rgba(125, 125, 125, 45);\n"
"    \n"
"}"));
        captions_color = new QComboBox(frame_3);
        captions_color->setObjectName(QStringLiteral("captions_color"));
        captions_color->setGeometry(QRect(10, 160, 87, 22));
        captions_color->setStyleSheet(QLatin1String("QPushButton {\n"
"    border: 2px solid rgba(125, 125, 125, 45);\n"
"    \n"
"}"));
        checkBox = new QCheckBox(format_progam_3);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(430, 160, 91, 19));
        save_picture = new QPushButton(format_progam_3);
        save_picture->setObjectName(QStringLiteral("save_picture"));
        save_picture->setGeometry(QRect(420, 50, 120, 40));

        retranslateUi(format_progam_3);

        QMetaObject::connectSlotsByName(format_progam_3);
    } // setupUi

    void retranslateUi(QWidget *format_progam_3)
    {
        format_progam_3->setWindowTitle(QApplication::translate("format_progam_3", "format_progam_3", 0));
        start_video->setText(QApplication::translate("format_progam_3", "TextLabel", 0));
        end_video->setText(QApplication::translate("format_progam_3", "TextLabel", 0));
        start->setText(QString());
        break_->setText(QString());
        slow->setText(QString());
        quick->setText(QString());
        ok->setText(QApplication::translate("format_progam_3", "PushButton", 0));
        start_time_cut->setText(QApplication::translate("format_progam_3", "PushButton", 0));
        end_cut_now->setText(QApplication::translate("format_progam_3", "PushButton", 0));
        start_2->setText(QApplication::translate("format_progam_3", "PushButton", 0));
        end_2->setText(QApplication::translate("format_progam_3", "PushButton", 0));
        cut_cut->setText(QApplication::translate("format_progam_3", "TextLabel", 0));
        label_cut->setText(QApplication::translate("format_progam_3", "TextLabel", 0));
        size->clear();
        size->insertItems(0, QStringList()
         << QApplication::translate("format_progam_3", "10", 0)
         << QApplication::translate("format_progam_3", "15", 0)
         << QApplication::translate("format_progam_3", "20", 0)
         << QApplication::translate("format_progam_3", "25", 0)
         << QApplication::translate("format_progam_3", "30", 0)
         << QApplication::translate("format_progam_3", "35", 0)
         << QApplication::translate("format_progam_3", "40", 0)
         << QApplication::translate("format_progam_3", "45", 0)
         << QApplication::translate("format_progam_3", "50", 0)
         << QApplication::translate("format_progam_3", "55", 0)
         << QApplication::translate("format_progam_3", "60", 0)
         << QApplication::translate("format_progam_3", "65", 0)
         << QApplication::translate("format_progam_3", "70", 0)
         << QApplication::translate("format_progam_3", "75", 0)
         << QApplication::translate("format_progam_3", "80", 0)
         << QApplication::translate("format_progam_3", "85", 0)
         << QApplication::translate("format_progam_3", "90", 0)
         << QApplication::translate("format_progam_3", "95", 0)
         << QApplication::translate("format_progam_3", "100", 0)
        );
        add_filter->setText(QApplication::translate("format_progam_3", "TextLabel", 0));
        label_size_caption->setText(QApplication::translate("format_progam_3", "TextLabel", 0));
        label_choice->setText(QApplication::translate("format_progam_3", "TextLabel", 0));
        label_size->setText(QApplication::translate("format_progam_3", "TextLabel", 0));
        checkBox->setText(QApplication::translate("format_progam_3", "CheckBox", 0));
        save_picture->setText(QApplication::translate("format_progam_3", "PushButton", 0));
    } // retranslateUi

};

namespace Ui {
    class format_progam_3: public Ui_format_progam_3 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMAT_PROGAM_3_H
