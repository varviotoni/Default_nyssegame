#ifndef SIMPLEMAINWINDOW_HH
#define SIMPLEMAINWINDOW_HH

#include "interfaces/iactor.hh"
#include "graphics/simpleactoritem.hh"
#include "city.hh"
#include "actorgui.hh"
#include "player.hh"

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <iostream>
#include <memory>
#include <QVector>
#include <map>

namespace Ui {
class SimpleMainWindow;
}

namespace StudentSide {

class SimpleMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SimpleMainWindow(std::shared_ptr<StudentSide::City> city, QWidget *parent = 0);
    virtual ~SimpleMainWindow();

    void setSize(int w, int h);
    void setTick(int t);

    void addActor(int locX, int locY, int type = 0, int num_passengers=0);
    void updateCoords(int nX, int nY);
    void setPicture(QImage &img);
    void drawStops();
    void updateAllActorPositions();
    void spawnPlayerGUI(Interface::Location);

signals:
    void gameStarted();

private slots:
    void on_startButton_clicked();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::SimpleMainWindow *ui;
    std::shared_ptr<StudentSide::City> city_;
    QGraphicsScene *map;
    QTimer *timer;
    QVector<ActorGUI*> actors_;
    QVector<ActorGUI*> stops_;
    std::vector<StudentSide::ActorGUI*> actor_pool_;
    std::vector<StudentSide::ActorGUI*> stop_pool_;
    // std::shared_ptr<ActorGUI*> player_gui_;
    QVector<ActorGUI*> player_gui_;
    std::shared_ptr<StudentSide::Player> player_;
    CourseSide::SimpleActorItem* last_;

    int width_ =1050; //pxls
    int height_ = 500;
    int tick_ = 150; //ms
    const int BUS_TYPE = 0;
    const int PASSENGER_TYPE = 1;
    const int STOP_TYPE = 2;
    const int PLAYER_TYPE = 3;
};

} //namespace
#endif // SIMPLEMAINWINDOW_HH
