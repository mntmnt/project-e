#pragma once

#include <QLabel>
#include <QMovie>
#include <QBitmap>
#include <QRegion>

class FunnyWin : public QLabel {
    Q_OBJECT
    QMovie mov;

public:

    FunnyWin():
        QLabel(0, Qt::FramelessWindowHint | Qt::WindowSystemMenuHint),
        mov(":/pics/animated_flying_super_penguin.gif")  {
        connect(&mov, SIGNAL(frameChanged(int)), this, SLOT(onFrameChanged(int)));
    }

public slots:

    void show() {
        mov.start();
        QWidget::show();
    }

    void hide() {
        mov.stop();
        QWidget::hide();
    }

private slots:

    void onFrameChanged(int i) {
        auto curimg = mov.currentPixmap();

        resize(curimg.size());

        setPixmap(curimg);
        setMask(curimg.mask());
    }

};
