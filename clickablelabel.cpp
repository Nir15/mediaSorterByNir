#include "clickablelabel.h"


ClickableLabel* ClickableLabel::s_chosenLabelPtr = nullptr;

ClickableLabel::ClickableLabel(const QString &text, QWidget* parent, Qt::WindowFlags f)
    : QLabel(text, parent) {

    setFocusPolicy(Qt::StrongFocus); // for capturing keypresses when this label is shown and "focused" (when clicked on, in our case)
}

ClickableLabel::~ClickableLabel() {}

void ClickableLabel::clearClickedLabel()
{
    if (s_chosenLabelPtr){
        QPalette palette = s_chosenLabelPtr->palette();
        palette.setColor(QPalette::Window, Qt::white);
        s_chosenLabelPtr->setAutoFillBackground(true);
        s_chosenLabelPtr->setPalette(palette);
    }
}

void ClickableLabel::mousePressEvent(QMouseEvent* event)
{
    if (!(event->modifiers() & Qt::ControlModifier)){ // mouse press over a label, WITHOUT holding Ctrl key
        // reset colors of last label clicked
        if (s_chosenLabelPtr){
            QPalette palette = s_chosenLabelPtr->palette();
            palette.setColor(QPalette::Window, Qt::white);
            s_chosenLabelPtr->setAutoFillBackground(true);
            s_chosenLabelPtr->setPalette(palette);
        }
        s_chosenLabelPtr = this; // set the pointer to the current label clicked

        QPalette palette = s_chosenLabelPtr->palette();
        palette.setColor(QPalette::Window, Qt::gray);
        s_chosenLabelPtr->setAutoFillBackground(true);
        s_chosenLabelPtr->setPalette(palette);
        // s_chosenLabelPtr->setStyleSheet("QLabel { background-color: rgb(190,190,190) }"); // color is kind of grey
        emit clicked();
    }

    else { // mouse press over a label, WITH holding Ctrl key
        s_chosenLabelPtr = this; // set the pointer to the current label clicked
        emit clickedWithCtrl();
    }
}


// activate the functions which are responsible for everything that keyboard press do
void ClickableLabel::keyPressEvent(QKeyEvent *event)
{
    emit keyPressSignal(event);
}
