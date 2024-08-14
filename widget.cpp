#include "widget.h"
#include "./ui_widget.h"
#include "qobjectdefs.h"
#include <QPushButton>
#include <QFileDialog>
#include <QStringList>
#include <QDir>
#include <QDebug>
#include <QMessageBox>
#include <QKeyEvent>
#include <QTransform>
#include <QFile>
#include <QVBoxLayout>
#include <QDirIterator>
#include <QRegularExpression>
#include <libraw.h>

#ifdef Q_OS_WIN
    #include <windows.h>
#elif defined(Q_OS_MAC)
    #include <sys/stat.h>
    #include <sys/types.h>
#endif

#define MAX_WIDTH_HEIGHT 700.0
#define MAX_UNDO_ACTIONS 1000

// ---------------------------Widget()--------------------------------------------------------------

static QVBoxLayout* QVBoxLayoutPtr;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget),
    m_imageCounter(0)
{
    ui->setupUi(this);
    m_startupScreenPtr = new startupScreen(this);
    QVBoxLayoutPtr = new QVBoxLayout(this);
    QVBoxLayoutPtr->addWidget(m_startupScreenPtr);
    this->setLayout(QVBoxLayoutPtr);

    m_pathsScreenPtr = new pathsScreen(this);
    m_mainSortingWindowPtr = new MainSortingWindow(this);

    m_customMessageBoxPtr = new CustomMessageBox(this);

    this->hide();
    m_pathsScreenPtr->hide();
    m_mainSortingWindowPtr->hide();

    //-------------- start screen --------------
    connect(m_startupScreenPtr->getStartSortingButton(),SIGNAL(clicked()),
            this, SLOT(startSortingButtonClicked()));

    //-------------- paths screen --------------
    connect(m_pathsScreenPtr->getBackButton(), SIGNAL(clicked()),
            this, SLOT(pathsBackButtonClicked()));

    connect(m_pathsScreenPtr->getExitButton(), &QPushButton::clicked, [=](){
        int ret = QMessageBox::critical(this,"Exit",
                                        "Are you sure?",
                                        QMessageBox::Yes | QMessageBox::No);
        if (ret == QMessageBox::Yes)
            QCoreApplication::quit();
    });

    connect(m_pathsScreenPtr->getNextButton(), &QPushButton::clicked,
            [=](){pathsNextButtonClicked();});

    connect(m_pathsScreenPtr->getDestinationButton(), SIGNAL(clicked()),
            this, SLOT(pathsBrowseDstButtonClicked()));

    connect(m_pathsScreenPtr->getSourceButton(), SIGNAL(clicked()),
            this, SLOT(pathsBrowseSrcButtonClicked()));



    // ----------- mainSortingWindow ---------

    m_mainSortingWindowPtr->getImageLabel()->installEventFilter(this); // Tie the event of clicking on image label to start/pause videos displayed

    connect(m_mainSortingWindowPtr->getBackButton(), &QPushButton::clicked,
            [=](){mainSortingBackButtonClicked();});

    setFocusPolicy(Qt::StrongFocus); // for capturing the right and left arrow presses

    connect(m_mainSortingWindowPtr->getNextButton(),&QPushButton::clicked,[=](){switchImage(imageSwitchEnum::Next);});
    connect(m_mainSortingWindowPtr->getPreviousButton(),&QPushButton::clicked,[=](){switchImage(imageSwitchEnum::Previous);});

    connect(m_mainSortingWindowPtr->getRotateClockwiseButton(),&QPushButton::clicked,[=](){rotateButtonClicked(imageRotate::ClockWise);});

    connect(m_mainSortingWindowPtr->getDeleteButton(),&QPushButton::clicked,m_customMessageBoxPtr, &CustomMessageBox::deleteButtonClicked);

    connect(m_mainSortingWindowPtr->getDeleteButton(),&QPushButton::clicked, [=](){
        if (m_customMessageBoxPtr->dontAskAgain){
            deleteImage();
        }
        else{
            if (m_customMessageBoxPtr->userChoiceOfDeletion == QMessageBox::Yes)
                deleteImage();
        }
    });

    // update the filtered list every time user typed text in the filter bar
    connect(m_mainSortingWindowPtr->getFilterTextEdit(), &QTextEdit::textChanged,
            [=](){updateFilteredImageList(m_mainSortingWindowPtr->getFilterTextEdit()->toPlainText());});

    connect(m_mainSortingWindowPtr->getUndoPushButton(), &QPushButton::clicked, [=](){undoLastAction();});

    // initialize a text for tooltips
    hoveredObject* foldersAvailbleHover = new hoveredObject(this);
    foldersAvailbleHover->setHoveredText("List of all subfolders available in chosen destination folder.\n"
                                         "By clicking on folder from the list, current image/video will be\n"
                                         "copied/moved to the chosen folder.");
    m_mainSortingWindowPtr->getFoldersAvailableLabel()->installEventFilter(foldersAvailbleHover);

    hoveredObject* currentlyInHover = new hoveredObject(this);
    currentlyInHover->setHoveredText("List of all subfolders in destination folder which contain a copy\n"
                                     "of the current image/video displayed. By clicking on folder from the list,\n"
                                     "current image/video will be removed from the chosen folder.");
    m_mainSortingWindowPtr->getCurrentlyInLabel()->installEventFilter(currentlyInHover);

    setAllVideoInterface();
}

// --------------------~Widget()--------------------------------------------------------------

Widget::~Widget()
{
    // when finish program, we must delete all images (and folder) deleted by the user,
    // because the deletion in the program is only pseudo deletion (see "deleteImage" method)
    QDir dir(m_srcDirPath + "/sortingAppDeletedImages");

    if (dir.exists()) {
        if (dir.removeRecursively()) {
            qDebug() << "Successfully deleted the folder and its contents:" << m_srcDirPath + "/sortingAppDeletedImages";
        } else {
            qWarning() << "Failed to delete the folder:" << m_srcDirPath + "/sortingAppDeletedImages";
        }
    }

    delete ui;
}

// ---------------------startSortingButtonClicked()-------------------------------------------

void Widget::startSortingButtonClicked()
{
    m_startupScreenPtr->hide(); // no more need for startup screen
    m_pathsScreenPtr->show();

    // set layout so the screen's components will shrink and grow dynamically
    delete QVBoxLayoutPtr;
    QVBoxLayoutPtr = new QVBoxLayout(this);
    QVBoxLayoutPtr->addWidget(m_pathsScreenPtr);
    this->setLayout(QVBoxLayoutPtr);

}

// ---------------------pathsBackButtonClicked()-----------------------------------------------

void Widget::pathsBackButtonClicked()
{
    m_pathsScreenPtr->hide();
    m_startupScreenPtr->show();

    // set layout so the screen's components will shrink and grow dynamically
    delete QVBoxLayoutPtr;
    QVBoxLayoutPtr = new QVBoxLayout(this);
    QVBoxLayoutPtr->addWidget(m_startupScreenPtr);
    this->setLayout(QVBoxLayoutPtr);
}

// ---------------------pathsNextButtonClicked()-----------------------------------------------

void Widget::pathsNextButtonClicked()
{
    m_pathsScreenPtr->hide();
    m_mainSortingWindowPtr->show();

    // set layout so the screen's components will shrink and grow dynamically
    delete QVBoxLayoutPtr;
    QVBoxLayoutPtr = new QVBoxLayout(this);
    QVBoxLayoutPtr->addWidget(m_mainSortingWindowPtr);
    this->setLayout(QVBoxLayoutPtr);

    m_mainSortingWindowPtr->getFilterTextEdit()->clear();           // clear filtered search
    m_mainSortingWindowPtr->getUndoPushButton()->setVisible(false); // hide undo button
    m_mainSortingWindowPtr->getVxTextLabel()->clear();              // hide vx text label
    m_mainSortingWindowPtr->getVxIconLabel()->clear();              // hide vx icon label
    ClickableLabel::s_chosenLabelPtr = nullptr;


    QDir dir;
    if (!dir.mkpath(m_srcDirPath + "/sortingAppDeletedImages")) {
        qWarning() << "Failed to create directory:" << m_srcDirPath + "/sortingAppDeletedImages";
    }

#ifdef Q_OS_WIN
    // Set the folder attributes to hidden
    if (!SetFileAttributesW(reinterpret_cast<const wchar_t*>((m_srcDirPath + "/sortingAppDeletedImages").utf16()), FILE_ATTRIBUTE_HIDDEN)) {
        qWarning() << "Failed to set folder as hidden:" << m_srcDirPath;
    }

    // Remove the hidden attribute from the parent folder
    if (!SetFileAttributesW(reinterpret_cast<const wchar_t*>(m_srcDirPath.utf16()), FILE_ATTRIBUTE_NORMAL)) {
        qWarning() << "Failed to unset hidden attribute for folder:" << m_srcDirPath;
    }

#elif defined(Q_OS_MAC)
    // Set the folder attributes to hidden
    QByteArray folderPath = (m_srcDirPath + "/sortingAppDeletedImages").toUtf8();
    if (chflags(folderPath.constData(), UF_HIDDEN) != 0) {
        qWarning() << "Failed to set folder as hidden:" << m_srcDirPath;
    }

    // Remove the hidden attribute from the parent folder
    QByteArray parentFolderPath = m_srcDirPath.toUtf8();
    if (chflags(parentFolderPath.constData(), 0) != 0) {
        qWarning() << "Failed to unset hidden attribute for folder:" << m_srcDirPath;
    }
#endif

    switchImage(imageSwitchEnum::Same);
}

