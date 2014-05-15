#include <QApplication>

#include "activity_driver.h"

#include "tray_icon.h"
#include <QMessageBox>

#include "virtual-widget.h"
#include "funny-widg.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(resources);

    QApplication a(argc, argv);

    if(TrayIcon::isAvailable()) {
        QApplication::setQuitOnLastWindowClosed(false);

        FunnyWin funnywgt;

        ActivityDriver driver;
        TrayIcon trayico;
        VirtualWidget input_catcher;
        input_catcher.activate();

        driver.stop();
        trayico.show();
        QObject::connect(&trayico, SIGNAL(start()), &driver, SLOT(start()));
        QObject::connect(&trayico, SIGNAL(stop()), &driver, SLOT(stop()));

        QObject::connect(&driver, SIGNAL(notifyActivated()), &trayico, SLOT(onStart()));
        QObject::connect(&driver, SIGNAL(notifyStopped()), &trayico, SLOT(onStop()));        

        /* TBD: special driver for automatic mode */

        QObject::connect(&input_catcher, SIGNAL(realInput()), &driver, SLOT(stop()));
        QObject::connect(&input_catcher, SIGNAL(realInput()), &funnywgt, SLOT(hide()));

        QTimer autoact;
        QObject::connect(&autoact, &QTimer::timeout, [&input_catcher, &driver, &funnywgt]() {
            if(input_catcher.getInactiveTimeMs() > 5_seconds) {
               driver.start();

               funnywgt.setWindowTitle(GetForegroundWindowTitle());
               funnywgt.show();
            }
        });
        autoact.setInterval(5_seconds);

        QObject::connect(&trayico, &TrayIcon::activemode, [&autoact, &trayico, &driver](){
           if(autoact.isActive()) {
               autoact.stop();
               trayico.onPassiveMode();
               driver.stop();
           } else {
               autoact.start();
               trayico.onActiveMode();
           }
        });

        /* == */
        QObject::connect(&trayico, SIGNAL(quit()), qApp, SLOT(quit()));

        return a.exec();
    } else {
        QMessageBox::critical(0, "No-Systray", "No system tray available");
        return 1;
    }
}
