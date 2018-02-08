/********************************************************************************
** Form generated from reading UI file 'cut_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUT_DIALOG_H
#define UI_CUT_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_cut_dialog
{
public:

    void setupUi(QWidget *cut_dialog)
    {
        if (cut_dialog->objectName().isEmpty())
            cut_dialog->setObjectName(QStringLiteral("cut_dialog"));
        cut_dialog->resize(400, 300);

        retranslateUi(cut_dialog);

        QMetaObject::connectSlotsByName(cut_dialog);
    } // setupUi

    void retranslateUi(QWidget *cut_dialog)
    {
        cut_dialog->setWindowTitle(QApplication::translate("cut_dialog", "cut_dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class cut_dialog: public Ui_cut_dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUT_DIALOG_H
