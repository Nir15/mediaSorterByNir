/********************************************************************************
** Form generated from reading UI file 'mainsortingwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINSORTINGWINDOW_H
#define UI_MAINSORTINGWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainSortingWindow
{
public:
    QHBoxLayout *horizontalLayout_10;
    QVBoxLayout *verticalLayout_13;
    QLabel *imageLabel;
    QVBoxLayout *verticalLayout_12;
    QVBoxLayout *verticalLayout_11;
    QHBoxLayout *horizontalLayout_8;
    QLabel *currentTimeLabel;
    QSlider *DurationHorizontalSlider;
    QLabel *totalTimeLabel;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *backwardsPushButton;
    QPushButton *stopPushButton;
    QPushButton *playPausePushButton;
    QPushButton *forwardPushButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *volumePushButton;
    QSlider *volumeHorizontalSlider;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *backPushButton;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_14;
    QHBoxLayout *horizontalLayout_9;
    QVBoxLayout *verticalLayout_10;
    QVBoxLayout *verticalLayout_7;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QLabel *currentlyInLabel;
    QScrollArea *currentlyInScrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QLabel *FoldersAvailableLabel;
    QScrollArea *foldersAvailableScrollArea;
    QWidget *scrollAreaWidgetContents_2;
    QVBoxLayout *verticalLayout_5;
    QTextEdit *FilterTextEdit;
    QLabel *filterNumImagesLeftLabel;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_4;
    QCheckBox *copyCheckBox;
    QCheckBox *moveCheckBox;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *undoPushButton;
    QHBoxLayout *horizontalLayout_5;
    QLabel *vxIconLabel;
    QLabel *vxTextLabel;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_8;
    QLabel *imageNameLabel;
    QLabel *imageSizeLabel;
    QLabel *dateModifiedLabel;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout;
    QPushButton *previousPushButton;
    QPushButton *nextPushButton;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *rotateClockwiseButton;
    QPushButton *DeleteButton;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *MainSortingWindow)
    {
        if (MainSortingWindow->objectName().isEmpty())
            MainSortingWindow->setObjectName("MainSortingWindow");
        MainSortingWindow->resize(1528, 928);
        QFont font;
        font.setFamilies({QString::fromUtf8("Calibri")});
        font.setPointSize(12);
        MainSortingWindow->setFont(font);
        horizontalLayout_10 = new QHBoxLayout(MainSortingWindow);
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        verticalLayout_13 = new QVBoxLayout();
        verticalLayout_13->setObjectName("verticalLayout_13");
        imageLabel = new QLabel(MainSortingWindow);
        imageLabel->setObjectName("imageLabel");
        imageLabel->setMinimumSize(QSize(700, 700));
        imageLabel->setMaximumSize(QSize(700, 700));
        imageLabel->setFrameShape(QFrame::Box);

        verticalLayout_13->addWidget(imageLabel);

        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setObjectName("verticalLayout_12");
        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setObjectName("verticalLayout_11");
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        currentTimeLabel = new QLabel(MainSortingWindow);
        currentTimeLabel->setObjectName("currentTimeLabel");
        currentTimeLabel->setFrameShape(QFrame::Box);
        currentTimeLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_8->addWidget(currentTimeLabel);

        DurationHorizontalSlider = new QSlider(MainSortingWindow);
        DurationHorizontalSlider->setObjectName("DurationHorizontalSlider");
        DurationHorizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_8->addWidget(DurationHorizontalSlider);

        totalTimeLabel = new QLabel(MainSortingWindow);
        totalTimeLabel->setObjectName("totalTimeLabel");
        totalTimeLabel->setFrameShape(QFrame::Box);
        totalTimeLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_8->addWidget(totalTimeLabel);


        verticalLayout_11->addLayout(horizontalLayout_8);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        backwardsPushButton = new QPushButton(MainSortingWindow);
        backwardsPushButton->setObjectName("backwardsPushButton");

        horizontalLayout_7->addWidget(backwardsPushButton);

        stopPushButton = new QPushButton(MainSortingWindow);
        stopPushButton->setObjectName("stopPushButton");

        horizontalLayout_7->addWidget(stopPushButton);

        playPausePushButton = new QPushButton(MainSortingWindow);
        playPausePushButton->setObjectName("playPausePushButton");

        horizontalLayout_7->addWidget(playPausePushButton);

        forwardPushButton = new QPushButton(MainSortingWindow);
        forwardPushButton->setObjectName("forwardPushButton");

        horizontalLayout_7->addWidget(forwardPushButton);

        horizontalSpacer = new QSpacerItem(238, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer);

        volumePushButton = new QPushButton(MainSortingWindow);
        volumePushButton->setObjectName("volumePushButton");

        horizontalLayout_7->addWidget(volumePushButton);

        volumeHorizontalSlider = new QSlider(MainSortingWindow);
        volumeHorizontalSlider->setObjectName("volumeHorizontalSlider");
        volumeHorizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_7->addWidget(volumeHorizontalSlider);

        horizontalSpacer_2 = new QSpacerItem(78, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_2);


        verticalLayout_11->addLayout(horizontalLayout_7);


        verticalLayout_12->addLayout(verticalLayout_11);

        backPushButton = new QPushButton(MainSortingWindow);
        backPushButton->setObjectName("backPushButton");
        backPushButton->setMinimumSize(QSize(80, 24));
        backPushButton->setMaximumSize(QSize(80, 24));

        verticalLayout_12->addWidget(backPushButton);


        verticalLayout_13->addLayout(verticalLayout_12);

        verticalSpacer = new QSpacerItem(20, 88, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_13->addItem(verticalSpacer);


        horizontalLayout_10->addLayout(verticalLayout_13);

        verticalLayout_14 = new QVBoxLayout();
        verticalLayout_14->setObjectName("verticalLayout_14");
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName("verticalLayout_10");
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName("verticalLayout_7");
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName("verticalLayout_6");
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        currentlyInLabel = new QLabel(MainSortingWindow);
        currentlyInLabel->setObjectName("currentlyInLabel");
        currentlyInLabel->setMinimumSize(QSize(224, 27));
        currentlyInLabel->setMaximumSize(QSize(224, 27));
        currentlyInLabel->setFont(font);
        currentlyInLabel->setFrameShape(QFrame::Box);
        currentlyInLabel->setFrameShadow(QFrame::Plain);
        currentlyInLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(currentlyInLabel);

        currentlyInScrollArea = new QScrollArea(MainSortingWindow);
        currentlyInScrollArea->setObjectName("currentlyInScrollArea");
        currentlyInScrollArea->setMinimumSize(QSize(224, 314));
        currentlyInScrollArea->setMaximumSize(QSize(224, 314));
        currentlyInScrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 222, 312));
        currentlyInScrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_3->addWidget(currentlyInScrollArea);


        horizontalLayout_4->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        FoldersAvailableLabel = new QLabel(MainSortingWindow);
        FoldersAvailableLabel->setObjectName("FoldersAvailableLabel");
        FoldersAvailableLabel->setMinimumSize(QSize(224, 27));
        FoldersAvailableLabel->setMaximumSize(QSize(224, 27));
        FoldersAvailableLabel->setFont(font);
        FoldersAvailableLabel->setFrameShape(QFrame::Box);
        FoldersAvailableLabel->setFrameShadow(QFrame::Plain);
        FoldersAvailableLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(FoldersAvailableLabel);

        foldersAvailableScrollArea = new QScrollArea(MainSortingWindow);
        foldersAvailableScrollArea->setObjectName("foldersAvailableScrollArea");
        foldersAvailableScrollArea->setMinimumSize(QSize(224, 314));
        foldersAvailableScrollArea->setMaximumSize(QSize(224, 314));
        foldersAvailableScrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName("scrollAreaWidgetContents_2");
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 222, 312));
        foldersAvailableScrollArea->setWidget(scrollAreaWidgetContents_2);

        verticalLayout_2->addWidget(foldersAvailableScrollArea);


        horizontalLayout_4->addLayout(verticalLayout_2);


        verticalLayout_6->addLayout(horizontalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        FilterTextEdit = new QTextEdit(MainSortingWindow);
        FilterTextEdit->setObjectName("FilterTextEdit");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(FilterTextEdit->sizePolicy().hasHeightForWidth());
        FilterTextEdit->setSizePolicy(sizePolicy);
        FilterTextEdit->setMinimumSize(QSize(451, 31));
        FilterTextEdit->setMaximumSize(QSize(451, 31));
        FilterTextEdit->setFrameShape(QFrame::Box);

        verticalLayout_5->addWidget(FilterTextEdit);

        filterNumImagesLeftLabel = new QLabel(MainSortingWindow);
        filterNumImagesLeftLabel->setObjectName("filterNumImagesLeftLabel");
        filterNumImagesLeftLabel->setMinimumSize(QSize(451, 20));
        filterNumImagesLeftLabel->setMaximumSize(QSize(451, 31));
        filterNumImagesLeftLabel->setFrameShape(QFrame::Box);

        verticalLayout_5->addWidget(filterNumImagesLeftLabel);


        verticalLayout_6->addLayout(verticalLayout_5);


        verticalLayout_7->addLayout(verticalLayout_6);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        copyCheckBox = new QCheckBox(MainSortingWindow);
        copyCheckBox->setObjectName("copyCheckBox");
        copyCheckBox->setMinimumSize(QSize(458, 31));
        copyCheckBox->setMaximumSize(QSize(458, 31));

        verticalLayout_4->addWidget(copyCheckBox);

        moveCheckBox = new QCheckBox(MainSortingWindow);
        moveCheckBox->setObjectName("moveCheckBox");
        moveCheckBox->setMinimumSize(QSize(458, 31));
        moveCheckBox->setMaximumSize(QSize(458, 31));

        verticalLayout_4->addWidget(moveCheckBox);


        verticalLayout->addLayout(verticalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        undoPushButton = new QPushButton(MainSortingWindow);
        undoPushButton->setObjectName("undoPushButton");

        horizontalLayout_3->addWidget(undoPushButton);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        vxIconLabel = new QLabel(MainSortingWindow);
        vxIconLabel->setObjectName("vxIconLabel");
        vxIconLabel->setMinimumSize(QSize(40, 40));
        vxIconLabel->setMaximumSize(QSize(40, 40));
        vxIconLabel->setFrameShape(QFrame::NoFrame);

        horizontalLayout_5->addWidget(vxIconLabel);

        vxTextLabel = new QLabel(MainSortingWindow);
        vxTextLabel->setObjectName("vxTextLabel");
        vxTextLabel->setMinimumSize(QSize(500, 80));
        vxTextLabel->setMaximumSize(QSize(500, 80));
        vxTextLabel->setFrameShape(QFrame::NoFrame);

        horizontalLayout_5->addWidget(vxTextLabel);


        horizontalLayout_3->addLayout(horizontalLayout_5);


        verticalLayout->addLayout(horizontalLayout_3);


        verticalLayout_7->addLayout(verticalLayout);


        verticalLayout_10->addLayout(verticalLayout_7);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName("verticalLayout_8");
        imageNameLabel = new QLabel(MainSortingWindow);
        imageNameLabel->setObjectName("imageNameLabel");
        imageNameLabel->setMinimumSize(QSize(400, 28));
        imageNameLabel->setMaximumSize(QSize(400, 28));
        imageNameLabel->setFrameShape(QFrame::Box);

        verticalLayout_8->addWidget(imageNameLabel);

        imageSizeLabel = new QLabel(MainSortingWindow);
        imageSizeLabel->setObjectName("imageSizeLabel");
        imageSizeLabel->setMinimumSize(QSize(400, 28));
        imageSizeLabel->setMaximumSize(QSize(400, 28));
        imageSizeLabel->setFrameShape(QFrame::Box);

        verticalLayout_8->addWidget(imageSizeLabel);

        dateModifiedLabel = new QLabel(MainSortingWindow);
        dateModifiedLabel->setObjectName("dateModifiedLabel");
        dateModifiedLabel->setMinimumSize(QSize(400, 28));
        dateModifiedLabel->setMaximumSize(QSize(400, 28));
        dateModifiedLabel->setFrameShape(QFrame::Box);

        verticalLayout_8->addWidget(dateModifiedLabel);


        horizontalLayout_6->addLayout(verticalLayout_8);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName("verticalLayout_9");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        previousPushButton = new QPushButton(MainSortingWindow);
        previousPushButton->setObjectName("previousPushButton");
        previousPushButton->setMinimumSize(QSize(150, 30));
        previousPushButton->setMaximumSize(QSize(150, 30));

        horizontalLayout->addWidget(previousPushButton);

        nextPushButton = new QPushButton(MainSortingWindow);
        nextPushButton->setObjectName("nextPushButton");
        nextPushButton->setMinimumSize(QSize(150, 30));
        nextPushButton->setMaximumSize(QSize(150, 30));

        horizontalLayout->addWidget(nextPushButton);


        verticalLayout_9->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        rotateClockwiseButton = new QPushButton(MainSortingWindow);
        rotateClockwiseButton->setObjectName("rotateClockwiseButton");
        rotateClockwiseButton->setMinimumSize(QSize(150, 30));
        rotateClockwiseButton->setMaximumSize(QSize(150, 30));

        horizontalLayout_2->addWidget(rotateClockwiseButton);

        DeleteButton = new QPushButton(MainSortingWindow);
        DeleteButton->setObjectName("DeleteButton");
        DeleteButton->setMinimumSize(QSize(150, 30));
        DeleteButton->setMaximumSize(QSize(150, 30));

        horizontalLayout_2->addWidget(DeleteButton);


        verticalLayout_9->addLayout(horizontalLayout_2);


        horizontalLayout_6->addLayout(verticalLayout_9);


        verticalLayout_10->addLayout(horizontalLayout_6);


        horizontalLayout_9->addLayout(verticalLayout_10);

        horizontalSpacer_3 = new QSpacerItem(78, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_3);


        verticalLayout_14->addLayout(horizontalLayout_9);

        verticalSpacer_2 = new QSpacerItem(20, 208, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_14->addItem(verticalSpacer_2);


        horizontalLayout_10->addLayout(verticalLayout_14);


        retranslateUi(MainSortingWindow);

        QMetaObject::connectSlotsByName(MainSortingWindow);
    } // setupUi

    void retranslateUi(QWidget *MainSortingWindow)
    {
        MainSortingWindow->setWindowTitle(QCoreApplication::translate("MainSortingWindow", "Form", nullptr));
        imageLabel->setText(QString());
        currentTimeLabel->setText(QCoreApplication::translate("MainSortingWindow", "00:00:00", nullptr));
        totalTimeLabel->setText(QCoreApplication::translate("MainSortingWindow", "00:00:00", nullptr));
        backwardsPushButton->setText(QString());
        stopPushButton->setText(QString());
        playPausePushButton->setText(QString());
        forwardPushButton->setText(QString());
        volumePushButton->setText(QString());
        backPushButton->setText(QCoreApplication::translate("MainSortingWindow", "Back", nullptr));
        currentlyInLabel->setText(QCoreApplication::translate("MainSortingWindow", "Currently In", nullptr));
        FoldersAvailableLabel->setText(QCoreApplication::translate("MainSortingWindow", "Folders Available", nullptr));
        FilterTextEdit->setPlaceholderText(QCoreApplication::translate("MainSortingWindow", "Text filter of images names. For example: \"university\"", nullptr));
        filterNumImagesLeftLabel->setText(QString());
        copyCheckBox->setText(QCoreApplication::translate("MainSortingWindow", "Copy Image", nullptr));
        moveCheckBox->setText(QCoreApplication::translate("MainSortingWindow", "Move Image", nullptr));
        undoPushButton->setText(QCoreApplication::translate("MainSortingWindow", "Undo", nullptr));
        vxIconLabel->setText(QString());
        vxTextLabel->setText(QString());
        imageNameLabel->setText(QString());
        imageSizeLabel->setText(QString());
        dateModifiedLabel->setText(QString());
        previousPushButton->setText(QCoreApplication::translate("MainSortingWindow", "Previous", nullptr));
        nextPushButton->setText(QCoreApplication::translate("MainSortingWindow", "Next", nullptr));
        rotateClockwiseButton->setText(QCoreApplication::translate("MainSortingWindow", "Rotate 90", nullptr));
        DeleteButton->setText(QCoreApplication::translate("MainSortingWindow", "Delete Image", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainSortingWindow: public Ui_MainSortingWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINSORTINGWINDOW_H
