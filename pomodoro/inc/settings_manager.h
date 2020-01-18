#ifndef SETTINGS_MANAGER_H
#define SETTINGS_MANAGER_H

#include <QObject>
#include <array>
#include <string>
#include "isettings_manager.h"

class SettingsManager : public QObject, public ISettingsManager {
  Q_OBJECT
 public:
  explicit SettingsManager(QObject* parent = nullptr)
      : QObject(parent), ISettingsManager() {}
  SettingsManager(const SettingsManager&) = default;
  SettingsManager(SettingsManager&&) noexcept = default;
  SettingsManager& operator=(const SettingsManager&) = default;
  SettingsManager& operator=(SettingsManager&&) noexcept = default;
  virtual ~SettingsManager() noexcept = default;

  virtual void changeValues(settings_values time_values,
                            uint16_t pomodoros_number) override;
  virtual void saveToFile(const char* file_name) override;
  virtual void loadFromFile(const char* file_name) override;
  virtual uint16_t getTimeValueForMode(Mode mode) const override;
  virtual uint16_t getPomodorosNumber() const override;

 signals:
  void emitSettingsValuesChanged();

 private:
  const QString POMODOROS_NUMBER_KEY{"POMODOROS_NUMBER"};
  settings_values time_values_{};
  uint16_t pomodoros_number_{};
};

#endif  // SETTINGS_MANAGER
