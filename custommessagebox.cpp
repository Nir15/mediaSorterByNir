#include "custommessagebox.h"
#include <QVBoxLayout>
#include <QHBoxLayout>


CustomMessageBox::CustomMessageBox(QWidget *parent)
    : QWidget(parent)
{

}

void CustomMessageBox::deleteButtonClicked()
{
    if (dontAskAgain) {
        return;
    }

    showMessageBox();
}


void CustomMessageBox::showMessageBox()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Delete File");
    msgBox.setText("Are you sure you want to delete the file?");
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    QCheckBox checkBox("Don't ask me again");
    msgBox.setCheckBox(&checkBox);

    int ret = msgBox.exec();

    if (checkBox.isChecked()) {
        dontAskAgain = true;
    }

    switch (ret) {
        case QMessageBox::Yes:
            qDebug() << "File deleted";
            userChoiceOfDeletion = QMessageBox::Yes;
            break;
        case QMessageBox::No:
            qDebug() << "File not deleted";
            userChoiceOfDeletion = QMessageBox::No;
            break;
        default:
            userChoiceOfDeletion = QMessageBox::No;
            break;
    }
}
