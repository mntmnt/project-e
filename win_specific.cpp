#include <windows.h>

#include <QString>

#include <functional>
#include <QDebug>

#include "win_predefs.h"

void KeyBDown(const WORD code) {
    INPUT Input = { 0 };

    Input.type = INPUT_KEYBOARD;
    Input.ki.wVk   = code;
    SendInput( 1, &Input, sizeof( INPUT ));
}

void KeyBUp(const WORD code) {
    INPUT Input = { 0 };

    Input.type = INPUT_KEYBOARD;
    Input.ki.dwFlags = KEYEVENTF_KEYUP;
    Input.ki.wVk   = code;
    SendInput( 1, &Input, sizeof( INPUT ) );
}

struct KeyClick {
    WORD cd;
    KeyClick(const WORD code): cd(code) {
        KeyBDown(cd);
    }

    ~KeyClick() {
        KeyBUp(cd);
    }
};


void KeybClick(const WORD code) {
    KeyClick click(code);
}

void KeybClick(const WORD modifier, const WORD code) {
    KeyClick hold(modifier);
    KeybClick(code);
}


void sendKeyStrokes() {
    KeybClick(VK_LSHIFT, 'A');
    KeybClick('X');
    KeybClick('E');
    KeybClick('L');

    KeybClick(qrand() % 2 == 0 ? VK_SPACE : VK_RETURN);
}

QString GetForegroundWindowTitle() {
    auto foreground = GetForegroundWindow(); //GetTopWindow(NULL);

    if(!foreground) {
        return "NOHWND";
    }

    if(isDesktopWindow()) {
        return "Desktop :)";
    }

    const int maxcount = 255;
    wchar_t str[maxcount] = {0};

    auto copied = GetWindowTextW(foreground, str, maxcount);

    if( copied < 1) {
        return QString("");
    } else {
        return QString::fromWCharArray(str, copied);
    }
}

QRect GetForegroundWindowSize() {
    auto foreground = GetForegroundWindow();

    if(!foreground || isDesktopWindow()) {
        return QRect(0,0,-1,-1);
    }

    RECT rect;
    if(GetWindowRect(foreground, &rect) == 0) {
        return QRect(-1, -1, -1, -1);
    }

    return QRect(rect.left, rect.top, std::abs(rect.right - rect.left), std::abs(rect.top - rect.bottom));
}

bool isDesktopWindow() {
    return GetForegroundWindow() == GetDesktopWindow();
}

std::size_t getCurrentMilliseconds() {
    return GetTickCount();
}

bool registerRawInputFor(unsigned int id) {
   HWND hwnd = reinterpret_cast<HWND>(id);

   const DWORD ridev_devnitify = 0x00002000;
   const USHORT kbUsage = 6, kbUsagePage = 1;
   const USHORT mouseUsage = 2, mouseUsagePage = 1;

   RAWINPUTDEVICE rd[2];
   rd[0].usUsage = kbUsage;
   rd[0].usUsagePage = kbUsagePage;
   rd[0].hwndTarget = hwnd;
   rd[0].dwFlags = RIDEV_INPUTSINK | ridev_devnitify;

   rd[1].usUsage = mouseUsage;
   rd[1].usUsagePage = mouseUsagePage;
   rd[1].hwndTarget = hwnd;
   rd[1].dwFlags = RIDEV_INPUTSINK | ridev_devnitify;

   auto res = RegisterRawInputDevices(rd, 2, sizeof(RAWINPUTDEVICE));

   if(res == FALSE) {
       qDebug() << "could not register RegisterRawInputDevices for mouse and keyboard";
       return false;
   }

   return true;
}

bool processRawInputFor(const QByteArray &, void * message, long * res, std::function<void()> onUserActivity) {
    MSG* msg = reinterpret_cast<MSG*>(message);

    if(msg->message == WM_INPUT) {
       UINT sz = sizeof(RAWINPUT);

       RAWINPUT rawd;

       auto rst = GetRawInputData((HRAWINPUT)msg->lParam, RID_INPUT, &rawd, &sz, sizeof (RAWINPUTHEADER));

       if(rst == (UINT)-1) {
           //error buffer;
          return true;
       }

       RAWINPUT * raw = & rawd;

       if(raw->header.hDevice != nullptr) {
           if(raw->header.dwType == RIM_TYPEMOUSE || raw->header.dwType == RIM_TYPEKEYBOARD) {
               onUserActivity();
           }
       }
       return true;
    }

    const UINT plug_unplug_raw_device = 0x00fe;
    if(msg->message == plug_unplug_raw_device) {
        qDebug() << "PLUG/UNPLUG device";
        return true;
    }

    return false;
}





