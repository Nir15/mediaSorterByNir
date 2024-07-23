#ifndef STARTUPSCREEN_H
#define STARTUPSCREEN_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class startupScreen;
}

class startupScreen : public QWidget
{
    Q_OBJECT

public:
    explicit startupScreen(QWidget *parent = nullptr);
    ~startupScreen();
    QPushButton* getStartSortingButton();
private:
    Ui::startupScreen *ui;

private slots:

};

#endif // STARTUPSCREEN_H
