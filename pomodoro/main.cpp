#include <QApplication>
#include "ipomodoro_model.h"
#include "itimer.h"
#include "pomodoro_model.h"
#include "pomodoro_view.h"
#include "timer.h"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  PomodoroView w;
  w.show();
  ITimer* timer = new Timer(&w);
  IPomodoroModel* model = new PomodoroModel(&w, timer);
  w.setModel(model);
  return a.exec();
}
