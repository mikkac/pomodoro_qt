#ifndef POMODORO_VIEW_H
#define POMODORO_VIEW_H

#include <QWidget>

namespace Ui {
class PomodoroView;
}

class PomodoroView : public QWidget
{
    Q_OBJECT

public:
    explicit PomodoroView(QWidget *parent = 0);
    ~PomodoroView();

private:
    Ui::PomodoroView *ui;
};

#endif // POMODORO_VIEW_H