// ---------------------pathsBrowseSrcButtonClicked()-------------------------------------------
// Function which opens a file browser for selecting the source directory to be sorted.

void Widget::pathsBrowseSrcButtonClicked()
{
        m_srcDirPath = QFileDialog::getExistingDirectory(
            this,                                                           // Parent widget
            tr("Source Directory"),                                         // Dialog title
            "C:\\",                                                         // Starting directory (optional)
            QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks    // Options to show directories only
        );


    if (!m_srcDirPath.isEmpty()){ // user selected valid path

        m_imageCounter = 0;
        m_srcDir = QDir(m_srcDirPath);

        // create a list of files by their names
        m_imagesList = m_srcDir.entryList(QStringList() << "*.jpg"
                                                        << "*.JPG"
                                                        << "*.jpeg"
                                                        << "*.JPEG"
                                                        << "*.mp4"
                                                        << "*.MP4"
                                                        << "*.tif"
                                                        << "*.TIF"
                                                        << "*.tiff"
                                                        << "*.TIFF"
                                                        << "*.svg"
                                                        << "*.SVG"
                                                        << "*.nef"
                                                        << "*.NEF",
                                                        QDir::Files);
        m_imagesListFiltered.clear();

        QStringList fileList = m_srcDir.entryList(QDir::AllEntries);



        // check for the number of images in directory
        int jpgCount = 0;
        for(int i=0;i<fileList.size();i++){
            if (fileList[i].endsWith(".jpg", Qt::CaseInsensitive)  ||
                fileList[i].endsWith(".jpeg", Qt::CaseInsensitive) ||
                fileList[i].endsWith(".mp4", Qt::CaseInsensitive)  ||
                fileList[i].endsWith(".tif", Qt::CaseInsensitive)  ||
                fileList[i].endsWith(".tiff", Qt::CaseInsensitive) ||
                fileList[i].endsWith(".nef", Qt::CaseInsensitive))
                jpgCount++;
        }

        if (jpgCount > 0){
            m_pathsScreenPtr->getSrcTextEdit()->setText(m_srcDirPath);
            QString tempJpgCount = QString("<span style='color:red; font-weight:bold;'>%1</span>").arg(QString::number(jpgCount));
            QString srcImagesCount = "The directory contains " + tempJpgCount + " media items.";
            m_pathsScreenPtr->getSrcImgCntTextEdit()->setText(srcImagesCount);
        }

        else {
            int ret = QMessageBox::critical(this,"Error!",
                                            "The selected folder cotains 0 media items.\n this folder cannot be selected. please choose a folder containing at least 1 media item.",
                                            QMessageBox::Ok | QMessageBox::Cancel);

            if (ret == QMessageBox::Ok){
                pathsBrowseSrcButtonClicked(); // user needs to choose again
            }
        }
    }

    // next screen of app will be available only if both src and dst directories have been selected
    if (!m_pathsScreenPtr->getSrcTextEdit()->document()->isEmpty() && !m_pathsScreenPtr->getDstTextEdit()->document()->isEmpty())
        m_pathsScreenPtr->getNextButton()->setEnabled(true);
}

// ---------------------pathsBrowseDstButtonClicked()--------------------------------------------
// Function which opes a file browser for selecting the destination directory to be sorted to.

void Widget::pathsBrowseDstButtonClicked()
{
    m_dstDirPath = QFileDialog::getExistingDirectory(
        this,                                                           // Parent widget
        tr("Destination Directory"),                                    // Dialog title
        "C:\\",                                                         // Starting directory (optional)
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks    // Options to show directories only
        );



    if (!m_dstDirPath.isEmpty()){ //user selected valid path

        // clear the last available lists from previous dst folder.
        m_AvailableFoldersList.clear();
        m_AvailableFoldersPtrsVector.clear();

        m_dstDir = QDir(m_dstDirPath);
        QStringList fileList = m_dstDir.entryList(QDir::NoDot | QDir::NoDotDot | QDir::Dirs);

        if (fileList.size() > 0){ // case the directory chosen is not empty of subfolders
            m_pathsScreenPtr->getDstTextEdit()->setText(m_dstDirPath);
            QString tempFolderCount = QString("<span style='color:red; font-weight:bold;'>%1</span>").arg(QString::number(fileList.size()));
            QString dstFolderCount = "The directory contains " + tempFolderCount + " subfolders.";
            m_pathsScreenPtr->getDstImgCntTextEdit()->setText(dstFolderCount);
        }

        else {
            int ret = QMessageBox::critical(this,"Error!",
                                            "The selected folder cotains 0 subfolders.\n this folder cannot be selected. please choose a folder containing at least 1 subfolder.",
                                            QMessageBox::Ok | QMessageBox::Cancel);

            if (ret == QMessageBox::Ok){
                pathsBrowseDstButtonClicked(); // user needs to choose again
            }
        }
    }

    // next screen of app will be available only if both src and dst directories have been selected
    if (!m_pathsScreenPtr->getSrcTextEdit()->document()->isEmpty() && !m_pathsScreenPtr->getDstTextEdit()->document()->isEmpty())
        m_pathsScreenPtr->getNextButton()->setEnabled(true);

    m_folderListUpdated = false;
}

// ---------------------mainSortingBackButtonClicked()-------------------------------------------

void Widget::mainSortingBackButtonClicked()
{
    m_mainSortingWindowPtr->hide();
    m_pathsScreenPtr->show();

    // set layout so the screen's components will shrink and grow dynamically
    delete QVBoxLayoutPtr;
    QVBoxLayoutPtr = new QVBoxLayout(this);
    QVBoxLayoutPtr->addWidget(m_pathsScreenPtr);
    this->setLayout(QVBoxLayoutPtr);

    m_undoVector.clear();   // remove all items from undo vector, since it is not required due to screen change
    m_undoVector.squeeze(); // clear all memory being by the vector used on the heap

    // when finish program, we must delete all images (and folder) deleted by the user,
    // because the deletion in the program is only pseudo deletion (see "deleteImage" method)
    QDir dir(m_srcDirPath + "/sortingAppDeletedImages");

    if (dir.exists()) {
        if (dir.removeRecursively()) {
            qDebug() << "Successfully deleted the folder and its contents:" << m_srcDirPath + "/sortingAppDeletedImages";
        } else {
            qWarning() << "Failed to delete the folder:" << m_srcDirPath + "/sortingAppDeletedImages";
        }
    }

}

// ---------------------rotateButtonClicked()-------------------------------------------

void Widget::rotateButtonClicked(imageRotate ir)
{

    if (ir == imageRotate::ClockWise){
        m_transformImage.rotate(90);
    }
    switchImage(imageSwitchEnum::Same);
}

// ---------------------updateFilteredImageList()-------------------------------------------
// After user typed filter for images, this function will update m_imagesListFiltered to contain only the
// images containing the filter in their names. then switchImage function will be called in order to
// present the first filtered image via m_imagesListFiltered list.

void Widget::updateFilteredImageList(QString filter)
{
    // 1. check what is the m_filteredImageList using the filterImageList function of m_mainSortingWindow,
    //    and filter which comes from this function
    m_imagesListFiltered.clear(); // empty the filtered list
    m_imagesListFiltered = m_mainSortingWindowPtr->filterImageList(m_imagesList, filter);

    if (!m_imagesListFiltered.empty()) { // need to reset m_imageCounter because of illegal index access can occur in stage 2
        m_imageCounter = 0;
        switchImage(imageSwitchEnum::Same); // 2. call switchImage function
    }
    else if (m_imagesListFiltered.empty() && !filter.isEmpty()){
        switchImage(imageSwitchEnum::InValid); // meaning the filter is incompatible to any of the images
    }



    // 3. check if m_filteredImageList is empty or not.
    //    a. if it is not empty, use this list to be the new list of the images to present (m_filteredImageList instead of m_imagesList)
    //    b. if it is empty, it means the filter is empty, so the original list m_imagesList is the one should be displayed.
}

// ---------------------keyPressEvent(QKeyEvent *event)-------------------------------------------
// this function is an overriden function, capturing the keyboard presses by the user. it is then
// call the correct function to activate.

