#ifndef POMODORO_MODEL_H
#define POMODORO_MODEL_H

#include <QDebug>
#include <QObject>
#include <QtPlugin>
#include "ipomodoro_model.h"
#include "itimer.h"

class PomodoroModel : public QObject, public IPomodoroModel {
  Q_OBJECT
 public:
  explicit PomodoroModel(QObject* parent = nullptr, ITimer* timer = nullptr);
  PomodoroModel(const PomodoroModel&) = default;
  PomodoroModel(PomodoroModel&&) noexcept = default;
  PomodoroModel& operator=(const PomodoroModel&) = default;
  PomodoroModel& operator=(PomodoroModel&&) noexcept = default;
  ~PomodoroModel() noexcept = default;

  virtual void setMode(Mode mode) override;
  virtual void start() override;
  virtual void pause() override;
  virtual void stop() override;

 signals:
  void timerValueChanged(uint16_t ms);

 protected:
  ITimer* timer_{};
  Mode mode_{Mode::WORK};  // get it from settings
};

#endif  // POMODORO_MODEL_H
