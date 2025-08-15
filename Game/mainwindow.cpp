#include "mainwindow.hh"
#include "ui_simplemainwindow.h"
#include "city.hh"
#include "actorgui.hh"
#include <QDebug>
#include <QKeyEvent>

const int PADDING = 10;

namespace StudentSide {

SimpleMainWindow::SimpleMainWindow(std::shared_ptr<StudentSide::City> city, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SimpleMainWindow),
    city_(city)
{
    ui->setupUi(this);
    ui->gameView->setFixedSize(width_, height_);
    ui->centralwidget->setFixedSize(width_ + ui->startButton->width() + PADDING, height_ + PADDING);

    ui->startButton->move(width_ + PADDING , PADDING);

    map = new QGraphicsScene(this);
    ui->gameView->setScene(map);
    map->setSceneRect(0,0,width_,height_);
    map->sceneRect();
    this->setPicture(city_->background_);

    resize(minimumSizeHint());
    //ui->gameView->fitInView(0,0, MAPWIDTH, MAPHEIGHT, Qt::KeepAspectRatio);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &SimpleMainWindow::updateAllActorPositions);
    // timer->start(tick_);
}

SimpleMainWindow::~SimpleMainWindow()
{
    delete ui;
}

void SimpleMainWindow::setSize(int w, int h)
{
    width_ = w;
    height_ = h;
}

void SimpleMainWindow::setTick(int t)
{
    tick_ = t;
}

void SimpleMainWindow::addActor(int locX, int locY, int type)
{
    StudentSide::ActorGUI* nActor = new StudentSide::ActorGUI(locX, locY, type);
    if (type == 0 || type == 1 ){
        actors_.push_back(nActor);
        map->addItem(nActor);
        //last_ = nActor;
    }
    if (type == 2){
        stops_.push_back(nActor);
        map->addItem(nActor);
    }
}

void SimpleMainWindow::updateCoords(int nX, int nY)
{
    last_->setCoord(nX, nY);
}

void SimpleMainWindow::setPicture(QImage &img)
{
    map->setBackgroundBrush(img);
}


void SimpleMainWindow::drawStops()
{
    for (auto const &stop : stops_){
        map->removeItem(stop);
        delete stop;
    }
    stops_.clear();
    auto allStops = city_->getStops();
    for (auto const &stop : allStops){
        Interface::Location loc = stop->getLocation();
        addActor(loc.giveX(),loc.giveY(),STOP_TYPE);
    }
    for (auto i = 0; i < stops_.size() && i < allStops.size(); ++i){
        Interface::Location loc = allStops[i]->getLocation();
        stops_[i]->setCoord(loc.giveX(), loc.giveY());
    }
}

void SimpleMainWindow::updateAllActorPositions()
{
    for (auto const &actor : actors_){
        map->removeItem(actor);
        delete actor;
    }
    actors_.clear();
    auto allActors = city_->getActors();

    for (auto const &actor : allActors) {
        // Check actor if bus type. Use dynamic_cast.
        if (std::dynamic_pointer_cast<Interface::IVehicle>(actor)){
            Interface::Location loc = actor->giveLocation();
            addActor(loc.giveX(), loc.giveY(), BUS_TYPE);
        }
    }

    // Update positions of existing busses and passenger actors
    for (size_t i = 0; i < actors_.size() && i < allActors.size(); ++i) {
        Interface::Location loc = allActors[i]->giveLocation();
        actors_[i]->setCoord(loc.giveX(), loc.giveY());
    }
    // handle player actor update
    Interface::Location loc = player_->giveLocation();
    // player_gui_[0]->setCoord(loc.giveX(),loc.giveY());
    if (!player_gui_.empty()) {
        player_gui_[0]->setCoord(loc.giveX(), loc.giveY());
    }
}

void SimpleMainWindow::spawnPlayerGUI(Interface::Location start_loc)
{
    player_=city_->getPlayer();
    StudentSide::ActorGUI* player_gui = new StudentSide::ActorGUI(start_loc.giveX(), start_loc.giveY(), PLAYER_TYPE);
    player_gui_.push_back(player_gui);
    map->addItem(player_gui_[0]);
}


void StudentSide::SimpleMainWindow::on_startButton_clicked()
{
    qDebug() << "Start clicked";

    drawStops();
    spawnPlayerGUI(PLAYER_START_LOC);
    timer->start(tick_);
    emit gameStarted();
}

void SimpleMainWindow::keyPressEvent(QKeyEvent *event)
{
    if (!player_) {
        QMainWindow::keyPressEvent(event);
        return;
    }

    Interface::Location currentLoc = player_->giveLocation();
    int x = currentLoc.giveX();
    int y = currentLoc.giveY();

    const int MOVE_STEP = 10;

    switch (event->key()) {
        case Qt::Key_W:
            y -= MOVE_STEP;
            break;
        case Qt::Key_S:
            y += MOVE_STEP;
            break;
        case Qt::Key_A:
            x -= MOVE_STEP;
            break;
        case Qt::Key_D:
            x += MOVE_STEP;
            break;
        default:
            QMainWindow::keyPressEvent(event);
            return;
    }

    // Boundary checking to keep player within game area
    x = std::max(0, std::min(x, width_ - 30));
    y = std::max(0, std::min(y, height_ -30));

    // Update player location
    Interface::Location newLoc;
    newLoc.setXY(x, y);
    player_->move(newLoc);

    event->accept();
}
} //namespace
