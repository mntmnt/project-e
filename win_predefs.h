#pragma once

#include <functional>

#include <QString>

void sendKeyStrokes();

QString GetForegroundWindowTitle();

std::size_t IdleTime();

bool isDesktopWindow();


bool registerRawInputFor(unsigned int);

bool processRawInputFor(const QByteArray &, void *, long *, std::function<void()>);

std::size_t getCurrentMilliseconds();

std::size_t operator "" _seconds(unsigned long long);

// *User-defined literals
