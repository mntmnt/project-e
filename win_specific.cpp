#include <windows.h>

#include <QString>

#include <functional>
#include <QDebug>

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
        return QString("NOHWND");
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

std::size_t IdleTime() {
     LASTINPUTINFO info;
     info.cbSize = sizeof(info);

     if(GetLastInputInfo(&info)) {
         auto dif = GetTickCount() - info.dwTime;
         return dif > 0 ? dif : 0u;
     }
     return 0u;
}

std::size_t getCurrentMilliseconds() {
    return GetTickCount();
}

bool registerRawInputFor(unsigned int id) {
   HWND hwnd = reinterpret_cast<HWND>(id);

   RAWINPUTDEVICE rd[2];
   rd[0].usUsage = 6;
   rd[0].usUsagePage = 1;
   rd[0].hwndTarget = hwnd;
   rd[0].dwFlags = RIDEV_INPUTSINK | 0x00002000;

   rd[1].usUsage = 2;
   rd[1].usUsagePage = 1;
   rd[1].hwndTarget = hwnd;
   rd[1].dwFlags = RIDEV_INPUTSINK | 0x00002000; //RIDEV_DEVNOTIFY;

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

    if(msg->message == 0x00fe) {
        qDebug() << "PLUG/UNPLUG device";
        return true;
    }

    return false;
}





