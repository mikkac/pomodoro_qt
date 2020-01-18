#ifndef POMODORO_VIEW_H
#define POMODORO_VIEW_H

#include <QDebug>
#include <QMainWindow>
#include "ipomodoro_model.h"
#include "settings_widget.h"

namespace Ui {
class PomodoroView;
}

class PomodoroView : public QMainWindow {
  Q_OBJECT

 public:
  explicit PomodoroView(QWidget* parent = nullptr);
  ~PomodoroView();

  void setModel(IPomodoroModel* model);
  void setSettingsWidget(SettingsWidget* settings);

 private slots:
  void on_startButton_clicked();
  void on_stopButton_clicked();
  void on_timerValueChanged(uint16_t seconds);
  void on_modeValueChanged(Mode mode);
  void on_settingsEntered();

 private:
  void start();
  void pause();
  void stop();
  QString formatTime(uint16_t seconds) const;
  void informAboutModeChange(const QString& message);

 private:
  Ui::PomodoroView* ui;
  IPomodoroModel* model_{};
  SettingsWidget* settings_{};
  bool is_started{false};
  bool is_paused{false};
};

#endif  // POMODORO_VIEW_H
