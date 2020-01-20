#ifndef ISETTINGS_MANAGER_H
#define ISETTINGS_MANAGER_H

#include "common.h"

class ISettingsManager {
 public:
  explicit ISettingsManager() = default;
  ISettingsManager(const ISettingsManager&) = default;
  ISettingsManager(ISettingsManager&&) noexcept = default;
  ISettingsManager& operator=(const ISettingsManager&) = default;
  ISettingsManager& operator=(ISettingsManager&&) noexcept = default;
  virtual ~ISettingsManager() noexcept = default;

  virtual void changeValues(settings_values time_values,
                            uint16_t pomodoros_number) = 0;
  virtual void saveToFile(const char* file_name) = 0;
  virtual void loadFromFile(const char* file_name) = 0;
  virtual uint16_t getTimeValueForMode(Mode mode) const = 0;
  virtual uint16_t getPomodorosNumber() const = 0;

  // signals
  void emitSettingsValuesChanged();
};

#endif  // ISETTINGS_MANAGER_H
