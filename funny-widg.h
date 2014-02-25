#pragma once

#include <QLabel>
#include <QMovie>
#include <QBitmap>
#include <QRegion>

#include "win_predefs.h"

class FunnyWin : public QLabel {
    Q_OBJECT
    QMovie mov;

public:

    FunnyWin():
        QLabel(0, Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint),
        mov(":/pics/animated_flying_super_penguin.gif")  {
        connect(&mov, SIGNAL(frameChanged(int)), this, SLOT(onFrameChanged(int)));
    }

public slots:

    void show() {
        if(isActiveWindow()) return;
        setWindowTitle(GetForegroundWindowTitle());
        mov.start();
        QLabel::show();
    }

    void hide() {
        if(!isActiveWindow()) return;
        mov.stop();
        QLabel::hide();
    }

private slots:

    void onFrameChanged(int i) {
        auto curimg = mov.currentPixmap();

        resize(curimg.size());

        setPixmap(curimg);
        setMask(curimg.mask());

    }

};

#include <QtWinExtras>

class ImitationWin : public QLabel {
    Q_OBJECT

public:

    ImitationWin():
        QLabel(0, Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowStaysOnBottomHint |  Qt::Tool) {

//        if (QtWin::isCompositionEnabled()) {
//                QtWin::extendFrameIntoClientArea(this, -1, -1, -1, -1);
//                setAttribute(Qt::WA_TranslucentBackground, true);
//                setAttribute(Qt::WA_NoSystemBackground, false);
//                setStyleSheet("Widget { background: transparent; }");
//        }
    }

public slots:

    void show() {
        if(isActiveWindow()) return;
        setWindowTitle(GetForegroundWindowTitle());
        auto rect = GetForegroundWindowSize();
        resize(rect.size());
        move(rect.x(), rect.y());
        setWindowOpacity(50.0/100.0);
        QWidget::show();
    }

    void hide() {
        if(!isActiveWindow()) return;
        QWidget::hide();
    }

};