void Widget::keyPressEvent(QKeyEvent *event)
{

    if (m_mainSortingWindowPtr->isVisible()){

        int key = event->key();

        switch(key){
            case Qt::Key_Right:
                qDebug() << "Right!";
                switchImage(imageSwitchEnum::Next);
                break;
            case Qt::Key_Left:
                switchImage(imageSwitchEnum::Previous);
                qDebug() << "Left!";
                break;
            case Qt::Key_D:
                // call DELETE image function
                if (m_customMessageBoxPtr->dontAskAgain){
                    deleteImage();
                }
                else{
                    emit m_mainSortingWindowPtr->getDeleteButton()->clicked();
                }
                qDebug() << "D!";
                break;
            case Qt::Key_C:
                // call COPY image function
                m_mainSortingWindowPtr->getCopyCheckBox()->setChecked(true);
                qDebug() << "C!";
                break;
            case Qt::Key_M:
                // call MOVE image function
                m_mainSortingWindowPtr->getMoveCheckBox()->setChecked(true);
                qDebug() << "M!";
                break;
            case Qt::Key_R:
                rotateButtonClicked(imageRotate::ClockWise);
                qDebug() << "R!";
                break;
            default:
                if (key >= Qt::Key_0 && key <= Qt::Key_9){
                    int index = key - Qt::Key_0; // for knowing the exact index
                    if (index < m_srcFolderCounter)
                        AvailableFolderLabelClicked((ClickOrTyped)index);
                }
                else if (key >= Qt::Key_A && key <= Qt::Key_Z){
                    // Ctrl+Z meaning undo keyboard shortcut, can only happen if previous action was made. otherwise nothing happens
                    if ((event->modifiers() & Qt::ControlModifier) && (event->key() == Qt::Key_Z) && m_undoVector.size()){
                            undoLastAction();
                    }
                    else {
                        int index = indexTranslation(key - Qt::Key_A + ClickOrTyped::Key_A); // for knowing the exact character index
                        qDebug() << (ClickOrTyped)index;
                        if (index < m_AvailableFoldersList.size())
                            AvailableFolderLabelClicked((ClickOrTyped)index);
                    }
                }
                break;
        }

    };
}

// ---------------------switchImage(imageSwitchEnum is)-------------------------------------------
// Function gets the direction to go to in the imageList, and presents the image and details about it.
// It can be called from multiple places in code, related to next or previous buttons but also related
// to filter applied.

void Widget::switchImage(imageSwitchEnum is){

    // the call for this function may occur via the next and previous buttons, but also from filter textedit.
    // therefor it is important to find out what is the reason of calling and adjust the image list apropriately
    QStringList localImageList = m_mainSortingWindowPtr->getFilterTextEdit()->toPlainText().isEmpty() ? m_imagesList : m_imagesListFiltered;
    m_isFilteredImageList = m_mainSortingWindowPtr->getFilterTextEdit()->toPlainText().isEmpty() ? false : true; // check if there is text in filter

    m_mainSortingWindowPtr->getfilterNumImagesLeftLabel()->setText(QString::number(localImageList.size()) + " images left after filter.");

    m_mainSortingWindowPtr->getNextButton()->setEnabled(true);
    m_mainSortingWindowPtr->getPreviousButton()->setEnabled(true);
    m_mainSortingWindowPtr->getDeleteButton()->setEnabled(true);
    m_mainSortingWindowPtr->getRotateClockwiseButton()->setEnabled(true);

    if (is == imageSwitchEnum::Next){ // advance to next image in directory
        m_imageCounter++;
        QTransform identityTransform;
        m_transformImage = identityTransform; // reset the rotation.
        if (m_imageCounter == localImageList.size())
            m_imageCounter = 0;

        // clear the comment about copy attempt from last picture presented
        m_mainSortingWindowPtr->getVxTextLabel()->clear();
        m_mainSortingWindowPtr->getVxIconLabel()->clear();

        // clear the grey background of the last picture's chosen folder
        if (ClickableLabel::s_chosenLabelPtr){
            ClickableLabel::s_chosenLabelPtr->clearClickedLabel();
        }
    }

    else if(is == imageSwitchEnum::Previous){ // go back to previous image in directory
        m_imageCounter--;
        QTransform identityTransform;
        m_transformImage = identityTransform; // reset the rotation.
        if (m_imageCounter == -1)
            m_imageCounter = localImageList.size() - 1;

        // clear the comment about copy attempt from last picture presented
        m_mainSortingWindowPtr->getVxTextLabel()->clear();
        m_mainSortingWindowPtr->getVxIconLabel()->clear();

        // clear the grey background of the last picture's chosen folder
        if (ClickableLabel::s_chosenLabelPtr){
            ClickableLabel::s_chosenLabelPtr->clearClickedLabel();
        }
    }
    else if (is == imageSwitchEnum::Same) { // stay on the same image as before. for rotating purposes and also for deleting images.
        // leave m_imageCounter the same value
    }
    else { // is == imageSwitchEnum::InValid. this occurs due to filter that does not match any image name in the folder
        // clear all labels, block all buttons. notify user the filter is incompatible
        m_mainSortingWindowPtr->getImageSizeLabel()->clear();
        m_mainSortingWindowPtr->getImageNameLabel()->clear();
        m_mainSortingWindowPtr->getDateModifiedLabel()->clear();
        m_mainSortingWindowPtr->getImageLabel()->clear();
        m_mainSortingWindowPtr->getNextButton()->setEnabled(false);
        m_mainSortingWindowPtr->getPreviousButton()->setEnabled(false);
        m_mainSortingWindowPtr->getDeleteButton()->setEnabled(false);
        m_mainSortingWindowPtr->getRotateClockwiseButton()->setEnabled(false);
        m_mainSortingWindowPtr->getfilterNumImagesLeftLabel()->setText("No media items match this filter.");
        hideAllVideoInterface();
        clearMediaObjects();
        return;
    }


    // situation where there is a filter applied, but no files left to match the filter.
    // the ONLY way to call switchImage function without imageSwitchEnum::InValid argument while there is a filter
    // not matching anything, is when we delete all files match the filter, yet there are more files
    // left in the folder. in this case we have to delete the filter and try a new one, or simply continue without filter.
    if (m_isFilteredImageList && m_imagesListFiltered.isEmpty()){
        // updateFilteredImageList(m_mainSortingWindowPtr->getFilterTextEdit()->toPlainText()); // this will cause a switchImage with imageSwitchEnum::InValid argument call
        switchImage(imageSwitchEnum::InValid); // meaning the filter is incompatible to any of the images
        return;
    }

    QFile jpgFile = m_srcDirPath + QString("/") + localImageList[m_imageCounter];

    // ImageSizeLabel filled with file size
    QString sizeOfImage = "Size of image is: ";

    if (jpgFile.size() < 1024){ // size of file is less than 1MB
        m_mainSortingWindowPtr->getImageSizeLabel()->setText(QString(sizeOfImage + QString("<span style='font-weight:bold;'>%1</span>").arg(QString::number(jpgFile.size()) + QString(" bytes."))));
    }
    else if (jpgFile.size() > 1024 && jpgFile.size() < 1024*1024){ // size of file is more than 1KB and less than 1MB
        m_mainSortingWindowPtr->getImageSizeLabel()->setText(QString(sizeOfImage + QString("<span style='font-weight:bold;'>%1</span>").arg(QString::number(jpgFile.size()/1024) + QString(" KB."))));
    }
    else { // size of file is more than 1MB
        m_mainSortingWindowPtr->getImageSizeLabel()->setText(QString(sizeOfImage + QString("<span style='font-weight:bold;'>%1</span>").arg(QString::number((jpgFile.size()*1.0)/(1024.0*1024.0),'f',1) + QString(" MB."))));
    }

    // ImageNameLabel filled with name of file
    m_mainSortingWindowPtr->getImageNameLabel()->setText(QString("File name: ") + QString("<span style='font-weight:bold;'>%1</span>").arg(localImageList[m_imageCounter]));

    // lastModifiedDate filled
    QFileInfo fileInfo(m_srcDirPath + QString("/") + localImageList[m_imageCounter]);
    QDateTime lastModified = fileInfo.lastModified();
    m_mainSortingWindowPtr->getDateModifiedLabel()->setText(QString("Last modified in: ") + QString("<span style='font-weight:bold;'>%1</span>").arg(lastModified.toString()));


    if (clearMediaObjects()){
        hideAllVideoInterface();
    }

    m_mainSortingWindowPtr->getImageLabel()->clear();

    if (fileInfo.suffix() == "mp4" || fileInfo.suffix() == "MP4"){ // video file
        loadNewVideo(m_srcDirPath + QString("/") + localImageList[m_imageCounter]);
        showAllVideoInterface();
    }

    else if (fileInfo.suffix() == "nef" || fileInfo.suffix() == "NEF"){ // .nef file
        // Convert LibRaw image to QImage
        QImage image = libRawToQImage(m_srcDirPath + QString("/") + localImageList[m_imageCounter]);

        m_imagePixmap = m_imagePixmap.fromImage(image);
        m_imagePixmap = m_imagePixmap.transformed(m_transformImage); // make the rotation if needed

        qDebug() << QString(":/") + localImageList[m_imageCounter];
        qDebug() << "m_imageCounter = " << m_imageCounter;

        float width = (float)m_imagePixmap.width();
        float height =  (float)m_imagePixmap.height();
        float scaleFactor = width > height ? (MAX_WIDTH_HEIGHT/width) : (MAX_WIDTH_HEIGHT/height);

        QRect rect = m_mainSortingWindowPtr->getImageLabel()->geometry();
        rect.setHeight(height*scaleFactor);
        rect.setWidth(width*scaleFactor);
        m_mainSortingWindowPtr->getImageLabel()->setGeometry(rect);

        qDebug() << "width = " << m_imagePixmap.width();
        qDebug() << "height = " << m_imagePixmap.height();
        m_mainSortingWindowPtr->getImageLabel()->setPixmap(m_imagePixmap.scaled(width*scaleFactor,height*scaleFactor,Qt::KeepAspectRatio,Qt::SmoothTransformation)); // image presented in label
    }

    else { // image file (.jpg or .tif)
        m_imagePixmap = QPixmap(m_srcDirPath + QString("/") + localImageList[m_imageCounter]);
        m_imagePixmap = m_imagePixmap.transformed(m_transformImage); // make the rotation if needed

        qDebug() << QString(":/") + localImageList[m_imageCounter];
        qDebug() << "m_imageCounter = " << m_imageCounter;

        float width = (float)m_imagePixmap.width();
        float height =  (float)m_imagePixmap.height();
        float scaleFactor = width > height ? (MAX_WIDTH_HEIGHT/width) : (MAX_WIDTH_HEIGHT/height);

        QRect rect = m_mainSortingWindowPtr->getImageLabel()->geometry();
        rect.setHeight(height*scaleFactor);
        rect.setWidth(width*scaleFactor);
        m_mainSortingWindowPtr->getImageLabel()->setGeometry(rect);

        qDebug() << "width = " << m_imagePixmap.width();
        qDebug() << "height = " << m_imagePixmap.height();
        m_mainSortingWindowPtr->getImageLabel()->setPixmap(m_imagePixmap.scaled(width*scaleFactor,height*scaleFactor,Qt::KeepAspectRatio,Qt::SmoothTransformation)); // image presented in label
    }

    // fill the list of folders available in the main destination folder chosen
    if (!m_folderListUpdated){
        findAvailableFolders();
        m_folderListUpdated = true;
    }
    findContainingFolders(localImageList[m_imageCounter], m_dstDirPath); // fill the list of folders (and sub-folders) containing the current image
}

