#include "pomodoro_model.h"

PomodoroModel::PomodoroModel(QObject* parent, ITimer* timer,
                             IModeManager* mode_manager,
                             ISettingsManager* settings_manager)
    : QObject(parent),
      IPomodoroModel(),
      timer_{timer},
      mode_manager_{mode_manager},
      settings_manager_{settings_manager} {
  qDebug() << "PomodoroModel: ctor";
  QObject::connect(dynamic_cast<QObject*>(timer_), SIGNAL(updateTime(uint16_t)),
                   this, SLOT(timerValueChanged(uint16_t)));
  QObject::connect(dynamic_cast<QObject*>(settings_manager_),
                   SIGNAL(emitSettingsValuesChanged()), this,
                   SLOT(settingsValuesChanged()));

  mode_ = Mode::WORK;
  if (settings_manager_) settings_manager_->loadFromFile(DEFAULT_SETTINGS_FILE);
  if (mode_manager_)
    mode_manager->setPomodorosBeforeLongBreak(pomodoros_before_long_break_);
  setProperValues();
  time_left_seconds_ = init_time_left_seconds_;
  reloadValues();
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
  is_started = true;
  if (timer_) timer_->startCountdown(time_left_seconds_);
  qDebug() << "TIME LEFT =" << QString::number(time_left_seconds_);
  qDebug() << "PomodoroModel: start";
}

void PomodoroModel::pause() {
  if (timer_) timer_->stopCountdown();
  qDebug() << "PomodoroModel: pause";
}

void PomodoroModel::stop() {
  is_started = false;
  reset();
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
  if (time_left_seconds_ == 0) {  // Time to change the mode
    if (timer_) timer_->stopCountdown();
    if (mode_manager_)
      setMode(mode_manager_->checkModeAndSetNewIfNeeded(mode_));
    setProperValues();
    time_left_seconds_ = init_time_left_seconds_;
  }
  emit emitNewTimerValue(time_left_seconds_);
}

void PomodoroModel::modeValueChanged(Mode mode) {
  qDebug() << "MODE CHANGEEED " << QString::number(static_cast<uint16_t>(mode))
           << "/" << QString::number(static_cast<uint16_t>(mode_));
  if (mode != mode_) {
    mode_ = mode;
    emit emitNewModeValue(mode_);
  }
}

void PomodoroModel::settingsValuesChanged() {
  setProperValues();
  if (!is_started) {
    time_left_seconds_ = init_time_left_seconds_;
    emit emitNewTimerValue(time_left_seconds_);
  }
}

void PomodoroModel::setProperValues() {  // TODO Load those values from
                                         // settings
  if (settings_manager_) {
    init_time_left_seconds_ =
        settings_manager_->getTimeValueForMode(mode_) * 60;
    pomodoros_before_long_break_ = settings_manager_->getPomodorosNumber();
  }
  qDebug() << "VALUES CHANGE" << QString::number(init_time_left_seconds_) << " "
           << QString::number(pomodoros_before_long_break_);
}

void PomodoroModel::reset() {
  setMode(Mode::WORK);
  setProperValues();
  time_left_seconds_ = init_time_left_seconds_;
  if (mode_manager_) mode_manager_->reset();
  emit emitNewTimerValue(time_left_seconds_);
}
