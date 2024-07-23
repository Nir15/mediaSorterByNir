#ifndef HOVEREDOBJECT_H
#define HOVEREDOBJECT_H

#include <QObject>
#include <QEvent>
#include <QWidget>
#include <QToolTip>
#include <QString>

class hoveredObject : public QObject
{
    Q_OBJECT

private:
    QString m_hoveredText;
public:
    explicit hoveredObject(QObject *parent = nullptr);
    void setHoveredText(QString text);

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
};

#endif // HOVEREDOBJECT_H
