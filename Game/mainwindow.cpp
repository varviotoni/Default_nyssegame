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
    connect(timer, &QTimer::timeout, map, &QGraphicsScene::advance);
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
    auto allActors = city_->actors_; // You'll need this method in City class

    for (const auto& actor : allActors) {
        Interface::Location loc = actor->giveLocation();
        int type = 0; // You might need to add a method to get actor type
        addActor(loc.giveX(), loc.giveY(), type);
    }
}




void StudentSide::SimpleMainWindow::on_startButton_clicked()
{
    qDebug() << "Start clicked";
    emit gameStarted();
}
} //namespace
