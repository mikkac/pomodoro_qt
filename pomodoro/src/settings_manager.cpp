#include "settings_manager.h"
#include <QApplication>
#include <QDebug>
#include <QSettings>

void SettingsManager::changeValues(settings_values time_values,
                                   uint16_t pomodoros_number) {
  time_values_ = time_values;
  pomodoros_number_ = pomodoros_number;
  emit emitSettingsValuesChanged();
}

void SettingsManager::saveToFile(const char *file_name) {
  auto settings_file = QApplication::applicationDirPath() + file_name;
  QSettings settings(settings_file, QSettings::NativeFormat);
  for (auto &pair : time_values_) {
    if (pair.second > 0)  // if value is less or equal to 0, it's probably empty
                          // or invalid. We shouldn't save it
      settings.setValue(QString::number(static_cast<uint16_t>(pair.first)),
                        pair.second);
  }
  if (pomodoros_number_ > 0)
    settings.setValue(POMODOROS_NUMBER_KEY, pomodoros_number_);
}

void SettingsManager::loadFromFile(const char *file_name) {
  auto settings_file = QApplication::applicationDirPath() + file_name;
  QSettings settings(settings_file, QSettings::NativeFormat);

  time_values_[Mode::WORK] =
      settings
          .value(QString::number(static_cast<uint16_t>(Mode::WORK)),
                 WORK_DEFAULT_TIME)
          .toUInt();

  time_values_[Mode::SHORT_BREAK] =
      settings
          .value(QString::number(static_cast<uint16_t>(Mode::SHORT_BREAK)),
                 SHORT_BREAK_DEFAULT_TIME)
          .toUInt();

  time_values_[Mode::LONG_BREAK] =
      settings
          .value(QString::number(static_cast<uint16_t>(Mode::LONG_BREAK)),
                 LONG_BREAK_DEFAULT_TIME)
          .toUInt();
  for (auto &pair : time_values_) {
    qDebug() << "LOAD FILES: "
             << QString::number(static_cast<uint16_t>(pair.first)) << ": "
             << pair.second;
  }
  pomodoros_number_ =
      settings.value(POMODOROS_NUMBER_KEY, DEFAULT_POMODOROS_NUMBER).toUInt();
  qDebug() << "LOAD FILES: "
           << "pomodoro_number: " << pomodoros_number_;
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
