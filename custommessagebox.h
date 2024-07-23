#ifndef CUSTOMMESSAGEBOX_H
#define CUSTOMMESSAGEBOX_H

#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QSettings>
#include <QCheckBox>

class CustomMessageBox : public QWidget
{
    Q_OBJECT
public:
    explicit CustomMessageBox(QWidget *parent = nullptr);
    bool dontAskAgain {false};
    QMessageBox::StandardButton userChoiceOfDeletion;

private:
    QPushButton *deleteButton;
    QCheckBox *dontAskAgainCheckBox;

    void showMessageBox();

public slots:
    void deleteButtonClicked();

signals:
};

#endif // CUSTOMMESSAGEBOX_H
