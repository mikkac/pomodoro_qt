#include "settings_manager.h"
#include <QApplication>
#include <QDebug>
#include <QSettings>

void SettingsManager::changeValues(settings_values time_values,
                                   uint16_t pomodoros_number) {
  qDebug() << "SettingsManager: changeValues";
  time_values_ = time_values;
  pomodoros_number_ = pomodoros_number;
  emit emitSettingsValuesChanged();
}

void SettingsManager::saveToFile(const char *file_name) {
  auto settings_file = QApplication::applicationDirPath() + file_name;
  qDebug() << "SettingsManager: saveToFile/ file_name = " << settings_file;

  QSettings settings(settings_file, QSettings::NativeFormat);
  for (auto &pair : time_values_) {
    if (pair.second >= 1)  // if value is less or equal to 0, it's probably
                           // empty or invalid. We shouldn't save it
      settings.setValue(QString::number(static_cast<uint16_t>(pair.first)),
                        pair.second);
  }
  if (pomodoros_number_ > 0)
    settings.setValue(POMODOROS_NUMBER_KEY, pomodoros_number_);
}

void SettingsManager::loadFromFile(const char *file_name) {
  auto settings_file = QApplication::applicationDirPath() + file_name;
  qDebug() << "SettingsManager: loadFromFile/ file_name = " << settings_file;

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
  pomodoros_number_ =
      settings.value(POMODOROS_NUMBER_KEY, DEFAULT_POMODOROS_NUMBER).toUInt();

  // print out loaded values
  for (auto &pair : time_values_) {
    qDebug() << "SettingsManager: loadFromFile/ " << modeAsString(pair.first)
             << " = " << pair.second;
  }
  qDebug() << "SettingsManager: loadFromFile/ pomodoros_number = "
           << pomodoros_number_;
}

uint16_t SettingsManager::getTimeValueForMode(Mode mode) const {
  uint16_t result{};
  auto it = time_values_.find(mode);
  if (it != time_values_.end())
    result = it->second;
  else
    result = defaultTimeValueForMode(mode);

  qDebug() << "SettingsManager: getTimeValueForMode/ mode = "
           << modeAsString(mode) << "/ value = " << QString::number(result);
  return result;
}

uint16_t SettingsManager::getPomodorosNumber() const {
  uint16_t result{};
  if (pomodoros_number_ > 0)
    result = pomodoros_number_;
  else
    result = DEFAULT_POMODOROS_NUMBER;

  qDebug() << "SettingsManager: getPomodorosNumber/ pomodoros_number = "
           << QString::number(result);
  return result;
}
