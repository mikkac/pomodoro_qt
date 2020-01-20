#ifndef SETTINGS_WIDGET_H
#define SETTINGS_WIDGET_H

#include <QWidget>
#include "isettings_manager.h"

namespace Ui {
class SettingsWidget;
}

class SettingsWidget : public QWidget {
  Q_OBJECT

 public:
  explicit SettingsWidget(QWidget *parent = 0,
                          ISettingsManager *settings_manager = nullptr);
  ~SettingsWidget();

  settings_values dumpTimes();
  uint16_t dumpPomodoros();

 private:
  void loadSettings();

 private slots:
  void save();
  void cancel();
  void on_workTimeSlider_valueChanged(int value);

  void on_shortTimeSlider_valueChanged(int value);

  void on_longTimeSlider_valueChanged(int value);

  void on_pomodorosSlider_valueChanged(int value);

 private:
  Ui::SettingsWidget *ui;
  ISettingsManager *settings_manager_{};
};

#endif  // SETTINGS_WIDGET_H
