#ifndef ITIMER_H
#define ITIMER_H

class ITimer {
 public:
  ITimer() = default;
  ITimer(const ITimer&) = default;
  ITimer(ITimer&&) noexcept = default;
  ITimer& operator=(const ITimer&) = default;
  ITimer& operator=(ITimer&&) noexcept = default;
  virtual ~ITimer() noexcept = default;

  virtual void startCountdown(uint16_t init_seconds) = 0;
  virtual void stopCountdown() = 0;

  void updateTime(uint16_t seconds);
};

#endif  // ITIMER_H
