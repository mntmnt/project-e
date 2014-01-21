#include <windows.h>

#include <QDebug>

void sendKeyStrokes() {
    INPUT Input = { 0 };
    // shift key down
    Input.type       = INPUT_KEYBOARD;
    Input.ki.wVk   = VK_LSHIFT;
    SendInput( 1, &Input, sizeof( INPUT ) );

    // 'a' key down
    Input.type       = INPUT_KEYBOARD;
    Input.ki.wVk   = 'A';
    SendInput( 1, &Input, sizeof( INPUT ) );

    // 'a' key release
    Input.type       = INPUT_KEYBOARD;
    Input.ki.dwFlags = KEYEVENTF_KEYUP;
    Input.ki.wVk   = 'A';
    SendInput( 1, &Input, sizeof( INPUT ) );

    // shift key release
    Input.type       = INPUT_KEYBOARD;
    Input.ki.dwFlags = KEYEVENTF_KEYUP;
    Input.ki.wVk   = VK_LSHIFT;
    SendInput( 1, &Input, sizeof( INPUT ) );

    /*X*/

    Input.ki.dwFlags = 0;
    // 'x' key down
    Input.type       = INPUT_KEYBOARD;
    Input.ki.wVk   = 'X';
    SendInput( 1, &Input, sizeof( INPUT ) );

    // 'x' key release
    Input.type       = INPUT_KEYBOARD;
    Input.ki.dwFlags = KEYEVENTF_KEYUP;
    Input.ki.wVk   = 'X';
    SendInput( 1, &Input, sizeof( INPUT ) );


    /*E*/

    Input.ki.dwFlags = 0;
    // 'e' key down
    Input.type       = INPUT_KEYBOARD;
    Input.ki.wVk   = 'E';
    SendInput( 1, &Input, sizeof( INPUT ) );

    // 'e' key release
    Input.type       = INPUT_KEYBOARD;
    Input.ki.dwFlags = KEYEVENTF_KEYUP;
    Input.ki.wVk   = 'E';
    SendInput( 1, &Input, sizeof( INPUT ) );

    /*l*/

    Input.ki.dwFlags = 0;
    // 'l' key down
    Input.type       = INPUT_KEYBOARD;
    Input.ki.wVk   = 'L';
    SendInput( 1, &Input, sizeof( INPUT ) );


    // 'l' key release
    Input.type       = INPUT_KEYBOARD;
    Input.ki.dwFlags = KEYEVENTF_KEYUP;
    Input.ki.wVk   = 'L';
    SendInput( 1, &Input, sizeof( INPUT ) );


    /*SP*/
    Input.ki.dwFlags = 0;
    int space = qrand() % 2;

    // 'a' key down
    Input.type       = INPUT_KEYBOARD;
    Input.ki.wVk   = ( (space == 0) ? VK_SPACE : VK_RETURN );
    SendInput( 1, &Input, sizeof( INPUT ) );


    // 'a' key release
    Input.type       = INPUT_KEYBOARD;
    Input.ki.dwFlags = KEYEVENTF_KEYUP;
    Input.ki.wVk   = ( (space == 0) ? VK_SPACE : VK_RETURN );
    SendInput( 1, &Input, sizeof( INPUT ) );


    qDebug() << "RESULT is " << 0 << "\n";
}