// ---------------------deleteImage()-------------------------------------------
// being called when DeleteButton is clicked, or 'D' key is pressed

void Widget::deleteImage()
{
    QString imageName = m_isFilteredImageList ? m_imagesListFiltered[m_imageCounter] : m_imagesList[m_imageCounter];

    QFile file(m_srcDirPath + "/" + imageName);

    // the Qt framework does not support deleting and restoring images using recycle bin. therefore, the solution made to allow user
    // to undo deletion of images is to store the "deleted" images at a temporary folder, which is tranparent to user. this way
    // it will be possible to restor the image, and when exiting the app only then the images will be truely deleted.


    // if the current file is .mp4, we need to first stop it and clear its containing objects.
    // otherwise OS spots the file is being used, and we can't make any actions on him.
    if (clearMediaObjects()){
        hideAllVideoInterface();
    }

    if (file.rename(m_srcDirPath + "/sortingAppDeletedImages/" + imageName)){
        QPixmap icon(":/icons/V_NoBackground.png");
        m_mainSortingWindowPtr->getVxIconLabel()->setPixmap(icon.scaled(30,30,Qt::KeepAspectRatio));
        m_mainSortingWindowPtr->getVxTextLabel()->setText("Image " + imageName + " was deleted successfully from\n"
                                                          + m_srcDirPath);

        m_imageCounter--; // current index is the index of previous image

        if (m_imageCounter < 0){
            m_imageCounter = 0;
        }

        m_imagesList.removeOne(imageName);
        m_imagesListFiltered.removeOne(imageName);

        if (m_imagesList.empty()){ // in case the folder is empty due to moving all the images out of it
            QMessageBox::information(
                this,
                tr("Information"),
                tr("Note: no more images left in folder. \nChoose other folder to edit."));
            m_pathsScreenPtr->getNextButton()->setEnabled(false);
            m_pathsScreenPtr->getSrcTextEdit()->clear();
            m_pathsScreenPtr->getDstTextEdit()->clear();
            mainSortingBackButtonClicked(); // go back to the paths screen
            return;
        }

        // in this case, the m_imagesList should be updated so it will not include
        // the deleted image anymore, because as long as it includes it the app will try to
        // find the image to show it and would obviously fail in the mission.

        switchImage(imageSwitchEnum::Same);
        fillUndoStruct(imageName,m_srcDirPath, m_srcDirPath + "/sortingAppDeletedImages",undoAction::DeleteImageFromSrc);

        if (m_undoVector.size() < MAX_UNDO_ACTIONS) // support up to MAX_UNDO_ACTIONS last actions to avoid heap overflow
            m_undoVector.append(m_undoStruct);
        else {
            m_undoVector.pop_front(); // clear the first undo action stored in vector
            m_undoVector.append(m_undoStruct); // append the last action user made
        }
    }
    else {
        QPixmap icon(":/icons/X_NoBackground.png");
        m_mainSortingWindowPtr->getVxIconLabel()->setPixmap(icon.scaled(30,30,Qt::KeepAspectRatio));
        m_mainSortingWindowPtr->getVxTextLabel()->setText("Image could not be deleted!");
    }
}

// ---------------------findAvailableFolders(QString dirPath)-------------------------------------------
// Finds all sub folders of the main m_dstDirPath selected by user. updates the list in FoldersAvailableScrollArea

void Widget::findAvailableFolders()
{
    QDir dir(m_dstDirPath);

    QWidget* container = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(container);

    container->setLayout(layout);
    m_mainSortingWindowPtr->getFoldersAvailableScrollArea()->setWidget(container);
    m_mainSortingWindowPtr->getFoldersAvailableScrollArea()->setWidgetResizable(true);

    m_AvailableFoldersList = dir.entryList(QDir::NoDot | QDir::NoDotDot | QDir::Dirs);
    m_srcFolderCounter = m_AvailableFoldersList.size();

    // fill the scroll area with all sub-folders in main directory
    for (int i=0; i< m_AvailableFoldersList.size(); i++){
        qDebug() << m_AvailableFoldersList[i];
        QString tempString;

        if(i <= 9){ // add numbers to the first 10 folders' names in the list
            tempString = m_AvailableFoldersList[i] + QString(" -- ") + QString("<span style='color:red; font-weight:bold;'>%1</span>").arg(QString::number(i));
        }
        else if (i > 9 && i < 10+22) { // if i is between 10 and 31, add characters instead of numbers to the name of folder. 4 characters - c,d,m,r are taken for keyboard shortcut.
            char character = asciiToChar('A' + (i-10));
            tempString = m_AvailableFoldersList[i] + QString(" -- ") + QString("<span style='color:red; font-weight:bold;'>%1</span>").arg(character);
        }
        else { // we already have 36 different folders, next one will have no number nor character attached to it. that's life
            tempString = m_AvailableFoldersList[i];
        }

        ClickableLabel* temp = new ClickableLabel(tempString);
        m_AvailableFoldersPtrsVector.append(temp); // add the pointer to new folder label, for AvailableFolderLabelClickedWithCtrl method usage.
        temp->setFrameStyle(QFrame::Box | QFrame::Raised);
        temp->setMaximumSize(224, 50);
        layout->addWidget(temp);

        connect(temp,&ClickableLabel::clicked,
                [=](){AvailableFolderLabelClicked();}); // get the default value for cot = ClickOrTyped::MouseClick

        connect(temp,&ClickableLabel::keyPressSignal, this,&Widget::keyPressEvent);

        connect(temp,&ClickableLabel::clickedWithCtrl,
                [=](){AvailableFolderLabelClickedWithCtrl();});

    }
}

// ---------------------findContainingFolders(QString fileName, QString dirPath)-------------------------------------------
// Find all sub directories of m_dstDirPath which contain fileName. updates the list in CurrentlyInScrollArea

