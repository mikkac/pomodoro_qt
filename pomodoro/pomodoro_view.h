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

  void setModel(IPomodoroModel* model) {
    model_ = model;
    qDebug() << "PomodoroView: setModel";
  }

 private:
  Ui::PomodoroView* ui;
  IPomodoroModel* model_{};
};

#endif  // POMODORO_VIEW_H
