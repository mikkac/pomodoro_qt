#include "pomodoro_view.h"
#include <QDateTime>
#include <QDebug>
#include <QSystemTrayIcon>
#include "ui_pomodoro_view.h"

PomodoroView::PomodoroView(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::PomodoroView) {
  qDebug() << "PomodoroView: ctor";
  ui->setupUi(this);
}

PomodoroView::~PomodoroView() { delete ui; }

void PomodoroView::setModel(IPomodoroModel* model) {
  qDebug() << "PomodoroView: setModel";
  model_ = model;
  QObject::connect(dynamic_cast<QObject*>(model_),
                   SIGNAL(emitNewTimerValue(uint16_t)), this,
                   SLOT(on_timerValueChanged(uint16_t)));
  QObject::connect(dynamic_cast<QObject*>(model_),
                   SIGNAL(emitNewModeValue(Mode)), this,
                   SLOT(on_modeValueChanged(Mode)));
  model->reloadValues();
}

void PomodoroView::setSettingsWidget(SettingsWidget* settings) {
  qDebug() << "PomodoroView: setSettingsWidget";
  settings_ = settings;
  QObject::connect(dynamic_cast<QObject*>(ui->actionPreferences),
                   SIGNAL(triggered(bool)), this, SLOT(on_settingsEntered()));
}

void PomodoroView::on_startButton_clicked() {
  qDebug() << "PomodoroView: on_startButton_clicked";
  if (!is_started)
    start();
  else if (!is_paused)
    pause();

  ui->stopButton->setEnabled(true);
}

void PomodoroView::on_stopButton_clicked() {
  qDebug() << "PomodoroView: on_stopButton_clicked";
  if (is_started || is_paused) stop();
}

void PomodoroView::on_timerValueChanged(uint16_t seconds) {
  ui->timerLabel->setText(formatTime(seconds));
}

void PomodoroView::on_modeValueChanged(Mode mode) {
  qDebug() << "PomodoroView: on_modeValueChanged/ old_mode = "
           << ui->modeLabel->text() << "/ new_mode = " << modeAsString(mode);
  QString display_value{};
  QString display_message{};
  switch (mode) {
    case Mode::WORK:
      display_value = "Work";
      display_message = "It's time to work!";
      if (is_started) pause();
      break;
    case Mode::SHORT_BREAK:
      display_value = "Short break";
      display_message = "Take a short break!";
      if (is_started) pause();
      break;
    case Mode::LONG_BREAK:
      display_value = "Long break";
      display_message = "Take a long break!";
      if (is_started) pause();
      break;
    default:
      display_value = "Unknown";
      display_message = "Unknown";
  }
  if (display_value != ui->modeLabel->text()) {
    informAboutModeChange(display_message);
    ui->modeLabel->setText(display_value);
  }
}

void PomodoroView::on_settingsEntered() {
  qDebug() << "PomodoroView: on_settingsEntered";
  if (settings_) settings_->show();
}

void PomodoroView::start() {
  qDebug() << "PomodoroView: start";
  model_->start();
  ui->startButton->setText("Pause");
  is_started = true;
  is_paused = false;
}

void PomodoroView::pause() {
  qDebug() << "PomodoroView: pause";
  model_->pause();
  ui->startButton->setText("Start");
  is_started = false;
  is_paused = true;
}

void PomodoroView::stop() {
  qDebug() << "PomodoroView: stop";
  ui->stopButton->setEnabled(false);
  model_->stop();
  ui->startButton->setText("Start");
  is_started = false;
  is_paused = false;
}

void PomodoroView::informAboutModeChange(const QString& message) {
  qDebug() << "PomodoroView: informAboutModeChange/ message = " << message;
  auto notification = new QSystemTrayIcon(this);
  if (notification->isSystemTrayAvailable()) {
    notification->setIcon(
        QIcon::fromTheme("phone"));  // TODO change to custom icon
    notification->setVisible(true);
    notification->showMessage("Pomodoro", message);
  }
}
