#include "actorgui.hh"

namespace StudentSide
{

ActorGUI::ActorGUI(int x, int y, int type): CourseSide::SimpleActorItem(x, y, type), x_(x), y_(y), type_(type)
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
    QColor color(type_%256, type_%256, type_%256);
    QBrush brush(color);
    painter->setBrush(brush);
    painter->drawEllipse(bounds);
}

void ActorGUI::setCoord(int x, int y)
{
    setX( x );
    setY( y );
}

void ActorGUI::advance(int step)
{
    if (step == 0) {
        // Phase 0: Calculate next state
        // No additional logic needed here for now
        // This is where you would typically update the actor's state based on game logic
        //nextX = x();
        //nextY = y();
        return;
    }
    else if (step == 1) {
        // Phase 1: Update position/animation
        // No additional logic needed here for now
        setCoord(x_, y_);
        return;
    }
    // Phase 1: Update position/animation
    // Add your animation logic here if needed
}
} //namespace
