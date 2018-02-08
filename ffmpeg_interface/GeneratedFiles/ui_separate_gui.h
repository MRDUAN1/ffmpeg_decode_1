/********************************************************************************
** Form generated from reading UI file 'separate_gui.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEPARATE_GUI_H
#define UI_SEPARATE_GUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_separate_gui
{
public:

    void setupUi(QWidget *separate_gui)
    {
        if (separate_gui->objectName().isEmpty())
            separate_gui->setObjectName(QStringLiteral("separate_gui"));
        separate_gui->resize(400, 300);

        retranslateUi(separate_gui);

        QMetaObject::connectSlotsByName(separate_gui);
    } // setupUi

    void retranslateUi(QWidget *separate_gui)
    {
        separate_gui->setWindowTitle(QApplication::translate("separate_gui", "separate_gui", 0));
    } // retranslateUi

};

namespace Ui {
    class separate_gui: public Ui_separate_gui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEPARATE_GUI_H
