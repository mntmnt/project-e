#ifndef ACTIVITY_DRIVER_H
#define ACTIVITY_DRIVER_H


#include <QLabel>

#include <QTimer>

void sendKeyStrokes();

class ActivityDriver : public QTimer {

Q_OBJECT

   int counter;
public:
    ActivityDriver() {
        setInterval(1000);
        stop();
        connect(this, SIGNAL(timeout()), this, SLOT(OnShot()));
    }

public slots:

    void OnShot() {
        sendKeyStrokes();
        emit shot();
    }

signals:
    void shot();
};

#endif // ACTIVITY_DRIVER_H
