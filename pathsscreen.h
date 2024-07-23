#ifndef PATHSSCREEN_H
#define PATHSSCREEN_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
namespace Ui {
class pathsScreen;
}

class pathsScreen : public QWidget
{
    Q_OBJECT

public:
    explicit pathsScreen(QWidget *parent = nullptr);
    ~pathsScreen();

    QPushButton* getDestinationButton();
    QPushButton* getSourceButton();
    QPushButton* getNextButton();
    QPushButton* getBackButton();
    QPushButton* getExitButton();
    QTextEdit* getDstTextEdit();
    QTextEdit* getSrcTextEdit();
    QTextEdit* getSrcImgCntTextEdit();
    QTextEdit* getDstImgCntTextEdit();

private:
    Ui::pathsScreen *ui;
};

#endif // PATHSSCREEN_H
