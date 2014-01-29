#ifndef TRAY_ICON_H
#define TRAY_ICON_H

#include <QSystemTrayIcon>
#include <QIcon>
#include <QMenu>

class TrayIcon : public QObject {
    Q_OBJECT

    QIcon inactive_mode_ico;
    QIcon active_mode_ico;
    QSystemTrayIcon tray_icon;
    QMenu menu;

public:

    TrayIcon():
        inactive_mode_ico(":/pics/ghost.png"),
        active_mode_ico(":/pics/pumpkin.png"),
        tray_icon(inactive_mode_ico),
        menu(tr("ProjectCE"))
    {
        {
            auto act = menu.addAction(tr("Start"));
            QObject::connect(act, SIGNAL(triggered()), this, SIGNAL(start()));
//            QObject::connect(act, &QAction::triggered, [this](){ tray_icon.setIcon(active_mode_ico); });

            act = menu.addAction(tr("Stop"));
            QObject::connect(act, SIGNAL(triggered()), this, SIGNAL(stop()));
//            QObject::connect(act, &QAction::triggered, [this]() { tray_icon.setIcon(inactive_mode_ico); });

            menu.addSeparator();

            act = menu.addAction(tr("Quit"));
            QObject::connect(act, SIGNAL(triggered()), this, SIGNAL(quit()));
        }

        tray_icon.setContextMenu(&menu);
    }

    static bool isAvailable() {
        return QSystemTrayIcon::isSystemTrayAvailable();
    }

public slots:

    void show() {
        tray_icon.show();
    }

    void onStart() {
        tray_icon.setIcon(active_mode_ico);
    }

    void onStop() {
        tray_icon.setIcon(inactive_mode_ico);
    }

signals:

    void start();
    void stop();
    void quit();

};

#endif // TRAY_ICON_H
