#pragma once

#include <QSystemTrayIcon>
#include <QIcon>
#include <QMenu>

class TrayIcon : public QObject {
    Q_OBJECT

    QIcon inactive_mode_ico;
    QIcon active_mode_ico;
    QIcon waiting_mode_ico, *current_inactive_mode_ico;
    QMenu menu;
    QSystemTrayIcon tray_icon;
    QAction * automatic;

    enum action_on_activate {
        show_nothing = 0,
        show_funny = 1,
        show_imitation = 2
    };

public:

    TrayIcon():
        inactive_mode_ico(":/pics/ghost.png"),
        active_mode_ico(":/pics/pumpkin.png"),
        waiting_mode_ico(":/pics/waiting.png"),
        tray_icon(inactive_mode_ico),
        current_inactive_mode_ico(&inactive_mode_ico),
        menu(tr("ProjectCE"))
    {
        {
            auto act = menu.addAction(tr("Start"));
            connect(act, SIGNAL(triggered()), this, SIGNAL(start()));

            act = menu.addAction(tr("Stop"));
            connect(act, SIGNAL(triggered()), this, SIGNAL(stop()));

            automatic = menu.addAction(tr("Auto Mode"));
            connect(automatic, SIGNAL(triggered()), this, SIGNAL(activemode()));

            menu.addSeparator();

            act = menu.addAction("Funny widget");
            connect(act, &QAction::triggered, [this]() { emit changeAction( static_cast<int>(show_funny) ); });
            act = menu.addAction("Imitate");
            connect(act, &QAction::triggered, [this]() { emit changeAction( static_cast<int>(show_imitation) ); });
            act = menu.addAction("Show nothing");
            connect(act, &QAction::triggered, [this]() { emit changeAction( static_cast<int>(show_nothing) ); });

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
        automatic->setEnabled(false);
    }

    void onStop() {
        tray_icon.setIcon(*current_inactive_mode_ico);
        automatic->setEnabled(true);
    }

    void onActiveMode() {
        current_inactive_mode_ico = &waiting_mode_ico;
        tray_icon.setIcon(*current_inactive_mode_ico);
    }

    void onPassiveMode() {
        current_inactive_mode_ico = &inactive_mode_ico;
        tray_icon.setIcon(*current_inactive_mode_ico);
    }

signals:

    void changeAction(int);

    void start();
    void stop();
    void activemode();
    void quit();

};
