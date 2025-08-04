#ifndef ActorGUI_HH
#define ActorGUI_HH
#include "graphics/simpleactoritem.hh"

namespace StudentSide
{

class ActorGUI : public CourseSide::SimpleActorItem
{
public:
    ActorGUI();
    // Brief destructor
    ~ActorGUI();

    // QGraphicsItem interface
public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};
} // namespace
#endif // ActorGUI_HH
