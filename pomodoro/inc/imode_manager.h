#ifndef IMODE_MANAGER_H
#define IMODE_MANAGER_H

#include "common.h"

class IModeManager {
 public:
  explicit IModeManager(uint16_t pomodoros_before_long_break = 0)
      : pomodoros_before_long_break_{pomodoros_before_long_break} {}
  IModeManager(const IModeManager&) = default;
  IModeManager(IModeManager&&) noexcept = default;
  IModeManager& operator=(const IModeManager&) = default;
  IModeManager& operator=(IModeManager&&) noexcept = default;
  virtual ~IModeManager() noexcept = default;

  virtual void reset() = 0;
  virtual void setPomodorosBeforeLongBreak(uint16_t val) = 0;
  virtual Mode checkModeAndSetNewIfNeeded(Mode current_mode) = 0;

 protected:
  uint16_t pomodoros_before_long_break_{};
  uint16_t pomodoros_counter_{0};
};

#endif  // IMODE_MANAGER_H
