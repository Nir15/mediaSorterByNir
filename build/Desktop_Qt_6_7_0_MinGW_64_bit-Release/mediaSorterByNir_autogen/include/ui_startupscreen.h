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
    QLabel *label_2;
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

        label_2 = new QLabel(startupScreen);
        label_2->setObjectName("label_2");
        QFont font1;
        font1.setPointSize(12);
        label_2->setFont(font1);
        label_2->setFrameShape(QFrame::Box);
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_2);

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
"Media Sorter By Nir!", nullptr));
        label_2->setText(QCoreApplication::translate("startupScreen", "The app is currently supporting the following formats:\n"
"JPG, PNG, TIFF, NEF*, ICO, SVG, MP4.\n"
"*Note that NEF format is working slowlier than others when displaying it on screen.", nullptr));
        startSortingButton->setText(QCoreApplication::translate("startupScreen", "Start Sorting", nullptr));
    } // retranslateUi

};

namespace Ui {
    class startupScreen: public Ui_startupScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTUPSCREEN_H
