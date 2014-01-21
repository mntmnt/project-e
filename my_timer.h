#ifndef MY_TIMER_H
#define MY_TIMER_H


#include <QLabel>

#include <QTimer>

void sendKeyStrokes();

class MyTimer : public QTimer {

Q_OBJECT

   QLabel * prntLabel;
   int counter;
public:
    MyTimer(QLabel * prnt):QTimer(prnt),prntLabel(prnt) {
        setInterval(1000);
        counter = 0;
        connect(this, SIGNAL(timeout()), this, SLOT(OnShot()));
    }

public slots:

    void OnShot() {
        counter ++;
        sendKeyStrokes();
        prntLabel->setText(QString("ProjectEKA => ") + QString::number(counter));
    }
};

#endif // MY_TIMER_H
