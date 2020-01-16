#ifndef MODE_MANAGER_H
#define MODE_MANAGER_H

#include <QObject>
#include "imode_manager.h"

class ModeManager : public QObject, public IModeManager {
 public:
  explicit ModeManager(uint16_t pomodoros_before_long_break = 0,
                       QObject* parent = nullptr)
      : QObject(parent), IModeManager(pomodoros_before_long_break) {}
  ModeManager(const ModeManager&) = default;
  ModeManager(ModeManager&&) noexcept = default;
  ModeManager& operator=(const ModeManager&) = default;
  ModeManager& operator=(ModeManager&&) noexcept = default;
  virtual ~ModeManager() noexcept = default;

  virtual void reset() override;
  virtual void setPomodorosBeforeLongBreak(uint16_t val) override;
  virtual Mode checkModeAndSetNewIfNeeded(Mode current_mode) override;
};

#endif  // MODE_MANAGER_H
