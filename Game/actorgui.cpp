#include "actorgui.hh"

namespace StudentSide
{

ActorGUI::ActorGUI(int x, int y, int type):
    CourseSide::SimpleActorItem(x, y, type),
    x_(x),
    y_(y),
    type_(type)
{
    setPos(mapToParent(x_, y_));
}
// Virtual destructor
ActorGUI::~ActorGUI()
{

}

QRectF ActorGUI::boundingRect() const
{
    return QRectF(0, 0, WIDTH, HEIGHT);
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
        // painter->setBrush(Qt::blue);
    }
    // Passenger
    else if (type_ == 1) {
        QRectF pas_bounds = QRectF(0,0,WIDTH/2,HEIGHT/2);
        this->setZValue(1);
        painter->setBrush(Qt::red);
        painter->drawEllipse(pas_bounds);
    }
    // Stop
    else if (type_ == 2) {
        this->setZValue(0);
        QImage stopImage(":offlinedata/stop.png");
        painter->drawImage(bounds, stopImage);
        // painter->setBrush(Qt::green);
    }
    // Player
    else if (type_ == 3){
        this->setZValue(4);
      //QImage playerImage(":offlinedata/player.png");
      //painter->drawImage(bounds, playerImage);
        painter->setBrush(Qt::green);
        painter->drawEllipse(bounds);
        //qDebug() << "draw player";
    }
}

void ActorGUI::setCoord(int x, int y)
{
    setX( x );
    setY( y );
}

} //namespace
