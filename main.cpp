#include <QApplication>

#include "activity_driver.h"

#include "tray_icon.h"
#include <QMessageBox>

#include "virtual-widget.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(resources);

    QApplication a(argc, argv);

    if(TrayIcon::isAvailable()) {
        QApplication::setQuitOnLastWindowClosed(false);

        ActivityDriver driver;
        driver.stop();

        TrayIcon trayico;

        QObject::connect(&trayico, SIGNAL(start()), &driver, SLOT(start()));
        QObject::connect(&trayico, SIGNAL(stop()), &driver, SLOT(stop()));

        QObject::connect(&driver, SIGNAL(notifyActivated()), &trayico, SLOT(onStart()));
        QObject::connect(&driver, SIGNAL(notifyStopped()), &trayico, SLOT(onStop()));

        QObject::connect(&trayico, SIGNAL(quit()), qApp, SLOT(quit()));

        trayico.show();

        VirtualWidget input_catcher;
        input_catcher.activate();

        QObject::connect(&input_catcher, SIGNAL(realInput()), &driver, SLOT(stop()));

        QTimer tmr2;
        QObject::connect(&tmr2, &QTimer::timeout, [&input_catcher, &driver]() {
            if(input_catcher.getInactiveTimeMs() > 10000) {
               driver.start();
            }
        });
        tmr2.start(5000);

        return a.exec();
    } else {
        QMessageBox::critical(0, "No-Systray", "No system tray available");
        return 1;
    }
}
