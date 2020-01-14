#include "pomodoro_view.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PomodoroView w;
    w.show();

    return a.exec();
}
