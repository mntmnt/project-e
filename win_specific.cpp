#include <windows.h>

#include <QString>
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


