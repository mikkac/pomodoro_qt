#include "mode_manager.h"
#include <QDebug>

void ModeManager::reset() {
  qDebug() << "ModeManager: reset";
  pomodoros_counter_ = 0;
}

void ModeManager::setPomodorosBeforeLongBreak(uint16_t val) {
  qDebug() << "ModeManager: setPomodorosBeforeLongBreak/ old_val = "
           << QString::number(pomodoros_before_long_break_)
           << " / new_val = " << QString::number(val);
  pomodoros_before_long_break_ = val;
}

Mode ModeManager::checkModeAndSetNewIfNeeded(Mode current_mode) {
  qDebug() << "ModeManager: checkModeAndSetNewIfNeeded/ mode = "
           << modeAsString(current_mode);
  if (current_mode == Mode::WORK) {
    ++pomodoros_counter_;
    if (pomodoros_counter_ == pomodoros_before_long_break_) {
      pomodoros_counter_ = 0;
      return Mode::LONG_BREAK;
    } else {
      return Mode::SHORT_BREAK;
    }
  } else {
    return Mode::WORK;
  }
  return current_mode;
}
