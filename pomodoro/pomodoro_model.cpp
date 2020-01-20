#include "pomodoro_model.h"
#include <QDebug>

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
  qDebug() << "PomodoroModel: setMode/ old_mode = " << modeAsString(mode_)
           << "/ new_mode = " << modeAsString(mode);
  modeValueChanged(mode);
}

void PomodoroModel::setTime(uint16_t seconds) {
  qDebug() << "PomodoroModel: setTime/ old_time = " << init_time_left_seconds_
           << "/ new_time = " << seconds;
  init_time_left_seconds_ = seconds;
  emit emitNewTimerValue(init_time_left_seconds_);
}

void PomodoroModel::start() {
  qDebug() << "PomodoroModel: start";
  is_started = true;
  if (timer_) timer_->startCountdown(time_left_seconds_);
}

void PomodoroModel::pause() {
  qDebug() << "PomodoroModel: pause";
  if (timer_) timer_->stopCountdown();
}

void PomodoroModel::stop() {
  qDebug() << "PomodoroModel: stop";
  is_started = false;
  reset();
  emit emitNewTimerValue(time_left_seconds_);
  if (timer_) timer_->stopCountdown();
}

void PomodoroModel::reloadValues() {
  qDebug() << "PomodoroModel: reloadValues";
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
  qDebug() << "PomodoroModel: setMode/ old_mode = " << modeAsString(mode_)
           << "/ new_mode = " << modeAsString(mode);
  if (mode != mode_) {
    mode_ = mode;
    emit emitNewModeValue(mode_);
  }
}

void PomodoroModel::settingsValuesChanged() {
  qDebug() << "PomodoroModel: settingsValueChanged";
  setProperValues();
  if (!is_started) {
    time_left_seconds_ = init_time_left_seconds_;
    emit emitNewTimerValue(time_left_seconds_);
  }
}

void PomodoroModel::setProperValues() {
  qDebug() << "PomodoroModel: setProperValues/ old_time = "
           << QString::number(init_time_left_seconds_) << "/ old_pomodoros = "
           << QString::number(pomodoros_before_long_break_);

  if (settings_manager_) {
    init_time_left_seconds_ =
        settings_manager_->getTimeValueForMode(mode_) * 60;
    pomodoros_before_long_break_ = settings_manager_->getPomodorosNumber();
  }
  qDebug() << "PomodoroModel: setProperValues/ new_time = "
           << QString::number(init_time_left_seconds_) << "/ new_pomodoros = "
           << QString::number(pomodoros_before_long_break_);
}

void PomodoroModel::reset() {
  qDebug() << "PomodoroModel: reset";
  setMode(Mode::WORK);
  setProperValues();
  time_left_seconds_ = init_time_left_seconds_;
  if (mode_manager_) mode_manager_->reset();
  emit emitNewTimerValue(time_left_seconds_);
}
