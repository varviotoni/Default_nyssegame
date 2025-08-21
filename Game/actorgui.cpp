#include "actorgui.hh"

namespace StudentSide
{

ActorGUI::ActorGUI(int x, int y, int type):
    CourseSide::SimpleActorItem(x, y, type),
    x_(x),
    y_(y),
    type_(type),
    num_passengers_(0)
{
    setPos(mapToParent(x_, y_));
}
// Virtual destructor
ActorGUI::~ActorGUI()
{

}

QRectF ActorGUI::boundingRect() const
{
    return QRectF(0, 0, BOUNDS_WIDTH, BOUNDS_HEIGHT);
}

void ActorGUI::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    QRectF bounds = boundingRect();
    // Set the color based on the type
    // Bus
    if (type_ == 0) {
        // Set Z value for bus to be on top
        this->setZValue(2);
        QImage busImage(":offlinedata/bus.png");
        painter->drawImage(bounds, busImage);
        QString num_passengers = QString::number(num_passengers_);
        painter->drawText(bounds.center(), num_passengers);
        // painter->setBrush(Qt::blue);
    }
    // Passenger
    else if (type_ == 1) {
        QRectF pas_bounds = QRectF(0,0,BOUNDS_WIDTH/4,BOUNDS_HEIGHT/4);
        this->setZValue(1);
        painter->setBrush(Qt::red);
        painter->drawEllipse(pas_bounds);
    }
    // Stop
    else if (type_ == 2) {
        QRectF stop_bounds = QRectF(0,0,BOUNDS_WIDTH/2,BOUNDS_HEIGHT/2);
        this->setZValue(0);
        QImage stopImage(":offlinedata/stop.png");
        painter->drawImage(stop_bounds, stopImage);
        // painter->setBrush(Qt::green);
    }
    // Player
    else if (type_ == 3){
        QRectF player_bounds = QRectF(0,0,BOUNDS_WIDTH/2,BOUNDS_HEIGHT/2);
        this->setZValue(3);
        QImage playerImage(":offlinedata/player.png");
        painter->drawImage(player_bounds, playerImage);
    }
}

void ActorGUI::setCoord(int x, int y)
{
    setX( x );
    setY( y );
}

void ActorGUI::setPassengers(int p)
{
    num_passengers_=p;
}

} //namespace
