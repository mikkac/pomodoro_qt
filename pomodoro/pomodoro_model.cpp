#include "pomodoro_model.h"

PomodoroModel::PomodoroModel(QObject* parent, ITimer* timer,
                             IModeManager* mode_manager)
    : QObject(parent),
      IPomodoroModel(),
      timer_{timer},
      mode_manager_{mode_manager} {
  qDebug() << "PomodoroModel: ctor";
  QObject::connect(dynamic_cast<QObject*>(timer_), SIGNAL(updateTime(uint16_t)),
                   this, SLOT(timerValueChanged(uint16_t)));
  // Load values from settings
  if (mode_manager_) mode_manager->setPomodorosBeforeLongBreak(4);
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
  qDebug() << "TIME LEFT =" << QString::number(time_left_seconds_);
  qDebug() << "PomodoroModel: start";
}

void PomodoroModel::pause() {
  if (timer_) timer_->stopCountdown();
  qDebug() << "PomodoroModel: pause";
}

void PomodoroModel::stop() {
  time_left_seconds_ = init_time_left_seconds_;
  setMode(Mode::WORK);
  if (mode_manager_) mode_manager_->reset();
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
  if (time_left_seconds_ == 0) {  // Time to change mode
    if (timer_) timer_->stopCountdown();
    if (mode_manager_)
      setMode(mode_manager_->checkModeAndSetNewIfNeeded(mode_));
    setProperInitTime();
    time_left_seconds_ = init_time_left_seconds_;
  }
  emit emitNewTimerValue(time_left_seconds_);
}

void PomodoroModel::modeValueChanged(Mode mode) {
  mode_ = mode;
  emit emitNewModeValue(mode_);
}

void PomodoroModel::setProperInitTime() {
  switch (mode_) {
    case Mode::WORK:
      init_time_left_seconds_ = 5;
      break;
    case Mode::SHORT_BREAK:
      init_time_left_seconds_ = 3;
      break;
    case Mode::LONG_BREAK:
      init_time_left_seconds_ = 10;
      break;
  }
}
