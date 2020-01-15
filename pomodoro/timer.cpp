#include "timer.h"
#include <QDebug>

void Timer::startCountdown(uint16_t init_ms) {
  qDebug() << "Timer: startCountdown = " << init_ms;
}

void Timer::stopCountdown() { qDebug() << "Timer: stopCountdown"; }
