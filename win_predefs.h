#pragma once

#include <functional>

bool registerRawInputFor(unsigned int);

bool processRawInputFor(const QByteArray &, void *, long *, std::function<void()>);

std::size_t getCurrentMilliseconds();
