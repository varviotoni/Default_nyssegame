#include <QApplication>
#include "graphics/simplemainwindow.hh"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Q_INIT_RESOURCE(offlinedata);
    CourseSide::SimpleMainWindow mainwindow;
    mainwindow.show();

    return a.exec();
}