void Widget::findContainingFolders(QString fileName, QString dirPath)
{
    QDir dir(dirPath);
    QStringList dirList = dir.entryList(QDir::NoDot | QDir::NoDotDot | QDir::Dirs);


    QWidget* container = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(container);

    container->setLayout(layout);
    m_mainSortingWindowPtr->getCurrentlyInScrollArea()->setWidget(container);
    m_mainSortingWindowPtr->getCurrentlyInScrollArea()->setWidgetResizable(true);

    for (int i=0; i<dirList.size(); i++){

        QString subDirName = dirList[i];
        // Create a QDir object for the subdirectory
        QDir subDir(dir.absoluteFilePath(subDirName));

        // Check if the subdirectory contains the specified file
        if (subDir.exists(fileName)) {
            ClickableLabel* temp = new ClickableLabel(subDirName,this);
            connect(temp,&ClickableLabel::clicked,
                    [=](){CurrentlyInLabelClicked();});
            // QLabel* temp = new QLabel(subDirName,this);
            temp->setFrameStyle(QFrame::Box | QFrame::Raised);
            temp->setMaximumSize(224, 50);
            layout->addWidget(temp); // add the file to the contained files list
        }
    }

}

// ---------------------AvailableFolderLabelClicked()-------------------------------------------
// needs to be implemented for clicking the labels in the FoldersAvailableScrollArea
// when clicked, the image should be copied to the selected folder, and add the name of the
// folder to the list in Currently-in scroll area. a call for switchImage(imageSwitchEnum::Same) is recommended.

void Widget::AvailableFolderLabelClicked(ClickOrTyped cot){

    QString clickedFolder;

    if (cot == ClickOrTyped::MouseClick){ // this has to be done due to addition of numbers from 0-9 or letter A-Z (not including C, D, M, R which are used to keynoard shortcuts) to the names of folders.
        int index = ClickableLabel::s_chosenLabelPtr->text().indexOf(QRegularExpression(" -- "));
        if (index != -1)
            clickedFolder = ClickableLabel::s_chosenLabelPtr->text().mid(0,index);
        else { // meaning mouse click on a folder without a number between 0-9 or letter A-Z (not including C, D, M, R which are used to keynoard shortcuts)
            clickedFolder = ClickableLabel::s_chosenLabelPtr->text();
        }
    }
    else { // cot is an index between 0-9 or between A-Z (not including C, D, M, R which are used to keynoard shortcuts)
        clickedFolder = m_AvailableFoldersList[cot];
    }

    QString imageName = m_isFilteredImageList ? m_imagesListFiltered[m_imageCounter] : m_imagesList[m_imageCounter];

    QString src = m_srcDirPath + "/" + imageName;
    QString dst = m_dstDirPath + "/" + clickedFolder + "/" + imageName;

    if (m_mainSortingWindowPtr->m_buttonGroupPtr->checkedButton()->text() == "Copy Image"){

        if (QFile::copy(src,dst)){
            QPixmap icon(":/icons/V_NoBackground.png");
            m_mainSortingWindowPtr->getVxIconLabel()->setPixmap(icon.scaled(30,30,Qt::KeepAspectRatio));
            m_mainSortingWindowPtr->getVxTextLabel()->setText("Image " + imageName + " copied successfully from\n"
                                                              + m_srcDirPath + "\nto\n"
                                                              + m_dstDirPath + "/" + clickedFolder);

            fillUndoStruct(imageName,m_srcDirPath,m_dstDirPath + "/" + clickedFolder,undoAction::CopyImageFromSrc);
            if (m_undoVector.size() < MAX_UNDO_ACTIONS) // support up to MAX_UNDO_ACTIONS last actions to avoid heap overflow
                m_undoVector.append(m_undoStruct);
            else {
                m_undoVector.pop_front(); // clear the first undo action stored in vector
                m_undoVector.append(m_undoStruct); // append the last action user made
            }
        }

        else {
            QPixmap icon(":/icons/X_NoBackground.png");
            m_mainSortingWindowPtr->getVxIconLabel()->setPixmap(icon.scaled(30,30,Qt::KeepAspectRatio));
            m_mainSortingWindowPtr->getVxTextLabel()->setText("Image copy failed!");
        }

        findContainingFolders(imageName,m_dstDirPath); // this is necessary for updating the list of folders containing the image
    }

    else { //meaning "Move Image" is now checked
        QFile file(m_srcDirPath + "/" + imageName);
        // m_mediaPlayer->stop();
        // m_mediaPlayer->setSource(QUrl());
        if (clearMediaObjects()){
            hideAllVideoInterface();
        }
        if (file.rename(m_dstDirPath + "/" + clickedFolder + "/" + imageName)){
            QPixmap icon(":/icons/V_NoBackground.png");
            m_mainSortingWindowPtr->getVxIconLabel()->setPixmap(icon.scaled(30,30,Qt::KeepAspectRatio));
            m_mainSortingWindowPtr->getVxTextLabel()->setText("Image " + imageName + " moved successfully from\n"
                                                              + m_srcDirPath + "\nto\n"
                                                              + m_dstDirPath + "/" + clickedFolder);

            m_imageCounter--; // current index is the index of previous image

            if (m_imageCounter < 0){
                m_imageCounter = 0;
            }

            m_imagesList.removeOne(imageName);
            m_imagesListFiltered.removeOne(imageName);

            if (m_imagesList.empty()){ // in case the folder is empty due to moving all the images out of it
                QMessageBox::information(
                    this,
                    tr("Information"),
                    tr("Note: no more images left in folder. \nChoose other folder to edit."));
                m_pathsScreenPtr->getNextButton()->setEnabled(false);
                m_pathsScreenPtr->getSrcTextEdit()->clear();
                m_pathsScreenPtr->getDstTextEdit()->clear();
                m_pathsScreenPtr->getSrcImgCntTextEdit()->clear();
                m_pathsScreenPtr->getDstImgCntTextEdit()->clear();
                mainSortingBackButtonClicked(); // go back to the paths screen
                return;
            }
            switchImage(imageSwitchEnum::Same);

            fillUndoStruct(imageName,m_srcDirPath,m_dstDirPath + "/" + clickedFolder,undoAction::MoveImage);
            if (m_undoVector.size() < MAX_UNDO_ACTIONS) // support up to MAX_UNDO_ACTIONS last actions to avoid heap overflow
                m_undoVector.append(m_undoStruct);
            else {
                m_undoVector.pop_front(); // clear the first undo action stored in vector
                m_undoVector.append(m_undoStruct); // append the last action user made
            }

            // in this case, the m_imagesList should be updated so it will not include
            // the moved image anymore, because as long as it includes it the app will try to
            // find the image to show it and would obviously fail in the mission.
        }

        else {
            QPixmap icon(":/icons/X_NoBackground.png");
            m_mainSortingWindowPtr->getVxIconLabel()->setPixmap(icon.scaled(30,30,Qt::KeepAspectRatio));
            m_mainSortingWindowPtr->getVxTextLabel()->setText("Image move failed!");
        }
    }

}

// ---------------------AvailableFolderLabelClickedWithCtrl()-------------------------------------------
// needs to be implemented for clicking the labels with Ctrl key pressed
// when clicked, the selected folder should be promoted to the top of the Available Folders list and get the number 0.

void Widget::AvailableFolderLabelClickedWithCtrl()
{

    // find out what is the clicked label
    ClickableLabel* clickedFolderPtr;
    int i;
    for (i = 0; i < m_AvailableFoldersList.size(); i++){
        clickedFolderPtr = m_AvailableFoldersPtrsVector.at(i);
        if (clickedFolderPtr == ClickableLabel::s_chosenLabelPtr)
            break;
    }

    // if first folder on the list clicked, do nothing
    if (i == 0){
        return;
    }

    ClickableLabel tempClickableLabel(clickedFolderPtr->text());
    QString tempClickedFolder = m_AvailableFoldersList[i];

    // make the clicked folder go to top of the list, and down every other folders one place under their previous location in the list
    for (int j = i; j > 0 ; j--){
        m_AvailableFoldersList[j] = m_AvailableFoldersList[j-1];
        m_AvailableFoldersPtrsVector.at(j)->setText(m_AvailableFoldersPtrsVector.at(j-1)->text());
    }
    m_AvailableFoldersList[0] = tempClickedFolder;
    (m_AvailableFoldersPtrsVector.at(0))->setText(tempClickableLabel.text());



    // update  the scroll area with all sub-folders new numbers in main directory
    for (int k=0; k< m_AvailableFoldersList.size(); k++){
        qDebug() << m_AvailableFoldersList[k];
        QString tempString;

        if(k <= 9){ // add numbers to the first 10 folders' names in the list
            tempString = m_AvailableFoldersList[k] + QString(" -- ") + QString("<span style='color:red; font-weight:bold;'>%1</span>").arg(QString::number(k));
        }
        else if (k > 9 && k < 10+22) { // if i is between 10 and 31, add characters instead of numbers to the name of folder. 4 characters - c,d,m,r are taken for keyboard shortcut.
            char character = asciiToChar('A' + (k-10));
            tempString = m_AvailableFoldersList[k] + QString(" -- ") + QString("<span style='color:red; font-weight:bold;'>%1</span>").arg(character);
        }
        else { // we already have 36 different folders, next one will have no number nor character attached to it. that's life
            tempString = m_AvailableFoldersList[k];
        }
        (m_AvailableFoldersPtrsVector.at(k))->setText(tempString);
    }

    qDebug() << tempClickableLabel.text();
}


