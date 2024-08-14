#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>
#include <QWidget>
#include <Qt>
#include <QKeyEvent>


class ClickableLabel : public QLabel {
    Q_OBJECT

public:
    explicit ClickableLabel(const QString &text, QWidget *parent=nullptr, Qt::WindowFlags f=Qt::WindowFlags());
    ~ClickableLabel();
    static ClickableLabel* s_chosenLabelPtr;
    void clearClickedLabel();

signals:
    void clicked();
    void clickedWithCtrl();
    void clickedImageLabel();
    void keyPressSignal(QKeyEvent* event);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent* event) override;

};

#endif // CLICKABLELABEL_H
