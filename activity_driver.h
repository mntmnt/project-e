#pragma once

#include <QTimer>

#include "win_predefs.h"

class ActivityDriver: public QObject {

Q_OBJECT

   QTimer timer;

   bool activated;

   bool isActive() const {
       return activated;
   }

private slots:

   void OnShot() {
       sendKeyStrokes();
   }

public:
   ActivityDriver():activated(false) {
        timer.setInterval(1000);
        timer.stop();
        connect(&timer, SIGNAL(timeout()), this, SLOT(OnShot()));
    }

public slots:


    void start() {
        if(isActive()) return;

        timer.start();
        activated = true;

        emit notifyActivated();
    }

    void stop() {
        if(!isActive()) return;

        timer.stop();

        activated = false;

        emit notifyStopped();
    }

signals:

    void notifyActivated();
    void notifyStopped();
};

