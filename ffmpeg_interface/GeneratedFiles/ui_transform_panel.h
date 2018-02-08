/********************************************************************************
** Form generated from reading UI file 'transform_panel.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRANSFORM_PANEL_H
#define UI_TRANSFORM_PANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_transform_panel
{
public:
    QLabel *label_transform_name;
    QLabel *label_transform_icon;
    QPushButton *out_setting;
    QLabel *high_quantity;
    QPushButton *cut_part;
    QPushButton *clear_list;
    QPushButton *remove_list;
    QPushButton *play_select;
    QPushButton *ok_start;
    QPushButton *add_file_up;
    QTableWidget *tableWidget;
    QLabel *under_nameof_output_file;
    QPushButton *add_file_under;
    QPushButton *under_change;
    QComboBox *comboBox;

    void setupUi(QWidget *transform_panel)
    {
        if (transform_panel->objectName().isEmpty())
            transform_panel->setObjectName(QStringLiteral("transform_panel"));
        transform_panel->resize(744, 731);
        transform_panel->setStyleSheet(QStringLiteral("background-color:rgb(245,245,245)"));
        label_transform_name = new QLabel(transform_panel);
        label_transform_name->setObjectName(QStringLiteral("label_transform_name"));
        label_transform_name->setGeometry(QRect(10, 10, 72, 15));
        label_transform_icon = new QLabel(transform_panel);
        label_transform_icon->setObjectName(QStringLiteral("label_transform_icon"));
        label_transform_icon->setGeometry(QRect(20, 50, 30, 30));
        out_setting = new QPushButton(transform_panel);
        out_setting->setObjectName(QStringLiteral("out_setting"));
        out_setting->setGeometry(QRect(310, 40, 130, 40));
        high_quantity = new QLabel(transform_panel);
        high_quantity->setObjectName(QStringLiteral("high_quantity"));
        high_quantity->setGeometry(QRect(120, 55, 72, 15));
        cut_part = new QPushButton(transform_panel);
        cut_part->setObjectName(QStringLiteral("cut_part"));
        cut_part->setGeometry(QRect(310, 110, 130, 40));
        clear_list = new QPushButton(transform_panel);
        clear_list->setObjectName(QStringLiteral("clear_list"));
        clear_list->setGeometry(QRect(20, 110, 30, 30));
        remove_list = new QPushButton(transform_panel);
        remove_list->setObjectName(QStringLiteral("remove_list"));
        remove_list->setGeometry(QRect(60, 110, 30, 30));
        play_select = new QPushButton(transform_panel);
        play_select->setObjectName(QStringLiteral("play_select"));
        play_select->setGeometry(QRect(100, 110, 30, 30));
        ok_start = new QPushButton(transform_panel);
        ok_start->setObjectName(QStringLiteral("ok_start"));
        ok_start->setGeometry(QRect(590, 40, 130, 40));
        ok_start->setStyleSheet(QStringLiteral(""));
        add_file_up = new QPushButton(transform_panel);
        add_file_up->setObjectName(QStringLiteral("add_file_up"));
        add_file_up->setGeometry(QRect(590, 110, 130, 40));
        tableWidget = new QTableWidget(transform_panel);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(20, 160, 701, 431));
        under_nameof_output_file = new QLabel(transform_panel);
        under_nameof_output_file->setObjectName(QStringLiteral("under_nameof_output_file"));
        under_nameof_output_file->setGeometry(QRect(30, 680, 72, 15));
        add_file_under = new QPushButton(transform_panel);
        add_file_under->setObjectName(QStringLiteral("add_file_under"));
        add_file_under->setGeometry(QRect(590, 610, 130, 40));
        under_change = new QPushButton(transform_panel);
        under_change->setObjectName(QStringLiteral("under_change"));
        under_change->setGeometry(QRect(590, 680, 130, 40));
        comboBox = new QComboBox(transform_panel);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(170, 679, 330, 25));

        retranslateUi(transform_panel);

        QMetaObject::connectSlotsByName(transform_panel);
    } // setupUi

    void retranslateUi(QWidget *transform_panel)
    {
        transform_panel->setWindowTitle(QApplication::translate("transform_panel", "transform_panel", 0));
        label_transform_name->setText(QApplication::translate("transform_panel", "TextLabel", 0));
        label_transform_icon->setText(QApplication::translate("transform_panel", "TextLabel", 0));
        out_setting->setText(QApplication::translate("transform_panel", "PushButton", 0));
        high_quantity->setText(QApplication::translate("transform_panel", "TextLabel", 0));
        cut_part->setText(QApplication::translate("transform_panel", "PushButton", 0));
        clear_list->setText(QString());
        remove_list->setText(QString());
        play_select->setText(QString());
        ok_start->setText(QApplication::translate("transform_panel", "PushButton", 0));
        add_file_up->setText(QApplication::translate("transform_panel", "PushButton", 0));
        under_nameof_output_file->setText(QApplication::translate("transform_panel", "TextLabel", 0));
        add_file_under->setText(QApplication::translate("transform_panel", "PushButton", 0));
        under_change->setText(QApplication::translate("transform_panel", "PushButton", 0));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("transform_panel", "OUT_PUT", 0)
         << QApplication::translate("transform_panel", "\350\276\223\345\207\272\350\207\263\346\272\220\346\226\207\344\273\266\347\233\256\345\275\225", 0)
         << QApplication::translate("transform_panel", "\346\270\205\347\251\272\345\210\227\350\241\250", 0)
         << QApplication::translate("transform_panel", "\346\267\273\345\212\240\346\226\207\344\273\266\345\244\271", 0)
        );
    } // retranslateUi

};

namespace Ui {
    class transform_panel: public Ui_transform_panel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRANSFORM_PANEL_H