// ---------------------CurrentlyInLabelClicked()-------------------------------------------
// clicking a folder in Currently-In ScrollArea should remove the image being presented from the folder clicked on.

void Widget::CurrentlyInLabelClicked()
{
    QDir SrcDir(m_srcDirPath);

    QString clickedFolder = ClickableLabel::s_chosenLabelPtr->text();
    QDir removeFrom(m_dstDirPath + "/" + clickedFolder);

    QString imageName = m_isFilteredImageList ? m_imagesListFiltered[m_imageCounter] : m_imagesList[m_imageCounter];

    // removing the image from a folder in the destination folder, which is NOT the source folder
    if (clickedFolder != SrcDir.dirName()){

        if (removeFrom.remove(imageName)){ //removal was successful
            QPixmap icon(":/icons/V_NoBackground.png");
            m_mainSortingWindowPtr->getVxIconLabel()->setPixmap(icon.scaled(30,30,Qt::KeepAspectRatio));
            m_mainSortingWindowPtr->getVxTextLabel()->setText(imageName + "\nwas removed successfully from\n"
                                                              + m_dstDirPath + "/" + clickedFolder);

            ClickableLabel::s_chosenLabelPtr = nullptr; // this is important because after removing image,s_chosenLabelPtr
                                                        //will not hold a valid path to image so it won't be able to
                                                        // clear it in findContainingFolders images, causing the program to crash. this instruction will prevent it
        }

        findContainingFolders(imageName,m_dstDirPath);

        fillUndoStruct(imageName,m_srcDirPath,m_dstDirPath + "/" + clickedFolder,undoAction::DeleteImageFromDst);
        if (m_undoVector.size() < MAX_UNDO_ACTIONS) // support up to MAX_UNDO_ACTIONS last actions to avoid heap overflow
            m_undoVector.append(m_undoStruct);
        else {
            m_undoVector.pop_front(); // clear the first undo action stored in vector
            m_undoVector.append(m_undoStruct); // append the last action user made
        }
    }

    else { //clickedFolder is the same as the source folder. in this case the image should be removed from the source
           // folder and then it could not be presented again since it is no longer part of the dest folder.

        // if the current file is .mp4, we need to first stop it and clear its containing objects.
        // otherwise OS spots the file is being used, and we can't make any actions on him.
        if (clearMediaObjects()){
            hideAllVideoInterface();
        }

        QFile file(m_dstDirPath + "/" + clickedFolder + "/" + imageName);

        // same as deleteImage process, first pseudo delete the file by copying it to the deletedImages folder.
        // this allows to restore it if needed. After exiting the sorting screen the image will be deleted permanently.
        if (file.rename(m_srcDirPath + "/sortingAppDeletedImages/" + imageName)){

            ClickableLabel::s_chosenLabelPtr = nullptr; // this is important because after removing image,s_chosenLabelPtr
            //will not hold a valid path to image so it won't be able to
            // clear it in findContainingFolders images, causing the program to crash. this instruction will prevent it

            QPixmap icon(":/icons/V_NoBackground.png");
            m_mainSortingWindowPtr->getVxIconLabel()->setPixmap(icon.scaled(30,30,Qt::KeepAspectRatio));
            m_mainSortingWindowPtr->getVxTextLabel()->setText(imageName + "\nwas removed successfully from\n"
                                                              + m_dstDirPath + "/" + clickedFolder);

            m_imageCounter--; // current index is the index of previous image

            if (m_imageCounter < 0){
                m_imageCounter = 0;
            }

            m_imagesList.removeOne(imageName);
            m_imagesListFiltered.removeOne(imageName);

            if (m_imagesList.empty()){ // in case the folder is empty due to moving all the images out of it
                QMessageBox::information(
                    this,
                    tr("Information"),
                    tr("Note: no more images left in folder. \nChoose other folder to edit."));
                m_pathsScreenPtr->getNextButton()->setEnabled(false);
                m_pathsScreenPtr->getSrcTextEdit()->clear();
                m_pathsScreenPtr->getDstTextEdit()->clear();
                m_pathsScreenPtr->getSrcImgCntTextEdit()->clear();
                m_pathsScreenPtr->getDstImgCntTextEdit()->clear();
                mainSortingBackButtonClicked(); // go back to the paths screen
                return;
            }
            switchImage(imageSwitchEnum::Same);

            fillUndoStruct(imageName,m_srcDirPath,m_srcDirPath + "/sortingAppDeletedImages",undoAction::DeleteImageFromSrc);

            if (m_undoVector.size() < MAX_UNDO_ACTIONS) // support up to MAX_UNDO_ACTIONS last actions to avoid heap overflow
                m_undoVector.append(m_undoStruct);
            else {
                m_undoVector.pop_front(); // clear the first undo action stored in vector
                m_undoVector.append(m_undoStruct); // append the last action user made
            }

            // in this case, the m_imagesList should be updated so it will not include
            // the moved image anymore, because as long as it includes it the app will try to
            // find the image to show it and would obviously fail in the mission.
        }

        else {
            QPixmap icon(":/icons/X_NoBackground.png");
            m_mainSortingWindowPtr->getVxIconLabel()->setPixmap(icon.scaled(30,30,Qt::KeepAspectRatio));
            m_mainSortingWindowPtr->getVxTextLabel()->setText("Image remove failed!");
        }
    }


}

// ---------------------asciiToChar(const char c)-------------------------------------------
// returns a translation of ascii code into relevant character for adding to the folder's name in Available-in list
// this has to be done since there are 4 keys which are taken for keyboard shortcuts: C,D,M,R
char Widget::asciiToChar(const char c)
{
    switch(c){
        case 'C':
            return 'E';
            break;
        case 'D':
            return 'F';
            break;
        case 'M':
            return 'P';
            break;
        case 'R':
            return 'V';
            break;
        default:
            break;
    }

    if (c == 'A' || c == 'B'){
        return c;
    }
    else if (c >= 'E' && c <= 'J'){
        return c + 2;
    }
    else if (c >= 'K' && c <= 'N') {
        return c + 3;
    }
    else { // c >= 'S'
        return c + 4;
    }
}


// ---------------------asciiToChar(const char c)-------------------------------------------
// returns a translation of index value into relevant index of the folder's name in Available-Folders list
// this has to be done since there are 4 keys which are taken for keyboard shortcuts: C,D,M,R
int Widget::indexTranslation(const int index)
{

    if (index >=  ClickOrTyped::Key_A && index <=  ClickOrTyped::Key_B){
        return index;
    }
    else if (index >=  ClickOrTyped::Key_E + 2 && index <=  ClickOrTyped::Key_L + 2){
        return index - 2;
    }
    else if (index >=  ClickOrTyped::Key_N + 3 && index <=  ClickOrTyped::Key_Q + 3){
        return index - 3;
    }
    else {
        return index - 4;
    }
}


// ---------------------fillUndoStruct(QString name, QString src, QString dst, undoAction action)-------------------------
// fill the undo struct, for tracking and letting the user the option to undo the last action made
void Widget::fillUndoStruct(QString name, QString src, QString dst, undoAction action)
{
    m_undoStruct.imageName = name;
    m_undoStruct.srcFolder = src;
    m_undoStruct.dstFolder = dst;
    m_undoStruct.action = action;
    m_mainSortingWindowPtr->getUndoPushButton()->setVisible(true);
}



