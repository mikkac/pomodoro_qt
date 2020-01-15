#include "pomodoro_model.h"

PomodoroModel::PomodoroModel(QObject* parent, ITimer* timer)
    : QObject(parent), IPomodoroModel(), timer_{timer} {
  qDebug() << "PomodoroModel: ctor";
  QObject::connect(dynamic_cast<QObject*>(timer_), SIGNAL(updateTime(uint16_t)),
                   this, SIGNAL(timerValueChanged(uint16_t)));
}

void PomodoroModel::setMode(Mode mode) {
  qDebug() << "PomodoroModel: setMode = " << QString(static_cast<int>(mode));
}

void PomodoroModel::start() {
  if (timer_) timer_->startCountdown(123);
  qDebug() << "PomodoroModel: start";
}

void PomodoroModel::pause() {
  if (timer_) timer_->stopCountdown();
  qDebug() << "PomodoroModel: pause";
}

void PomodoroModel::stop() {
  if (timer_) timer_->stopCountdown();
  qDebug() << "PomodoroModel: stop";
}
