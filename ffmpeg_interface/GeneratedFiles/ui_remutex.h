/********************************************************************************
** Form generated from reading UI file 'remutex.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REMUTEX_H
#define UI_REMUTEX_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_remutex
{
public:

    void setupUi(QWidget *remutex)
    {
        if (remutex->objectName().isEmpty())
            remutex->setObjectName(QStringLiteral("remutex"));
        remutex->resize(400, 300);

        retranslateUi(remutex);

        QMetaObject::connectSlotsByName(remutex);
    } // setupUi

    void retranslateUi(QWidget *remutex)
    {
        remutex->setWindowTitle(QApplication::translate("remutex", "remutex", 0));
    } // retranslateUi

};

namespace Ui {
    class remutex: public Ui_remutex {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REMUTEX_H
