#include "pomodoro_view.h"
#include "ui_pomodoro_view.h"

PomodoroView::PomodoroView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PomodoroView)
{
    ui->setupUi(this);
}

PomodoroView::~PomodoroView()
{
    delete ui;
}
