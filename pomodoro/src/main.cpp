#include <QApplication>
#include "imode_manager.h"
#include "ipomodoro_model.h"
#include "itimer.h"
#include "mode_manager.h"
#include "pomodoro_model.h"
#include "pomodoro_view.h"
#include "settings_widget.h"
#include "timer.h"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  PomodoroView w;
  w.show();
  SettingsWidget* settings = new SettingsWidget(nullptr);
  ITimer* timer = new Timer(&w);
  IModeManager* mode_manager = new ModeManager(0, &w);
  IPomodoroModel* model = new PomodoroModel(&w, timer, mode_manager);
  w.setModel(model);
  w.setSettingsWidget(settings);
  return a.exec();
}
