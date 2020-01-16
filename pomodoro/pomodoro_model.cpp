#include "pomodoro_model.h"

PomodoroModel::PomodoroModel(QObject* parent, ITimer* timer)
    : QObject(parent), IPomodoroModel(), timer_{timer} {
  qDebug() << "PomodoroModel: ctor";
  QObject::connect(dynamic_cast<QObject*>(timer_), SIGNAL(updateTime(uint16_t)),
                   this, SLOT(timerValueChanged(uint16_t)));
  // Load values from settings
  setMode(Mode::WORK);
}

void PomodoroModel::setMode(Mode mode) {
  modeValueChanged(mode);
  qDebug() << "PomodoroModel: setMode = " << QString(static_cast<int>(mode));
}

void PomodoroModel::setTime(uint16_t seconds) {
  init_time_left_seconds_ = seconds;
  emit emitNewTimerValue(init_time_left_seconds_);
}

void PomodoroModel::start() {
  if (timer_) timer_->startCountdown(time_left_seconds_);
  qDebug() << "PomodoroModel: start";
}

void PomodoroModel::pause() {
  if (timer_) timer_->stopCountdown();
  qDebug() << "PomodoroModel: pause";
}

void PomodoroModel::stop() {
  time_left_seconds_ = init_time_left_seconds_;
  emit emitNewTimerValue(time_left_seconds_);
  if (timer_) timer_->stopCountdown();
  qDebug() << "PomodoroModel: stop";
}

void PomodoroModel::reloadValues() {
  emit emitNewModeValue(mode_);
  emit emitNewTimerValue(time_left_seconds_);
}

void PomodoroModel::timerValueChanged(uint16_t seconds) {
  time_left_seconds_ = seconds;
  emit emitNewTimerValue(seconds);
}

void PomodoroModel::modeValueChanged(Mode mode) {
  mode_ = mode;
  emit emitNewModeValue(mode_);
}
