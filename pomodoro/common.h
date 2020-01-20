#ifndef POMODORO_COMMON_H
#define POMODORO_COMMON_H

#include <QDateTime>
#include <QDebug>
#include <QString>
#define DEFAULT_SETTINGS_FILE "pomodoro_settings.txt"

constexpr uint16_t WORK_DEFAULT_TIME = 20;
constexpr uint16_t SHORT_BREAK_DEFAULT_TIME = 5;
constexpr uint16_t LONG_BREAK_DEFAULT_TIME = 15;
constexpr uint16_t DEFAULT_POMODOROS_NUMBER = 4;

enum class Mode { WORK, SHORT_BREAK, LONG_BREAK };

using settings_values = std::map<Mode, uint16_t>;

inline uint16_t defaultTimeValueForMode(Mode mode) {
  switch (mode) {
    case Mode::WORK:
      return WORK_DEFAULT_TIME;
    case Mode::SHORT_BREAK:
      return SHORT_BREAK_DEFAULT_TIME;
    case Mode::LONG_BREAK:
      return LONG_BREAK_DEFAULT_TIME;
    default:
      return WORK_DEFAULT_TIME;
  }
}

inline QString formatTime(uint16_t seconds) {
  if (seconds <= 3600)
    return QDateTime::fromTime_t(seconds).toUTC().toString("mm:ss");
  else
    return QDateTime::fromTime_t(seconds).toUTC().toString("hh:mm:ss");
}

#endif  // POMODORO_COMMON_H
