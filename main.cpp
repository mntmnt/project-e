#include <QApplication>

#include "activity_driver.h"

#include "tray_icon.h"
#include <QMessageBox>

#include "last-real-activity-catcher.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(resources);

    QApplication a(argc, argv);

    if(TrayIcon::isAvailable()) {
        QApplication::setQuitOnLastWindowClosed(false);

        ActivityDriver driver;
        driver.stop();
        auto tmr = &driver;

        TrayIcon trayico;

        QObject::connect(&trayico, SIGNAL(start()), tmr, SLOT(start()));
        QObject::connect(&trayico, SIGNAL(stop()), tmr, SLOT(stop()));

        QObject::connect(tmr, SIGNAL(notifyActivated()), &trayico, SLOT(onStart()));
        QObject::connect(tmr, SIGNAL(notifyStopped()), &trayico, SLOT(onStop()));

        QObject::connect(&trayico, SIGNAL(quit()), qApp, SLOT(quit()));

        trayico.show();

        VirtualWidget input_catcher;
        input_catcher.activate();

        QTimer tmr2;
        QObject::connect(&tmr2, &QTimer::timeout, [&input_catcher]() {
            qDebug() << "Inactively " << input_catcher.getInactiveTimeMs() << " ms";
        });
        tmr2.start(5000);

        return a.exec();
    } else {
        QMessageBox::critical(0, "No-Systray", "No system tray available");
        return 1;
    }
}
