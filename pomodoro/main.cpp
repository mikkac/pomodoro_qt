#include <QApplication>
#include "imode_manager.h"
#include "ipomodoro_model.h"
#include "itimer.h"
#include "mode_manager.h"
#include "pomodoro_model.h"
#include "pomodoro_view.h"
#include "settings_manager.h"
#include "settings_widget.h"
#include "timer.h"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  PomodoroView w;
  w.show();
  ISettingsManager* settings_manager = new SettingsManager(&w);
  SettingsWidget* settings_widget =
      new SettingsWidget(nullptr, settings_manager);
  // new SettingsWidget(nullptr, settings_manager);
  ITimer* timer = new Timer(&w);
  IModeManager* mode_manager = new ModeManager(0, &w);
  IPomodoroModel* model =
      new PomodoroModel(&w, timer, mode_manager, settings_manager);
  w.setModel(model);
  w.setSettingsWidget(settings_widget);
  return a.exec();
  // TODO
  // * zeby nie wyswietalo sie okienko po wlaczeniu
  // * zmienic textedit na suwaki
}
