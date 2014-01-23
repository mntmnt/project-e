#include <windows.h>

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
