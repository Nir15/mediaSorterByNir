#include "mainsortingwindow.h"
#include "ui_mainsortingwindow.h"

MainSortingWindow::MainSortingWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainSortingWindow)
{
    ui->setupUi(this);

    m_buttonGroupPtr = new QButtonGroup(this);
    m_buttonGroupPtr->addButton(ui->copyCheckBox);
    m_buttonGroupPtr->addButton(ui->moveCheckBox);
    m_buttonGroupPtr->setExclusive(true);
    ui->copyCheckBox->setChecked(true);
}

MainSortingWindow::~MainSortingWindow()
{
    delete ui;
}

// -----------------------------------------------------------------
// video related section
QPushButton *MainSortingWindow::getStopPushButton()
{
    return ui->stopPushButton;
}

QPushButton *MainSortingWindow::getForwardPushButton()
{
    return ui->forwardPushButton;
}

QPushButton *MainSortingWindow::getBackwardsPushButton()
{
    return ui->backwardsPushButton;
}

QPushButton *MainSortingWindow::getPlayPausePushButton()
{
    return ui->playPausePushButton;
}

QPushButton *MainSortingWindow::getVolumePushButton()
{
    return ui->volumePushButton;
}

QLabel *MainSortingWindow::getCurrentTimeLabel()
{
    return ui->currentTimeLabel;
}

QLabel *MainSortingWindow::getTotalTimeLabel()
{
    return ui->totalTimeLabel;
}

QSlider* MainSortingWindow::getDurationHorizontalSlider()
{
    return ui->DurationHorizontalSlider;
}

QSlider* MainSortingWindow::getVolumeHorizontalSlider()
{
    return ui->volumeHorizontalSlider;
}

// -----------------------------------------------------------------

QPushButton *MainSortingWindow::getBackButton()
{
    return ui->backPushButton;
}

QPushButton *MainSortingWindow::getNextButton()
{
    return ui->nextPushButton;
}

QPushButton *MainSortingWindow::getPreviousButton()
{
    return ui->previousPushButton;
}

QPushButton *MainSortingWindow::getDeleteButton()
{
    return ui->DeleteButton;
}

QPushButton *MainSortingWindow::getRotateClockwiseButton()
{
    return ui->rotateClockwiseButton;
}

QPushButton *MainSortingWindow::getUndoPushButton()
{
    return ui->undoPushButton;
}

QLabel *MainSortingWindow::getImageLabel()
{
    return ui->imageLabel;
}

QLabel *MainSortingWindow::getImageSizeLabel()
{
    return ui->imageSizeLabel;
}

QLabel *MainSortingWindow::getImageNameLabel()
{
    return ui->imageNameLabel;
}

QLabel *MainSortingWindow::getDateModifiedLabel()
{
    return ui->dateModifiedLabel;
}

QLabel *MainSortingWindow::getfilterNumImagesLeftLabel()
{
    return ui->filterNumImagesLeftLabel;
}

QLabel *MainSortingWindow::getVxIconLabel()
{
    return ui->vxIconLabel;
}

QLabel *MainSortingWindow::getVxTextLabel()
{
    return ui->vxTextLabel;
}

QLabel *MainSortingWindow::getFoldersAvailableLabel()
{
    return ui->FoldersAvailableLabel;
}

QLabel *MainSortingWindow::getCurrentlyInLabel()
{
    return ui->currentlyInLabel;
}

QScrollArea *MainSortingWindow::getCurrentlyInScrollArea()
{
    return ui->currentlyInScrollArea;
}

QScrollArea *MainSortingWindow::getFoldersAvailableScrollArea()
{
    return ui->foldersAvailableScrollArea;
}

QTextEdit *MainSortingWindow::getFilterTextEdit()
{
    return ui->FilterTextEdit;
}

QCheckBox *MainSortingWindow::getCopyCheckBox()
{
    return ui->copyCheckBox;
}

QCheckBox *MainSortingWindow::getMoveCheckBox()
{
    return ui->moveCheckBox;
}


QStringList MainSortingWindow::filterImageList(const QStringList& originalImageList, const QString& filter)
{
    // create a temp empty QstringList
    QStringList temp;
    // loop over every element of the string list and check if it contains the filter
    for (int i=0; i<originalImageList.size(); i++){
        if (originalImageList[i].contains(filter, Qt::CaseInsensitive))
            temp << originalImageList[i];
    }
    return temp;
}

// activate the functions which are responsible for everything that keyboard press do
void MainSortingWindow::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();

    switch(key){
    case Qt::Key_Right:
        qDebug() << "Right MainSortingWindow!";
        break;
    case Qt::Key_Left:
        qDebug() << "Left MainSortingWindow!";
        break;
    case Qt::Key_D:
        // call DELETE image function
        qDebug() << "D MainSortingWindow!";
        break;
    case Qt::Key_C:
        // call COPY image function
        qDebug() << "C MainSortingWindow!";
        break;
    case Qt::Key_M:
        // call MOVE image function
        qDebug() << "M MainSortingWindow!";
        break;
    case Qt::Key_R:
        qDebug() << "R MainSortingWindow!";
        break;
    default:
        break;
    }

}
