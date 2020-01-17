#include "settings_widget.h"
#include "isettings_manager.h"
#include "ui_preferences_widget.h"

SettingsWidget::SettingsWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::SettingsWidget) {
  ui->setupUi(this);
}

SettingsWidget::~SettingsWidget() { delete ui; }
