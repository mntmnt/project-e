#include <QApplication>

#include "activity_driver.h"

#include "tray_icon.h"
#include <QMessageBox>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(resources);

    QApplication a(argc, argv);

    if(TrayIcon::isAvailable()) {
        QApplication::setQuitOnLastWindowClosed(false);

        ActivityDriver driver;
        driver.stop();
        auto tmr = &driver;

        /* == For development purposes = */
        QLabel label;
        label.setText(QObject::tr("ProjectEKA"));
        label.show();
        int counter = 0;

        QObject::connect(tmr, &ActivityDriver::shot, [&label, &counter]() {
            label.setText(QString("<b>ProjectEKA<b> - <font color=red>") + QString::number(counter++) + "</font>");
        });
        /* == end = */

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
