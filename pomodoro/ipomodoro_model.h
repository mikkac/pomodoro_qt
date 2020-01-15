#ifndef IPOMODORO_MODEL_H
#define IPOMODORO_MODEL_H

enum class Mode { NONE, WORK, SHORT_BREAK, LONG_BREAK };

class IPomodoroModel {
 public:
  IPomodoroModel() = default;
  IPomodoroModel(const IPomodoroModel&) = default;
  IPomodoroModel(IPomodoroModel&&) noexcept = default;
  IPomodoroModel& operator=(const IPomodoroModel&) = default;
  IPomodoroModel& operator=(IPomodoroModel&&) noexcept = default;
  virtual ~IPomodoroModel() noexcept = default;

  virtual void setMode(Mode mode) = 0;

 public slots:
  virtual void start() = 0;
  virtual void pause() = 0;
  virtual void stop() = 0;
};

#endif  // IPOMODORO_MODEL_H
