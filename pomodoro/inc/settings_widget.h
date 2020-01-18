#ifndef PREFERENCES_WIDGET_H
#define PREFERENCES_WIDGET_H

#include <QWidget>
#include <map>
#include "isettings_manager.h"

namespace Ui {
class SettingsWidget;
}

class SettingsWidget : public QWidget {
  Q_OBJECT

 public:
  explicit SettingsWidget(QWidget *parent = nullptr,
                          ISettingsManager *settings_manager = nullptr);
  ~SettingsWidget();

  settings_values dumpTimes();
  uint16_t dumpPomodoros();

 private slots:
  void save();
  void cancel();

 private:
  Ui::SettingsWidget *ui;
  ISettingsManager *settings_manager_{};
};

#endif  // PREFERENCES_WIDGET_H
