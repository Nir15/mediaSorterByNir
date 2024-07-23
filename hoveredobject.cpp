#include "hoveredobject.h"

hoveredObject::hoveredObject(QObject *parent)
    : QObject{parent}, m_hoveredText{"Object explanation"}
{}

void hoveredObject::setHoveredText(const QString text)
{
    m_hoveredText = text;
}




bool hoveredObject::eventFilter(QObject *watched, QEvent *event)
{
    // Check if the event is a QEvent::Enter, meaning object is hovered
    if (event->type() == QEvent::Enter) {
        // Cast the watched object to a QWidget
        QWidget *widget = qobject_cast<QWidget*>(watched);
        if (widget) {
            // Show a tooltip at the widget's position
            QToolTip::showText(widget->mapToGlobal(QPoint(0, widget->height())), m_hoveredText, widget);
        }
    }
    // Pass the event to the base class implementation
    return QObject::eventFilter(watched, event);
}
