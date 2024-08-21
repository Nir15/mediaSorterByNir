#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "startupscreen.h"
#include "pathsscreen.h"
#include "mainsortingwindow.h"
#include "clickablelabel.h"
#include "custommessagebox.h"
#include "hoveredobject.h"
#include <QDir>
#include <Qvector>
#include <QtMultimedia>
#include <QtMultimediaWidgets>
#include <QtCore>
#include <QtGui>


QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE


enum imageSwitchEnum {
    Next,
    Previous,
    Same,
    InValid
};

enum imageRotate {
    ClockWise,
    AntiClockWise
};

enum copyOrMove {
    Copy,
    Move
};

enum ClickOrTyped {
    Key_0 = 0,
    Key_1 = 1,
    Key_2 = 2,
    Key_3 = 3,
    Key_4 = 4,
    Key_5 = 5,
    Key_6 = 6,
    Key_7 = 7,
    Key_8 = 8,
    Key_9 = 9,
    Key_A = 10,
    Key_B = 11,
    Key_E = 12,
    Key_F = 13,
    Key_G = 14,
    Key_H = 15,
    Key_I = 16,
    Key_J = 17,
    Key_K = 18,
    Key_L = 19,
    Key_N = 20,
    Key_O = 21,
    Key_P = 22,
    Key_Q = 23,
    Key_S = 24,
    Key_T = 25,
    Key_U = 26,
    Key_V = 27,
    Key_W = 28,
    Key_X = 29,
    Key_Y = 30,
    Key_Z = 31,
    MouseClick
};

enum undoAction{
    MoveImage,
    CopyImageFromSrc,
    DeleteImageFromSrc,
    DeleteImageFromDst,
    NoAction
};

typedef struct undoStruct{
    QString imageName;
    QString srcFolder;
    QString dstFolder;
    undoAction action;
}undoStruct;



class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void switchImage(imageSwitchEnum);
    void deleteImage();

private slots:
    // start screen slots
    void startSortingButtonClicked();

    // paths (second) screen slots
    void pathsBackButtonClicked();
    void pathsNextButtonClicked();
    void pathsBrowseSrcButtonClicked();
    void pathsBrowseDstButtonClicked();

    // mainSortingWindow (third)
    void mainSortingBackButtonClicked();
    void rotateButtonClicked(imageRotate);
    void updateFilteredImageList(QString filter);

    void durationChanged(qint64 duration); // typedef long long qint64;
    void positionChanged(qint64 duration); // typedef long long qint64;

    void volumePushButtonClicked();
    void volumeHorizontalSliderValueChanged(int value);
    void durationHorizontalSliderValueChanged(int value);
    void stopPushButtonClicked();
    void forwardPushButtonClicked();
    void backwardsPushButtonClicked();
    void playPausePushButtonClicked();
    void loadNewVideo(const QString& videoName);
    bool clearMediaObjects();

private: //methods
    void findAvailableFolders();
    void findContainingFolders(QString fileName, QString dirPath);
    void AvailableFolderLabelClicked(ClickOrTyped cot = ClickOrTyped::MouseClick);
    void AvailableFolderLabelClickedWithCtrl();
    void CurrentlyInLabelClicked();
    char asciiToChar(const char c);
    int indexTranslation(const int index);
    void fillUndoStruct(QString name, QString src, QString dst, undoAction action);
    void undoLastAction();
    void setAllVideoInterface();
    void hideAllVideoInterface();
    void showAllVideoInterface();
    void updateDuration(qint64 duration); // typedef long long qint64;
    QImage libRawToQImage(const QString imagePath);


private: // fields
    Ui::Widget*                 ui;
    startupScreen*              m_startupScreenPtr;
    pathsScreen*                m_pathsScreenPtr;
    MainSortingWindow*          m_mainSortingWindowPtr;
    CustomMessageBox*           m_customMessageBoxPtr;
    QLabel*                     m_labelSelectedPtr;
    QStringList                 m_imagesList;
    QStringList                 m_imagesListFiltered;
    QStringList                 m_AvailableFoldersList;
    QDir                        m_srcDir;
    QDir                        m_dstDir;
    QString                     m_srcDirPath;
    QString                     m_dstDirPath;
    QPixmap                     m_imagePixmap;
    QTransform                  m_transformImage;
    QVector<undoStruct>         m_undoVector;
    QVector<ClickableLabel*>    m_AvailableFoldersPtrsVector;
    undoStruct                  m_undoStruct {"","","",undoAction::NoAction};

    QMediaPlayer*               m_mediaPlayer;
    QAudioOutput*               m_audioOutput;
    QVideoWidget*               m_videoWidget {nullptr};
    bool                        m_isMuted {false};
    bool                        m_isPaused {false};
    float                       m_realVolume {0.0};
    qint64                      m_videoDuration;

    bool                        m_folderListUpdated {false};
    bool                        m_isFilteredImageList {false};
    copyOrMove                  copyOrMoveSelect {copyOrMove::Copy};
    int                         m_imageCounter;
    unsigned int                m_srcFolderCounter {0};

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
};
#endif // WIDGET_H
