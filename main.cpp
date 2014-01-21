#include <QApplication>

#include "my_timer.h"

#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QLabel label;
    label.setText("ProjectEKA");
    label.show();

    MyTimer * t = new MyTimer(&label);
    t->start();


    return a.exec();
}
