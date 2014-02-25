#pragma once

#include <functional>

#include <QString>
#include <QRect>

void sendKeyStrokes();

QString GetForegroundWindowTitle();

QRect GetForegroundWindowSize();

std::size_t IdleTime();

bool isDesktopWindow();


bool registerRawInputFor(unsigned int);

bool processRawInputFor(const QByteArray &, void *, long *, std::function<void()>);

std::size_t getCurrentMilliseconds();
