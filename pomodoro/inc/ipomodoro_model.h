#ifndef IPOMODORO_MODEL_H
#define IPOMODORO_MODEL_H

#include "common.h"

class IPomodoroModel {
 public:
  explicit IPomodoroModel() {}
  IPomodoroModel(const IPomodoroModel&) = default;
  IPomodoroModel(IPomodoroModel&&) noexcept = default;
  IPomodoroModel& operator=(const IPomodoroModel&) = default;
  IPomodoroModel& operator=(IPomodoroModel&&) noexcept = default;
  virtual ~IPomodoroModel() noexcept = default;

  virtual void setMode(Mode mode) = 0;
  virtual void setTime(uint16_t seconds) = 0;
  virtual void start() = 0;
  virtual void pause() = 0;
  virtual void stop() = 0;
  virtual void reloadValues() = 0;

  // signals
  void emitNewTimerValue(uint16_t seconds);
  void emitNewModeValue(Mode mode);
};

#endif  // IPOMODORO_MODEL_H
