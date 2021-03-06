#include "timer.h"
#include <QDebug>

Timer::Timer(QObject* parent) : QObject(parent), ITimer() {
  qDebug() << "Timer: ctor";
  timer_ = new QTimer();
  timer_->setInterval(1000);
  QObject::connect(timer_, SIGNAL(timeout()), this, SLOT(tick()));
}

void Timer::startCountdown(uint16_t init_seconds) {
  qDebug() << "Timer: startCountdown/ init_seconds = " << init_seconds;
  time_left_seconds_ = init_seconds;
  timer_->start();
}

void Timer::stopCountdown() {
  qDebug() << "Timer: stopCountdown";
  timer_->stop();
}

void Timer::tick() {
  time_left_seconds_ -= interval_ms_ / 1000;
  emit updateTime(time_left_seconds_);
}
