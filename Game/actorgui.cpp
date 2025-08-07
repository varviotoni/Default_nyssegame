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
        this->setZValue(10);
        // Draw a black rectangle for type 0
        painter->setBrush(Qt::blue);
    }
    // Passenger
    else if (type_ == 1) {
        this->setZValue(5);
        painter->setBrush(Qt::red);
    }
    // Stop
    else if (type_ == 2) {
        this->setZValue(0);
        painter->setBrush(Qt::green);
    }
    painter->drawEllipse(bounds);
}

void ActorGUI::setCoord(int x, int y)
{
    setX( x );
    setY( y );
}

} //namespace
