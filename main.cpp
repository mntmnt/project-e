#include <QApplication>

#include "my_timer.h"

#include <QSystemTrayIcon>
#include <QIcon>
#include <QMenu>

#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setQuitOnLastWindowClosed(false);

    QLabel label;
    label.setText(QObject::tr("ProjectEKA"));
    label.show();

    MyTimer * t = new MyTimer(&label);
    t->stop();

    QIcon icon(":/pics/ghost.png");
    QSystemTrayIcon tray_icon(icon);
    QMenu menu(QObject::tr("ProjectCE"));

    {
        auto act = menu.addAction(QObject::tr("Start"));
        QObject::connect(act, SIGNAL(triggered()), t, SLOT(start()));
        QObject::connect(act, &QAction::triggered,[&tray_icon](){
            tray_icon.setIcon(QIcon(":/pics/pumpkin.png"));
        });

        act = menu.addAction(QObject::tr("Stop"));
        QObject::connect(act, SIGNAL(triggered()), t, SLOT(stop()));
        QObject::connect(act, &QAction::triggered, [&tray_icon]() {
            tray_icon.setIcon(QIcon(":/pics/ghost.png"));
        });

        menu.addSeparator();

        act = menu.addAction(QObject::tr("Quit"));
        QObject::connect(act, SIGNAL(triggered()), qApp, SLOT(quit()));
    }

    tray_icon.setContextMenu(&menu);
    tray_icon.show();


    return a.exec();
}
