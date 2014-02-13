#pragma once

#include <QWidget>

#include "win_predefs.h"


class VirtualWidget : public QWidget {
    Q_OBJECT

public:

    VirtualWidget(): last_input_tick(getCurrentMilliseconds()) {
        hide();
    }

    void activate() {
        hide();
        registerOnRawInput();
    }

    std::size_t getInactiveTimeMs() {
        return getCurrentMilliseconds() - last_input_tick;
    }

private:

    std::size_t last_input_tick;

    typedef QByteArray NativeEventType;

    //See QAbstractNativeEventFilter
    bool nativeEvent(const NativeEventType & e, void * message, long * result)
    {
       return processRawInput(e, message, result);
    }

    void registerOnRawInput() {
        registerRawInputFor(this->winId());
    }

    bool processRawInput(const NativeEventType & e, void * message, long * result) {
        return processRawInputFor(e, message, result, [this]() {
            last_input_tick = getCurrentMilliseconds();
            emit realInput();
        });
    }

signals:

    void realInput();

};
