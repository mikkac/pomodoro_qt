#ifndef POMODORO_MODEL_H
#define POMODORO_MODEL_H

#include <QDebug>
#include <QObject>
#include "ipomodoro_model.h"
#include "itimer.h"

class PomodoroModel : public QObject, public IPomodoroModel {
  Q_OBJECT
 public:
  explicit PomodoroModel(QObject* parent = nullptr, ITimer* timer = nullptr)
      : QObject(parent), IPomodoroModel(), timer_{timer} {
    qDebug() << "PomodoroModel: ctor";
  }
  PomodoroModel(const PomodoroModel&) = default;
  PomodoroModel(PomodoroModel&&) noexcept = default;
  PomodoroModel& operator=(const PomodoroModel&) = default;
  PomodoroModel& operator=(PomodoroModel&&) noexcept = default;
  ~PomodoroModel() noexcept = default;

  virtual void setMode(Mode mode) override;

 public slots:
  virtual void start() override;
  virtual void pause() override;
  virtual void stop() override;

 protected:
  ITimer* timer_{};
};

#endif  // POMODORO_MODEL_H
