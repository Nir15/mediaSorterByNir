#ifndef MAINSORTINGWINDOW_H
#define MAINSORTINGWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QScrollArea>
#include <QTextEdit>
#include <QButtonGroup>
#include <QKeyEvent>
#include <QCheckBox>
#include <QSlider>


namespace Ui {
class MainSortingWindow;
}

class MainSortingWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainSortingWindow(QWidget *parent = nullptr);
    ~MainSortingWindow();
    QPushButton*                getBackButton();
    QPushButton*                getNextButton();
    QPushButton*                getPreviousButton();
    QPushButton*                getDeleteButton();
    QPushButton*                getRotateClockwiseButton();
    QPushButton*                getUndoPushButton();
    //video related objects
    QPushButton*                getVolumePushButton();
    QPushButton*                getStopPushButton();
    QPushButton*                getBackwardsPushButton();
    QPushButton*                getForwardPushButton();
    QPushButton*                getPlayPausePushButton();
    QLabel*                     getTotalTimeLabel();
    QLabel*                     getCurrentTimeLabel();
    QSlider*                    getDurationHorizontalSlider();
    QSlider*                    getVolumeHorizontalSlider();
    //video related objects
    QLabel*                     getImageLabel();
    QLabel*                     getImageSizeLabel();
    QLabel*                     getImageNameLabel();
    QLabel*                     getDateModifiedLabel();
    QLabel*                     getfilterNumImagesLeftLabel();
    QLabel*                     getVxIconLabel();
    QLabel*                     getVxTextLabel();
    QLabel*                     getFoldersAvailableLabel();
    QLabel*                     getCurrentlyInLabel();
    QScrollArea*                getCurrentlyInScrollArea();
    QScrollArea*                getFoldersAvailableScrollArea();
    QTextEdit*                  getFilterTextEdit();
    QCheckBox*                  getCopyCheckBox();
    QCheckBox*                  getMoveCheckBox();

    QStringList filterImageList(const QStringList& originalImageList, const QString& filter);

    QButtonGroup* m_buttonGroupPtr;

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::MainSortingWindow *ui;
};

#endif // MAINSORTINGWINDOW_H
