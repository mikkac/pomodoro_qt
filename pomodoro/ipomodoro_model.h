#ifndef IPOMODORO_MODEL_H
#define IPOMODORO_MODEL_H

#include <QObject>

enum class Mode { NONE, WORK, SHORT_BREAK, LONG_BREAK };

class IPomodoroModel {
 public:
  explicit IPomodoroModel() {}
  IPomodoroModel(const IPomodoroModel&) = default;
  IPomodoroModel(IPomodoroModel&&) noexcept = default;
  IPomodoroModel& operator=(const IPomodoroModel&) = default;
  IPomodoroModel& operator=(IPomodoroModel&&) noexcept = default;
  virtual ~IPomodoroModel() noexcept = default;

  virtual void setMode(Mode mode) = 0;
  virtual void start() = 0;
  virtual void pause() = 0;
  virtual void stop() = 0;

  void timerValueChanged(uint16_t ms);
};

#endif  // IPOMODORO_MODEL_H
