#include "pathsscreen.h"
#include "ui_pathsscreen.h"

pathsScreen::pathsScreen(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::pathsScreen)
{
    ui->setupUi(this);
}

pathsScreen::~pathsScreen()
{
    delete ui;
}

// getters section

QPushButton* pathsScreen::getDestinationButton()
{
    return ui->destinationButton;
}

QPushButton* pathsScreen::getSourceButton()
{
    return ui->sourceButton;
}

QPushButton* pathsScreen::getNextButton()
{
    return ui->nextButton;
}

QPushButton* pathsScreen::getBackButton()
{
    return ui->backButton;
}

QPushButton* pathsScreen::getExitButton()
{
    return ui->exitButton;
}

QTextEdit* pathsScreen::getDstTextEdit()
{
    return ui->destinationTextEdit;
}

QTextEdit* pathsScreen::getSrcTextEdit()
{
    return ui->sourceTextEdit;
}

QTextEdit *pathsScreen::getSrcImgCntTextEdit()
{
    return ui->sourceImagesCountTextEdit;
}

QTextEdit *pathsScreen::getDstImgCntTextEdit()
{
    return ui->destinationImagesCountTextEdit;
}
