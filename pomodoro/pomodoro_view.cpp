#include "pomodoro_view.h"
#include "ui_pomodoro_view.h"

PomodoroView::PomodoroView(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::PomodoroView) {
  qDebug() << "PomodoroView: ctor";
  ui->setupUi(this);
}

PomodoroView::~PomodoroView() { delete ui; }

void PomodoroView::setModel(IPomodoroModel* model) {
  model_ = model;
  QObject::connect(dynamic_cast<QObject*>(model),
                   SIGNAL(emitNewTimerValue(uint16_t)), this,
                   SLOT(on_timerValueChanged(uint16_t)));
  QObject::connect(dynamic_cast<QObject*>(model),
                   SIGNAL(emitNewModeValue(Mode)), this,
                   SLOT(on_modeValueChanged(Mode)));
  model->reloadValues();
  qDebug() << "PomodoroView: setModel";
}

void PomodoroView::on_startButton_clicked() {
  if (!is_started)
    start();
  else if (!is_paused)
    pause();

  ui->stopButton->setEnabled(true);
}

void PomodoroView::on_stopButton_clicked() {
  if (is_started || is_paused) stop();
}

void PomodoroView::on_timerValueChanged(uint16_t seconds) {
  ui->timerLabel->setText(QString::number(seconds));
}

void PomodoroView::on_modeValueChanged(Mode mode) {
  QString display_value{};
  switch (mode) {
    case Mode::WORK:
      display_value = "Work";
      if (is_started) pause();
      break;
    case Mode::SHORT_BREAK:
      display_value = "Short break";

      if (is_started) pause();
      break;
    case Mode::LONG_BREAK:
      display_value = "Long break";
      if (is_started) pause();
      break;
    default:
      display_value = "Unknown";
  }
  qDebug() << "PomodoroView: mode to set: " << display_value;
  ui->modeLabel->setText(display_value);
}

void PomodoroView::start() {
  model_->start();
  ui->startButton->setText("Pause");
  is_started = true;
  is_paused = false;
}

void PomodoroView::pause() {
  model_->pause();
  ui->startButton->setText("Start");
  is_started = false;
  is_paused = true;
}

void PomodoroView::stop() {
  ui->stopButton->setEnabled(false);
  model_->stop();
  ui->startButton->setText("Start");
  is_started = false;
  is_paused = false;
}