// ---------------------undoLastAction()-------------------------------------------
// undo last action made by user
void Widget::undoLastAction()
{
    // implement undo last action using m_undo struct of Widget class

    switch(m_undoStruct.action){

        case undoAction::CopyImageFromSrc:
        {
            // file was copied from src folder to dst folder. only thing has to be done
            // is to remove the copy of the file from the dst folder. done via "remove" method
            QFile file(m_undoStruct.dstFolder + "/" + m_undoStruct.imageName);
            if (file.remove()){
                QPixmap icon(":/icons/V_NoBackground.png");
                m_mainSortingWindowPtr->getVxIconLabel()->setPixmap(icon.scaled(30,30,Qt::KeepAspectRatio));
                m_mainSortingWindowPtr->getVxTextLabel()->setText("Image " + m_undoStruct.imageName + " removed successfully from\n"
                                                              + m_undoStruct.dstFolder);

                switchImage(imageSwitchEnum::Same);
            }
            break;
        }
        case undoAction::DeleteImageFromDst:
        {
            // file was deleted from currentlyIn list, meaning it has to return there without
            // changing anything else. this has to be done via "copy" method
            QFile file(m_undoStruct.srcFolder + "/" + m_undoStruct.imageName);
            if (file.copy(m_undoStruct.dstFolder + "/" + m_undoStruct.imageName)){
                QPixmap icon(":/icons/V_NoBackground.png");
                m_mainSortingWindowPtr->getVxIconLabel()->setPixmap(icon.scaled(30,30,Qt::KeepAspectRatio));
                m_mainSortingWindowPtr->getVxTextLabel()->setText("Image " + m_undoStruct.imageName + " copied successfully from\n"
                                                                  + m_undoStruct.srcFolder + "\nto\n"
                                                                  + m_undoStruct.dstFolder);

                switchImage(imageSwitchEnum::Same);
            }
            break;
        }
        case undoAction::DeleteImageFromSrc:
        {
            QFile file(m_undoStruct.dstFolder + "/" + m_undoStruct.imageName);
            if (file.rename(m_undoStruct.srcFolder + "/" + m_undoStruct.imageName)){
                QPixmap icon(":/icons/V_NoBackground.png");
                m_mainSortingWindowPtr->getVxIconLabel()->setPixmap(icon.scaled(30,30,Qt::KeepAspectRatio));
                m_mainSortingWindowPtr->getVxTextLabel()->setText("Image " + m_undoStruct.imageName + " restored successfully");

                // m_imageCounter++; // current index is the index of previous image
                m_imagesList.append(m_undoStruct.imageName);
                m_imagesListFiltered.append(m_undoStruct.imageName);

                switchImage(imageSwitchEnum::Same);
            }
            break;
        }
        case undoAction::MoveImage: // move image back to original source folder
        {
            QFile file(m_undoStruct.dstFolder + "/" + m_undoStruct.imageName);
            if (file.rename(m_undoStruct.srcFolder + "/" + m_undoStruct.imageName)){
                QPixmap icon(":/icons/V_NoBackground.png");
                m_mainSortingWindowPtr->getVxIconLabel()->setPixmap(icon.scaled(30,30,Qt::KeepAspectRatio));
                m_mainSortingWindowPtr->getVxTextLabel()->setText("Image " + m_undoStruct.imageName + " moved successfully from\n"
                                                                  + m_undoStruct.dstFolder + "\nto\n"
                                                                  + m_undoStruct.srcFolder);

                // m_imageCounter++; // current index is the index of previous image
                m_imagesList.append(m_undoStruct.imageName);
                m_imagesListFiltered.append(m_undoStruct.imageName);

                switchImage(imageSwitchEnum::Same);
            }
            break;
        }

        default:
            break;
    }

    m_undoVector.pop_back(); // delete the last element of the vector, which is the action that was undone now

    if (!m_undoVector.isEmpty()){
        m_undoStruct = m_undoVector.last(); // make the next undone action to be made to be the previous action made by user
    }
    else {
        m_mainSortingWindowPtr->getUndoPushButton()->setVisible(false); // when finish undoing, hide the undo pushbutton.
    }
}


// ---------------------setAllVideoInterface()-------------------------------------------
// sets all objects related to the video player control
void Widget::setAllVideoInterface()
{

    m_mainSortingWindowPtr->getVolumePushButton()->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
    m_mainSortingWindowPtr->getBackwardsPushButton()->setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));
    m_mainSortingWindowPtr->getForwardPushButton()->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));
    m_mainSortingWindowPtr->getPlayPausePushButton()->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    m_mainSortingWindowPtr->getStopPushButton()->setIcon(style()->standardIcon(QStyle::SP_MediaStop));

    hoveredObject* BackwardsPushButtonHover = new hoveredObject(this);
    BackwardsPushButtonHover->setHoveredText("-10s");
    m_mainSortingWindowPtr->getBackwardsPushButton()->installEventFilter(BackwardsPushButtonHover);

    hoveredObject* ForwardPushButtonHover = new hoveredObject(this);
    ForwardPushButtonHover->setHoveredText("+10s");
    m_mainSortingWindowPtr->getForwardPushButton()->installEventFilter(ForwardPushButtonHover);

    m_mainSortingWindowPtr->getVolumeHorizontalSlider()->setMinimum(0);
    m_mainSortingWindowPtr->getVolumeHorizontalSlider()->setMaximum(100);
    m_mainSortingWindowPtr->getVolumeHorizontalSlider()->setValue(10);

    connect(m_mainSortingWindowPtr->getBackwardsPushButton(), &QPushButton::clicked, this, &Widget::backwardsPushButtonClicked);
    connect(m_mainSortingWindowPtr->getForwardPushButton(), &QPushButton::clicked, this, &Widget::forwardPushButtonClicked);
    connect(m_mainSortingWindowPtr->getPlayPausePushButton(), &QPushButton::clicked, this, &Widget::playPausePushButtonClicked);
    connect(m_mainSortingWindowPtr->getStopPushButton(), &QPushButton::clicked, this, &Widget::stopPushButtonClicked);
    connect(m_mainSortingWindowPtr->getVolumePushButton(), &QPushButton::clicked, this, &Widget::volumePushButtonClicked);
    connect(m_mainSortingWindowPtr->getVolumeHorizontalSlider(), &QSlider::sliderMoved, this, &Widget::volumeHorizontalSliderValueChanged);
    connect(m_mainSortingWindowPtr->getDurationHorizontalSlider(), &QSlider::sliderMoved, this, &Widget::durationHorizontalSliderValueChanged);


    // m_mainSortingWindowPtr->getDurationHorizontalSlider()->setRange(0, m_mediaPlayer->duration() / 1000);

    hideAllVideoInterface();
}


// ---------------------durationChanged(qint64 duration)-------------------------------------------
// this slot is being executed whenever new video is being loaded to m_videoDuration
void Widget::durationChanged(qint64 duration)
{
    m_videoDuration = duration / 1000;
    m_mainSortingWindowPtr->getDurationHorizontalSlider()->setMaximum(m_videoDuration);
}

// ---------------------positionChanged(qint64 duration)-------------------------------------------
// this slot is being executed whenever the video changes it's position i.e at all times it plays or when user uses slider
void Widget::positionChanged(qint64 duration)
{
    if (!m_mainSortingWindowPtr->getDurationHorizontalSlider()->isSliderDown()) {
        m_mainSortingWindowPtr->getDurationHorizontalSlider()->setValue(duration / 1000);
    }
    updateDuration(duration / 1000); // calls update using only the nuber of seconds passed of video play. ms don't matter
}

// ---------------------updateDuration(qint64 duration)-------------------------------------------
// this slot is being executed whenever the video changes it's position i.e at all times it plays or when user uses slider
void Widget::updateDuration(qint64 duration)
{
    if (duration > 0 || m_videoDuration > 0) {

        QTime CurrentTime((duration / 3600) % 60, // hours
                          (duration / 60) % 60, // minutes
                          duration % 60); // seconds

        QTime TotalTime((m_videoDuration / 3600) % 60, // hours
                        (m_videoDuration / 60) % 60, // minutes
                         m_videoDuration % 60); // seconds

        QString timeFormat ="";
        if (m_videoDuration > 3600){
            timeFormat = "hh:mm:ss";
        }
        else {
            timeFormat = "mm:ss";
        }

        m_mainSortingWindowPtr->getCurrentTimeLabel()->setText(CurrentTime.toString(timeFormat)); // update cuurent time of video
        m_mainSortingWindowPtr->getTotalTimeLabel()->setText(TotalTime.toString(timeFormat)); // update total time of video
    }
}

// ---------------------hideAllVideoInterface()-------------------------------------------
// hides all video UI from the bottom of image label
void Widget::hideAllVideoInterface()
{
    m_mainSortingWindowPtr->getVolumePushButton()->hide();
    m_mainSortingWindowPtr->getBackwardsPushButton()->hide();
    m_mainSortingWindowPtr->getForwardPushButton()->hide();
    m_mainSortingWindowPtr->getPlayPausePushButton()->hide();
    m_mainSortingWindowPtr->getStopPushButton()->hide();
    m_mainSortingWindowPtr->getVolumeHorizontalSlider()->hide();
    m_mainSortingWindowPtr->getDurationHorizontalSlider()->hide();
    m_mainSortingWindowPtr->getTotalTimeLabel()->hide();
    m_mainSortingWindowPtr->getCurrentTimeLabel()->hide();
}

