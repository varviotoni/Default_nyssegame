#ifndef PLAYER_HH
#define PLAYER_HH
#include "interfaces/iactor.hh"

namespace StudentSide{

class player : public Interface::IActor
{
public:
    player();

    // IActor interface
public:
    Interface::Location giveLocation() const override;
    void move(Interface::Location loc) override;
    bool isRemoved() const override;
    void remove() override;
};
} // namespace

#endif // PLAYER_HH
