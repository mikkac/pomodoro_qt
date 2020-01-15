#ifndef TIMER_H
#define TIMER_H

#include <QDebug>
#include <QTimer>
#include "itimer.h"

class Timer : public QObject, public ITimer {
  Q_OBJECT
 public:
  explicit Timer(QObject* parent = nullptr) : QObject(parent), ITimer() {
    qDebug() << "Timer: ctor";
  }
  Timer(const Timer&) = default;
  Timer(Timer&&) = default;
  Timer& operator=(const Timer&) noexcept = default;
  Timer& operator=(Timer&&) noexcept = default;
  ~Timer() noexcept = default;

  virtual void startCountdown(uint16_t init_ms) override;
  virtual void stopCountdown() override;

 signals:
  void timeChanged(uint16_t new_time_ms);

 private:
  uint16_t time_left{};
  QTimer* timer_;
};

#endif  // TIMER_H
