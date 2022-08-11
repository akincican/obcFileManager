#ifndef CAN_H
#define CAN_H

#include <QDeclarativeItem>
#include <QMainWindow>
#include <QObject>
#include <QQuickItem>
#include <QSharedDataPointer>
#include <QWidget>

class CanData;

class Can
{
    Q_OBJECT
public:
    Can();
    Can(const Can &);
    Can &operator=(const Can &);
    ~Can();

private:
    QSharedDataPointer<CanData> data;
};

#endif // CAN_H
