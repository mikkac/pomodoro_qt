#include "timer.h"
#include <QDebug>

Timer::Timer(QObject* parent) : QObject(parent), ITimer() {
  qDebug() << "Timer: ctor";
  timer_ = new QTimer();
  timer_->setInterval(1000);
  QObject::connect(timer_, SIGNAL(timeout()), this, SLOT(tick()));
}

void Timer::startCountdown(uint16_t init_ms) {
  time_left_ = init_ms;
  timer_->start();
  qDebug() << "Timer: startCountdown = " << init_ms;
}

void Timer::stopCountdown() {
  timer_->stop();
  qDebug() << "Timer: stopCountdown";
}

void Timer::tick() {
  time_left_ -= interval_ / 1000;
  emit updateTime(time_left_);
}
