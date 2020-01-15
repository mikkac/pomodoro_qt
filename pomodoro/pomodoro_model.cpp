#include "pomodoro_model.h"

void PomodoroModel::setMode(Mode mode) {
  qDebug() << "PomodoroModel: setMode = " << QString(static_cast<int>(mode));
}

void PomodoroModel::start() { qDebug() << "PomodoroModel: start"; }

void PomodoroModel::pause() { qDebug() << "PomodoroModel: pause"; }

void PomodoroModel::stop() { qDebug() << "PomodoroModel: stop"; }
