#ifndef PLAYER_HH
#define PLAYER_HH
#include "interfaces/iactor.hh"

namespace StudentSide{

class Player : public Interface::IActor
{
public:
    Player(Interface::Location start_loc);

    ~Player();

    // IActor interface
public:
    Interface::Location giveLocation() const override;
    void move(Interface::Location loc) override;
    bool isRemoved() const override;
    void remove() override;

private:
    Interface::Location location_;
};
} // namespace

#endif // PLAYER_HH
