#ifndef ActorGUI_HH
#define ActorGUI_HH
#include "graphics/simpleactoritem.hh"
#include <QDebug>


namespace StudentSide
{
const int WIDTH = 30;
const int HEIGHT = 30;

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
    void setPassengers(int p);

private:
    int x_;
    int y_;
    const int type_;
    int num_passengers_;
};
} // namespace
#endif // ActorGUI_HH
