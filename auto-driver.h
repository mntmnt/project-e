#pragma once

#include <QTimer>
#include <QWidget>

#include "win_predefs.h"

class AutoModeDriver : public QObject {
    Q_OBJECT

    QWidget imitation;
    bool active;

    void goImitation() {
        if(isDesktopWindow()) {
            emit started();
        } else {
            auto name = GetForegroundWindowTitle();
            imitation.show();
            imitation.setWindowTitle(name);

            emit started();
        }
    }

    void stopImitation() {
        imitation.hide();

        emit stopped();
    }

public:
    AutoModeDriver() {
        active = false;
        imitation.resize(200, 200);
        imitation.hide();
    }

public slots:

    void enable() {
        if(active) return;

        active = true;
        emit activated();
    }

    void disable() {
        if(!active) return;

        active = false;
        emit deactivated();
    }

    void reverse() {
        if(active) disable();
        else enable();
    }

    void stop() {
        stopImitation();

        emit stopped();
    }

    void checkInactiveTime(std::size_t ms) {
        if(ms > 10000) {
            goImitation();
        }
    }

signals:

    void deactivated();
    void activated();

    void started();
    void stopped();

};
