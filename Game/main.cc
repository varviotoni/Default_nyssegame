#include <QApplication>
#include "mainwindow.hh"
#include "city.hh"
#include "creategame.hh"
#include "core/logic.hh"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Q_INIT_RESOURCE(offlinedata);
    auto icity=Interface::createGame();

    std::shared_ptr<StudentSide::City> city =
        std::dynamic_pointer_cast<StudentSide::City>(icity);

    StudentSide::SimpleMainWindow mainwindow(city);
    auto logic = new CourseSide::Logic();
    logic->takeCity(icity);
    logic->fileConfig();
    logic->setTime(10,0);
    logic->finalizeGameStart();
    mainwindow.show();

    return a.exec();
}
