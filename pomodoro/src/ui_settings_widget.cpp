#include "ui_settings_widget.h"
#include "common.h"
#include "isettings_manager.h"
#include "ui_preferences_widget.h"

SettingsWidget::SettingsWidget(QWidget* parent,
                               ISettingsManager* settings_manager)
    : QWidget(parent),
      ui(new Ui::SettingsWidget),
      settings_manager_{settings_manager} {
  ui->setupUi(this);
  QObject::connect(ui->saveButton, SIGNAL(clicked(bool)), this, SLOT(save()));
  QObject::connect(ui->cancelButton, SIGNAL(clicked(bool)), this,
                   SLOT(cancel()));
  QObject::connect(dynamic_cast<QObject*>(settings_manager_),
                   SIGNAL(emitSettingsValuesChanged), this,
                   SLOT(onLoadSettings()));

  ui->workTimeSlider->setValue(WORK_DEFAULT_TIME);
  ui->shortTimeSlider->setValue(SHORT_BREAK_DEFAULT_TIME);
  ui->longTimeSlider->setValue(LONG_BREAK_DEFAULT_TIME);
  ui->pomodorosSlider->setValue(DEFAULT_POMODOROS_NUMBER);
}

SettingsWidget::~SettingsWidget() { delete ui; }

settings_values SettingsWidget::dumpTimes() {
  settings_values result;
  result[Mode::WORK] = ui->workTimeValue->text().toUInt();
  result[Mode::SHORT_BREAK] = ui->shortTimeValue->text().toUInt();
  result[Mode::LONG_BREAK] = ui->longTimeValue->text().toUInt();
  return result;
}

uint16_t SettingsWidget::dumpPomodoros() {
  return ui->pomodorosValue->text().toUInt();
}

void SettingsWidget::save() {
  auto time_values = dumpTimes();
  auto pomodoros_number = dumpPomodoros();

  settings_manager_->changeValues(time_values, pomodoros_number);
  settings_manager_->saveToFile(DEFAULT_SETTINGS_FILE);

  this->close();
}

void SettingsWidget::cancel() { this->close(); }

void SettingsWidget::onLoadSettings() {
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
  ui->workTimeValue->setText(QString::number(value));
}

void SettingsWidget::on_shortTimeSlider_valueChanged(int value) {
  ui->shortTimeValue->setText(QString::number(value));
}

void SettingsWidget::on_longTimeSlider_valueChanged(int value) {
  ui->shortTimeValue->setText(QString::number(value));
}

void SettingsWidget::on_pomodorosSlider_valueChanged(int value) {
  ui->shortTimeValue->setText(QString::number(value));
}