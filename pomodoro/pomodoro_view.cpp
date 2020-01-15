#include "pomodoro_view.h"
#include "ui_pomodoro_view.h"

PomodoroView::PomodoroView(QWidget *parent)
    : QWidget(parent), ui(new Ui::PomodoroView) {
  qDebug() << "PomodoroView: ctor";
  ui->setupUi(this);
}

PomodoroView::~PomodoroView() { delete ui; }

void PomodoroView::on_startButton_clicked() {
  if (!is_started) {
    model_->start();
    ui->startButton->setText("Pause");
    is_started = true;
    is_paused = false;
  } else if (!is_paused) {
    model_->pause();
    ui->startButton->setText("Start");
    is_started = false;
    is_paused = true;
  }
  ui->stopButton->setEnabled(true);
}

void PomodoroView::on_stopButton_clicked() {
  if (is_started || is_paused) {
    ui->stopButton->setEnabled(false);
    model_->stop();
    ui->startButton->setText("Start");
    is_started = false;
    is_paused = false;
  }
}