// ---------------------showAllVideoInterface()-------------------------------------------
// shows all video UI in bottom of image label
void Widget::showAllVideoInterface()
{
    m_mainSortingWindowPtr->getVolumePushButton()->show();
    m_mainSortingWindowPtr->getBackwardsPushButton()->show();
    m_mainSortingWindowPtr->getForwardPushButton()->show();
    m_mainSortingWindowPtr->getPlayPausePushButton()->show();
    m_mainSortingWindowPtr->getStopPushButton()->show();
    m_mainSortingWindowPtr->getVolumeHorizontalSlider()->show();
    m_mainSortingWindowPtr->getDurationHorizontalSlider()->show();
    m_mainSortingWindowPtr->getTotalTimeLabel()->show();
    m_mainSortingWindowPtr->getCurrentTimeLabel()->show();
}


// ---------------------volumePushButtonClicked()-------------------------------------------
void Widget::volumePushButtonClicked()
{
    if (m_isMuted == false)
    {
        m_isMuted = true;
        m_mainSortingWindowPtr->getVolumePushButton()->setIcon(style()->standardIcon(QStyle::SP_MediaVolumeMuted));
        m_audioOutput->setMuted(true);
    }
    else
    {
        m_isMuted = false;
        m_mainSortingWindowPtr->getVolumePushButton()->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
        m_audioOutput->setMuted(false);
    }
}


// ---------------------volumeHorizontalSliderValueChanged(int value)-------------------------------------------
void Widget::volumeHorizontalSliderValueChanged(int value)
{
    float realVolume = (float)value/((m_mainSortingWindowPtr->getVolumeHorizontalSlider()->maximum())*1.0);
    m_audioOutput->setVolume(realVolume);
}



// ---------------------durationHorizontalSliderValueChanged(int value)-------------------------------------------
void Widget::durationHorizontalSliderValueChanged(int value)
{
    m_mainSortingWindowPtr->getDurationHorizontalSlider()->setValue(value); // advance duration bar by 10 seconds
    m_mediaPlayer->setPosition(m_mainSortingWindowPtr->getDurationHorizontalSlider()->value() * 1000); // position is in ms, multiply by 1000 to advance video in seconds
}


// ---------------------stopPushButtonClicked()-------------------------------------------
void Widget::stopPushButtonClicked()
{
    m_mediaPlayer->stop();
    m_isPaused = true;
    m_mainSortingWindowPtr->getPlayPausePushButton()->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
}



// ---------------------forwardPushButtonClicked()-------------------------------------------
void Widget::forwardPushButtonClicked()
{
    m_mainSortingWindowPtr->getDurationHorizontalSlider()->setValue(m_mainSortingWindowPtr->getDurationHorizontalSlider()->value() + 10); // advance duration bar by 10 seconds
    m_mediaPlayer->setPosition(m_mainSortingWindowPtr->getDurationHorizontalSlider()->value() * 1000); // position is in ms, multiply by 1000 to advance video in seconds
}



// ---------------------backwardsPushButtonClicked()-------------------------------------------
void Widget::backwardsPushButtonClicked()
{
    m_mainSortingWindowPtr->getDurationHorizontalSlider()->setValue(m_mainSortingWindowPtr->getDurationHorizontalSlider()->value() - 10); // decrease duration bar by 10 seconds
    m_mediaPlayer->setPosition(m_mainSortingWindowPtr->getDurationHorizontalSlider()->value() * 1000); // position is in ms, multiply by 1000 to advance video in seconds
}


// ---------------------playPausePushButtonClicked()-------------------------------------------
void Widget::playPausePushButtonClicked()
{
    if (m_isPaused == true)
    {
        m_isPaused = false;
        m_mediaPlayer->play();
        m_mainSortingWindowPtr->getPlayPausePushButton()->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    }
    else
    {
        m_isPaused = true;
        m_mediaPlayer->pause();
        m_mainSortingWindowPtr->getPlayPausePushButton()->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    }
}


// ---------------------loadNewVideo()-------------------------------------------
// load new video to the relevant multimedia objects and display it on label
void Widget::loadNewVideo(const QString& videoName){
    m_mediaPlayer = new QMediaPlayer(this);
    m_audioOutput = new QAudioOutput(this);
    m_mediaPlayer->setAudioOutput(m_audioOutput);

    m_videoWidget = new QVideoWidget(m_mainSortingWindowPtr->getImageLabel());
    m_videoWidget->setGeometry(5, 5, m_mainSortingWindowPtr->getImageLabel()->width() - 10, m_mainSortingWindowPtr->getImageLabel()->height() - 10);
    m_videoWidget->setParent(m_mainSortingWindowPtr->getImageLabel());

    m_mediaPlayer->setVideoOutput(m_videoWidget);
    m_mediaPlayer->setSource(QUrl(videoName));
    m_videoWidget->setVisible(true);
    m_videoWidget->show();
    m_audioOutput->setMuted(false);

    m_isPaused = false;
    m_mediaPlayer->play();
    m_mainSortingWindowPtr->getPlayPausePushButton()->setIcon(style()->standardIcon(QStyle::SP_MediaPause));

    m_mainSortingWindowPtr->getVolumeHorizontalSlider()->setValue(0);
    m_audioOutput->setVolume(0.0); // start video play muted

    connect(m_mediaPlayer, &QMediaPlayer::durationChanged, this, &Widget::durationChanged);
    connect(m_mediaPlayer, &QMediaPlayer::positionChanged, this, &Widget::positionChanged);
}


// ---------------------clearMediaObjects()-------------------------------------------
// deletes all media object creaated to display video on image label
bool Widget::clearMediaObjects(){
    if (m_mediaPlayer){
        delete m_mediaPlayer; // delete last object for preventing memory leak
        m_mediaPlayer = nullptr;

        if (m_videoWidget){
            delete m_videoWidget; // delete last object for preventing memory leak
            m_videoWidget = nullptr;

            if (m_audioOutput){
                delete m_audioOutput; // delete last object for preventing memory leak
                m_audioOutput = nullptr;
                return true;
            }
        }
    }

    return false; // if no media objects currently alive
}


// ---------------------libRawToQImage()-------------------------------------------
// Function to convert LibRaw image to QImage
QImage Widget::libRawToQImage(const QString imagePath) {

    // Initialize LibRaw
    LibRaw rawProcessor;

    QString tempPath;

    // Load the NEF file
    if (rawProcessor.open_file(imagePath.toUtf8().constData()) != LIBRAW_SUCCESS) {
        qWarning() << "Failed to open NEF file";
        qWarning() << rawProcessor.open_file(imagePath.toUtf8().constData());

        // since LibRaw object can't read paths with non-english names, a small behind
        // the scenes adjustment is taking place. The original NEF image is moved to
        // a path which is readable for LibRaw, then after reading and transforming it into
        // QImage object it is returned to the original location.
        QFile nefFile(imagePath);
        tempPath = QDir::homePath() + "/temp.NEF";
        if (!nefFile.rename(tempPath)){ // if image could not be copied - abort
            return QImage();
        }
        if (rawProcessor.open_file(tempPath.toUtf8().constData()) != LIBRAW_SUCCESS){ // if image could not be opened - abort
            qWarning() << "Failed to open NEF file";
            qWarning() << rawProcessor.open_file(imagePath.toUtf8().constData());
            return QImage();
        }
    }

    // Process the image
    if (rawProcessor.unpack() != LIBRAW_SUCCESS || rawProcessor.dcraw_process() != LIBRAW_SUCCESS) {
        qWarning() << "Failed to process NEF file";
        return QImage();
    }

    // Get the processed image data
    const libraw_processed_image_t *image = rawProcessor.dcraw_make_mem_image();

    if (!image) {
        qWarning() << "Failed to get image data from LibRaw";
        return QImage();
    }

    // Convert to QImage
    QImage qImage(image->data, image->width, image->height, image->width * 3, QImage::Format_RGB888);

    // return the situation beck to normal if necessary
    if (!tempPath.isEmpty()){
        rawProcessor.recycle(); // release all resources from image
        QFile copiedFile(tempPath);
        copiedFile.rename(imagePath); // move back to original folder
    }

    if (qImage.isNull()) {
        qWarning() << "Failed to convert image to QImage";
        return QImage();
    }

    return qImage.copy();  // Return a copy to avoid memory issues
}


// ---------------------eventFilter(QObject *watched, QEvent *event)-------------------------------------------
// Handles clicks over imageLabel, so it would activate start/pause when displaying a video
bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        QStringList localImageList = m_mainSortingWindowPtr->getFilterTextEdit()->toPlainText().isEmpty() ? m_imagesList : m_imagesListFiltered;
        QFileInfo fileInfo(m_srcDirPath + QString("/") + localImageList[m_imageCounter]);
        if (fileInfo.suffix() == "mp4" || fileInfo.suffix() == "MP4"){
            playPausePushButtonClicked();
        }
        return true;
    }
    return false; // Event was not handled
}
