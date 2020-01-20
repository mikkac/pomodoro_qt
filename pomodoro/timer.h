#ifndef TIMER_H
#define TIMER_H

#include <QTimer>
#include "itimer.h"

class Timer : public QObject, public ITimer {
  Q_OBJECT
 public:
  explicit Timer(QObject* parent = nullptr);
  Timer(const Timer&) = default;
  Timer(Timer&&) = default;
  Timer& operator=(const Timer&) noexcept = default;
  Timer& operator=(Timer&&) noexcept = default;
  ~Timer() noexcept = default;

  virtual void startCountdown(uint16_t init_seconds) override;
  virtual void stopCountdown() override;

 signals:
  void updateTime(uint16_t seconds);
 private slots:
  void tick();

 private:
  uint16_t interval_ms_{1000};
  uint16_t time_left_seconds_{};
  QTimer* timer_;
};

#endif  // TIMER_H
