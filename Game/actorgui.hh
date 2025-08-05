#ifndef ActorGUI_HH
#define ActorGUI_HH
#include "graphics/simpleactoritem.hh"

namespace StudentSide
{
const int WIDTH = 15;
const int HEIGHT = 15;

class ActorGUI : public CourseSide::SimpleActorItem
{
public:
    ActorGUI(int x, int y, int type = 0);
    // Brief destructor
    ~ActorGUI();

    // QGraphicsItem interface
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setCoord(int x, int y);
    void advance(int step) override;

private:
    int x_;
    int y_;
    int type_;
};
} // namespace
#endif // ActorGUI_HH
