#ifndef ACTIVITY_DRIVER_H
#define ACTIVITY_DRIVER_H


#include <QLabel>
#include <QTimer>

#include <QDebug>

void sendKeyStrokes();
QString GetForegroundWindowTitle();
std::size_t IdleTime();

class ActivityDriver: public QObject {

Q_OBJECT

   QString title;

   QTimer timer;
   QTimer update_last_activity;

   bool activated;

   QLabel label;

   bool isActive() const {
       return activated;
   }

   std::size_t last_activity;

private slots:

   void grabActiveWinTitle() {
       title = GetForegroundWindowTitle();

       last_activity = IdleTime();

       label.setText("<b><font color=red>" + title + "</font></b>&nbsp; --" + QString::number(last_activity ));
   }

   void OnShot() {
       sendKeyStrokes();
   }

public:
   ActivityDriver():activated(false), last_activity(0u) {
        timer.setInterval(1000);
        timer.stop();
        connect(&timer, SIGNAL(timeout()), this, SLOT(OnShot()));

        update_last_activity.setInterval(10000);
        update_last_activity.start();

        connect(&update_last_activity, &QTimer::timeout, [this](){
            grabActiveWinTitle();
        });

        label.resize(100, 50);
        label.hide();
    }

public slots:


    void start() {
        if(isActive()) return;

        QTimer::singleShot(3000, this, SLOT(grabActiveWinTitle()));
        label.show();

        timer.start();
        activated = true;

        emit notifyActivated();
    }

    void stop() {
        if(!isActive()) return;

        label.hide();

        timer.stop();

        activated = false;

        emit notifyStopped();
    }

signals:

    void notifyActivated();
    void notifyStopped();
};

#endif // ACTIVITY_DRIVER_H
