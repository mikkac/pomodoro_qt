#ifndef POMODORO_VIEW_H
#define POMODORO_VIEW_H

#include <QDebug>
#include <QWidget>
#include "ipomodoro_model.h"

namespace Ui {
class PomodoroView;
}

class PomodoroView : public QWidget {
  Q_OBJECT

 public:
  explicit PomodoroView(QWidget* parent = nullptr);
  ~PomodoroView();

  void setModel(IPomodoroModel* model);

 private slots:
  void on_startButton_clicked();
  void on_stopButton_clicked();
  void on_timerValueChanged(uint16_t seconds);
  void on_modeValueChanged(Mode mode);

 private:
  Ui::PomodoroView* ui;
  IPomodoroModel* model_{};
  bool is_started{false};
  bool is_paused{false};
};

#endif  // POMODORO_VIEW_H
