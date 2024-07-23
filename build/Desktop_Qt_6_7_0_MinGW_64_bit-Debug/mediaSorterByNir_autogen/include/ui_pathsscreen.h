/********************************************************************************
** Form generated from reading UI file 'pathsscreen.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PATHSSCREEN_H
#define UI_PATHSSCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_pathsScreen
{
public:
    QHBoxLayout *horizontalLayout_9;
    QVBoxLayout *verticalLayout_7;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QTextEdit *sourceTextEdit;
    QPushButton *sourceButton;
    QHBoxLayout *horizontalLayout_5;
    QTextEdit *sourceImagesCountTextEdit;
    QSpacerItem *horizontalSpacer_4;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_8;
    QTextEdit *destinationTextEdit;
    QPushButton *destinationButton;
    QHBoxLayout *horizontalLayout;
    QTextEdit *destinationImagesCountTextEdit;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_4;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *backButton;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer;
    QPushButton *nextButton;
    QPushButton *exitButton;

    void setupUi(QWidget *pathsScreen)
    {
        if (pathsScreen->objectName().isEmpty())
            pathsScreen->setObjectName("pathsScreen");
        pathsScreen->resize(820, 460);
        horizontalLayout_9 = new QHBoxLayout(pathsScreen);
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName("verticalLayout_7");
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName("verticalLayout_6");
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        label = new QLabel(pathsScreen);
        label->setObjectName("label");

        horizontalLayout_7->addWidget(label);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_2);


        verticalLayout_5->addLayout(horizontalLayout_7);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        sourceTextEdit = new QTextEdit(pathsScreen);
        sourceTextEdit->setObjectName("sourceTextEdit");
        QFont font;
        font.setPointSize(12);
        sourceTextEdit->setFont(font);
        sourceTextEdit->setReadOnly(true);

        horizontalLayout_2->addWidget(sourceTextEdit);

        sourceButton = new QPushButton(pathsScreen);
        sourceButton->setObjectName("sourceButton");

        horizontalLayout_2->addWidget(sourceButton);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        sourceImagesCountTextEdit = new QTextEdit(pathsScreen);
        sourceImagesCountTextEdit->setObjectName("sourceImagesCountTextEdit");
        sourceImagesCountTextEdit->setFont(font);
        sourceImagesCountTextEdit->setReadOnly(true);

        horizontalLayout_5->addWidget(sourceImagesCountTextEdit);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_5);


        verticalLayout_5->addLayout(verticalLayout);


        verticalLayout_6->addLayout(verticalLayout_5);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        label_2 = new QLabel(pathsScreen);
        label_2->setObjectName("label_2");

        horizontalLayout_6->addWidget(label_2);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_3);


        verticalLayout_2->addLayout(horizontalLayout_6);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        destinationTextEdit = new QTextEdit(pathsScreen);
        destinationTextEdit->setObjectName("destinationTextEdit");
        destinationTextEdit->setFont(font);
        destinationTextEdit->setReadOnly(true);

        horizontalLayout_8->addWidget(destinationTextEdit);

        destinationButton = new QPushButton(pathsScreen);
        destinationButton->setObjectName("destinationButton");

        horizontalLayout_8->addWidget(destinationButton);


        verticalLayout_2->addLayout(horizontalLayout_8);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        destinationImagesCountTextEdit = new QTextEdit(pathsScreen);
        destinationImagesCountTextEdit->setObjectName("destinationImagesCountTextEdit");
        destinationImagesCountTextEdit->setFont(font);
        destinationImagesCountTextEdit->setReadOnly(true);

        horizontalLayout->addWidget(destinationImagesCountTextEdit);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);


        verticalLayout_2->addLayout(horizontalLayout);


        verticalLayout_6->addLayout(verticalLayout_2);


        verticalLayout_7->addLayout(verticalLayout_6);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        backButton = new QPushButton(pathsScreen);
        backButton->setObjectName("backButton");

        horizontalLayout_3->addWidget(backButton);


        verticalLayout_4->addLayout(horizontalLayout_3);


        horizontalLayout_4->addLayout(verticalLayout_4);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        nextButton = new QPushButton(pathsScreen);
        nextButton->setObjectName("nextButton");
        nextButton->setEnabled(false);

        verticalLayout_3->addWidget(nextButton);

        exitButton = new QPushButton(pathsScreen);
        exitButton->setObjectName("exitButton");

        verticalLayout_3->addWidget(exitButton);


        horizontalLayout_4->addLayout(verticalLayout_3);


        verticalLayout_7->addLayout(horizontalLayout_4);


        horizontalLayout_9->addLayout(verticalLayout_7);


        retranslateUi(pathsScreen);

        QMetaObject::connectSlotsByName(pathsScreen);
    } // setupUi

    void retranslateUi(QWidget *pathsScreen)
    {
        pathsScreen->setWindowTitle(QCoreApplication::translate("pathsScreen", "Form", nullptr));
        label->setText(QCoreApplication::translate("pathsScreen", "Choose a source directory to sort images from:", nullptr));
        sourceButton->setText(QCoreApplication::translate("pathsScreen", "Browse", nullptr));
        label_2->setText(QCoreApplication::translate("pathsScreen", "Choose a destination directory to host the sorted images:", nullptr));
        destinationButton->setText(QCoreApplication::translate("pathsScreen", "Browse", nullptr));
        backButton->setText(QCoreApplication::translate("pathsScreen", "Back", nullptr));
        nextButton->setText(QCoreApplication::translate("pathsScreen", "Next", nullptr));
        exitButton->setText(QCoreApplication::translate("pathsScreen", "Exit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class pathsScreen: public Ui_pathsScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PATHSSCREEN_H
