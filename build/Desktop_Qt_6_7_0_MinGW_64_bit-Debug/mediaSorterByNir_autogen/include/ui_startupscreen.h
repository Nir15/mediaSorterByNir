/********************************************************************************
** Form generated from reading UI file 'startupscreen.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTUPSCREEN_H
#define UI_STARTUPSCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_startupScreen
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QPushButton *startSortingButton;

    void setupUi(QWidget *startupScreen)
    {
        if (startupScreen->objectName().isEmpty())
            startupScreen->setObjectName("startupScreen");
        startupScreen->resize(731, 472);
        horizontalLayout = new QHBoxLayout(startupScreen);
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        label = new QLabel(startupScreen);
        label->setObjectName("label");
        QFont font;
        font.setFamilies({QString::fromUtf8("Calibri")});
        font.setPointSize(24);
        label->setFont(font);
        label->setFrameShape(QFrame::Box);
        label->setFrameShadow(QFrame::Plain);
        label->setTextFormat(Qt::PlainText);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        startSortingButton = new QPushButton(startupScreen);
        startSortingButton->setObjectName("startSortingButton");

        verticalLayout->addWidget(startSortingButton);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(startupScreen);

        QMetaObject::connectSlotsByName(startupScreen);
    } // setupUi

    void retranslateUi(QWidget *startupScreen)
    {
        startupScreen->setWindowTitle(QCoreApplication::translate("startupScreen", "Form", nullptr));
        label->setText(QCoreApplication::translate("startupScreen", "Welcome to\n"
"Sort Master!", nullptr));
        startSortingButton->setText(QCoreApplication::translate("startupScreen", "Start Sorting", nullptr));
    } // retranslateUi

};

namespace Ui {
    class startupScreen: public Ui_startupScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTUPSCREEN_H
