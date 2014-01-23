#include <QApplication>

#include "my_timer.h"

#include "tray_icon.h"
#include <QMessageBox>
int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(resources);

    QApplication a(argc, argv);

    if(TrayIcon::isAvailable()) {
        QApplication::setQuitOnLastWindowClosed(false);

        QLabel label;
        label.setText(QObject::tr("ProjectEKA"));
        label.show();

        MyTimer * tmr = new MyTimer(&label);
        tmr->stop();

        TrayIcon trayico;

        QObject::connect(&trayico, SIGNAL(start()), tmr, SLOT(start()));
        QObject::connect(&trayico, SIGNAL(stop()), tmr, SLOT(stop()));
        QObject::connect(&trayico, SIGNAL(quit()), qApp, SLOT(quit()));

        trayico.show();
        return a.exec();
    } else {
        QMessageBox::critical(0, "No-Systray", "No system tray available");
        return 1;
    }
}
