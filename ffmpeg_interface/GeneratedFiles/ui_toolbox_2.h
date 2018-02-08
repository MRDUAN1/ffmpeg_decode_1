/********************************************************************************
** Form generated from reading UI file 'toolbox_2.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TOOLBOX_2_H
#define UI_TOOLBOX_2_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_toolbox_2
{
public:

    void setupUi(QWidget *toolbox_2)
    {
        if (toolbox_2->objectName().isEmpty())
            toolbox_2->setObjectName(QStringLiteral("toolbox_2"));
        toolbox_2->resize(400, 300);

        retranslateUi(toolbox_2);

        QMetaObject::connectSlotsByName(toolbox_2);
    } // setupUi

    void retranslateUi(QWidget *toolbox_2)
    {
        toolbox_2->setWindowTitle(QApplication::translate("toolbox_2", "toolbox_2", 0));
    } // retranslateUi

};

namespace Ui {
    class toolbox_2: public Ui_toolbox_2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TOOLBOX_2_H
