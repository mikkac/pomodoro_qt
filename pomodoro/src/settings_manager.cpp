#include "settings_manager.h"
#include <QDebug>

void SettingsManager::changeValues(settings_values time_values,
                                   uint16_t pomodoros_number) {
  time_values_ = time_values;
  pomodoros_number_ = pomodoros_number;
  emit emitSettingsValuesChanged();
}

void SettingsManager::saveToFile(const char *file_name) {
  qDebug() << "SAVE TO FILE " << QString(file_name);
}

void SettingsManager::loadFromFile(const char *file_name) {
  qDebug() << "LOAD FROM FILE " << QString(file_name);
}

uint16_t SettingsManager::getTimeValueForMode(Mode mode) const {
  auto it = time_values_.find(mode);
  if (it != time_values_.end())
    return it->second;
  else
    return defaultTimeValueForMode(mode);
}

uint16_t SettingsManager::getPomodorosNumber() const {
  if (pomodoros_number_ > 0)
    return pomodoros_number_;
  else
    return DEFAULT_POMODOROS_NUMBER;
}
