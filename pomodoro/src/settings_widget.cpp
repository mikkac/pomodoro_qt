#include "settings_widget.h"
#include "common.h"
#include "isettings_manager.h"
#include "ui_preferences_widget.h"

SettingsWidget::SettingsWidget(QWidget* parent,
                               ISettingsManager* settings_manager)
    : QWidget(parent),
      ui(new Ui::SettingsWidget),
      settings_manager_{settings_manager} {
  ui->setupUi(this);
  QObject::connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(save()));
  QObject::connect(ui->pushButton_2, SIGNAL(clicked(bool)), this,
                   SLOT(cancel()));
}

SettingsWidget::~SettingsWidget() { delete ui; }

settings_values SettingsWidget::dumpTimes() {
  settings_values result;
  result[Mode::WORK] = ui->textEdit->toPlainText().toUInt();
  result[Mode::SHORT_BREAK] = ui->textEdit_2->toPlainText().toUInt();
  result[Mode::LONG_BREAK] = ui->textEdit_3->toPlainText().toUInt();
  return result;
}

uint16_t SettingsWidget::dumpPomodoros() {
  return ui->textEdit_4->toPlainText().toUInt();
}

void SettingsWidget::save() {
  auto time_values = dumpTimes();
  auto pomodoros_number = dumpPomodoros();

  settings_manager_->changeValues(time_values, pomodoros_number);
  settings_manager_->saveToFile(DEFAULT_SETTINGS_FILE);

  this->close();
}

void SettingsWidget::cancel() { this->close(); }
