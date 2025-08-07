#include "mainwindow.hh"
#include "ui_simplemainwindow.h"
#include "city.hh"
#include "actorgui.hh"
#include <QDebug>

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
    timer->start(tick_);
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
    actors_.push_back(nActor);
    map->addItem(nActor);
    last_ = nActor;
}

void SimpleMainWindow::updateCoords(int nX, int nY)
{
    last_->setCoord(nX, nY);
}

void SimpleMainWindow::setPicture(QImage &img)
{
    map->setBackgroundBrush(img);
}

void SimpleMainWindow::drawAllActors()
{
     // Clear existing actors first
     for (auto actor : actors_) {
         map->removeItem(actor);
        delete actor;
    }
    actors_.clear();

    // Get all actors from the city and draw them
    auto allActors = city_->getActors();

    for (auto const &actor : allActors) {
        // Check actor type. Use dynamic_cast.
        if (std::dynamic_pointer_cast<Interface::IVehicle>(actor)) {
            Interface::Location loc = actor->giveLocation();
            addActor(loc.giveX(), loc.giveY(), BUS_TYPE);
        }
        else if (std::dynamic_pointer_cast<Interface::IPassenger>(actor)) {
            auto passenger = std::dynamic_pointer_cast<Interface::IPassenger>(actor);
            if (!passenger->isInVehicle()){
                Interface::Location loc = actor->giveLocation();
                addActor(loc.giveX(), loc.giveY(), PASSENGER_TYPE);
            }
        }
    }
}

void SimpleMainWindow::drawStops()
{

}

void SimpleMainWindow::updateAllActorPositions()
{
    auto allActors = city_->getActors();

    // // Make sure we have the same number of GUI actors as city actors
    // if (actors_.size() != allActors.size()) {
    //     drawAllActors(); // Redraw if counts don't match
    //     return;
    // }

    // Update positions of existing GUI actors
    for (size_t i = 0; i < actors_.size() && i < allActors.size(); ++i) {
        Interface::Location loc = allActors[i]->giveLocation();
        actors_[i]->setCoord(loc.giveX(), loc.giveY());
    }
}

void StudentSide::SimpleMainWindow::on_startButton_clicked()
{
    qDebug() << "Start clicked";
    drawAllActors(); // Draw all actors when game starts
    emit gameStarted();
}
} //namespace
