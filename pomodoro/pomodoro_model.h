#ifndef POMODORO_MODEL_H
#define POMODORO_MODEL_H

#include <QObject>
#include "imode_manager.h"
#include "ipomodoro_model.h"
#include "isettings_manager.h"
#include "itimer.h"

class PomodoroModel : public QObject, public IPomodoroModel {
  Q_OBJECT
 public:
  explicit PomodoroModel(QObject* parent = nullptr, ITimer* timer = nullptr,
                         IModeManager* mode_manager = nullptr,
                         ISettingsManager* settings_manager = nullptr);
  PomodoroModel(const PomodoroModel&) = default;
  PomodoroModel(PomodoroModel&&) noexcept = default;
  PomodoroModel& operator=(const PomodoroModel&) = default;
  PomodoroModel& operator=(PomodoroModel&&) noexcept = default;
  ~PomodoroModel() noexcept = default;

  virtual void setMode(Mode mode) override;
  virtual void setTime(uint16_t seconds) override;
  virtual void start() override;
  virtual void pause() override;
  virtual void stop() override;
  virtual void reloadValues() override;

 signals:
  void emitNewTimerValue(uint16_t seconds);
  void emitNewModeValue(Mode mode);

 private slots:
  void timerValueChanged(uint16_t seconds);
  void modeValueChanged(Mode mode);
  void settingsValuesChanged();

 private:
  void setProperValues();
  void reset();

 private:
  ITimer* timer_{};
  IModeManager* mode_manager_{};
  ISettingsManager* settings_manager_{};
  Mode mode_{Mode::WORK};
  uint16_t init_time_left_seconds_{};
  uint16_t time_left_seconds_{init_time_left_seconds_};
  uint16_t pomodoros_before_long_break_{};
  bool is_started{false};
};

#endif  // POMODORO_MODEL_H
