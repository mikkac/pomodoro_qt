#include "settings_widget.h"
#include "common.h"
#include "ui_settings_widget.h"

SettingsWidget::SettingsWidget(QWidget* parent,
                               ISettingsManager* settings_manager)
    : QWidget(parent),
      ui(new Ui::SettingsWidget),
      settings_manager_{settings_manager} {
  qDebug() << "SettingsWidget: ctor";
  ui->setupUi(this);
  QObject::connect(ui->saveButton, SIGNAL(clicked(bool)), this, SLOT(save()));
  QObject::connect(ui->cancelButton, SIGNAL(clicked(bool)), this,
                   SLOT(cancel()));
  loadSettings();
}

SettingsWidget::~SettingsWidget() { delete ui; }

settings_values SettingsWidget::dumpTimes() {
  qDebug() << "SettingsWidget: dumpTimes";
  settings_values result;
  result[Mode::WORK] = ui->workTimeValue->text().toUInt();
  result[Mode::SHORT_BREAK] = ui->shortTimeValue->text().toUInt();
  result[Mode::LONG_BREAK] = ui->longTimeValue->text().toUInt();
  return result;
}

uint16_t SettingsWidget::dumpPomodoros() {
  qDebug() << "SettingsWidget: dumpPomodoros (pomodoros before long break)";
  return ui->pomodorosValue->text().toUInt();
}

void SettingsWidget::save() {
  qDebug() << "SettingsWidget: save";
  auto time_values = dumpTimes();
  auto pomodoros_number = dumpPomodoros();

  settings_manager_->changeValues(time_values, pomodoros_number);
  settings_manager_->saveToFile(DEFAULT_SETTINGS_FILE);

  this->close();
}

void SettingsWidget::cancel() {
  qDebug() << "SettingsWidget: cancel";
  this->close();
}

void SettingsWidget::loadSettings() {
  qDebug() << "SettingsWidget: loadSettings";
  auto time_value = settings_manager_->getTimeValueForMode(Mode::WORK);
  ui->workTimeSlider->setValue(time_value);
  ui->workTimeValue->setText(QString::number(time_value));

  time_value = settings_manager_->getTimeValueForMode(Mode::SHORT_BREAK);
  ui->shortTimeSlider->setValue(time_value);
  ui->shortTimeValue->setText(QString::number(time_value));

  time_value = settings_manager_->getTimeValueForMode(Mode::LONG_BREAK);
  ui->longTimeSlider->setValue(time_value);
  ui->shortTimeValue->setText(QString::number(time_value));

  auto pomodoros_number = settings_manager_->getPomodorosNumber();
  ui->pomodorosSlider->setValue(pomodoros_number);
  ui->pomodorosValue->setText(QString::number(pomodoros_number));
}

void SettingsWidget::on_workTimeSlider_valueChanged(int value) {
  qDebug() << "SettingsWidget: on_workTimeSlider_valueChanged";
  ui->workTimeValue->setText(QString::number(value));
}

void SettingsWidget::on_shortTimeSlider_valueChanged(int value) {
  qDebug() << "SettingsWidget: on_shortTimeSlider_valueChanged";
  ui->shortTimeValue->setText(QString::number(value));
}

void SettingsWidget::on_longTimeSlider_valueChanged(int value) {
  qDebug() << "SettingsWidget: on_longTimeSlider_valueChanged";
  ui->longTimeValue->setText(QString::number(value));
}

void SettingsWidget::on_pomodorosSlider_valueChanged(int value) {
  qDebug() << "SettingsWidget: on_pomodorosSlider_valueChanged";
  ui->pomodorosValue->setText(QString::number(value));
}
