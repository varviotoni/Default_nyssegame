#include "player.hh"

namespace StudentSide{

Player::Player(Interface::Location start_loc):
    location_(start_loc)
{

}

Player::~Player()
{

}


Interface::Location Player::giveLocation() const
{
}

void Player::move(Interface::Location loc)
{
    location_ = loc;
}

bool Player::isRemoved() const
{
}

void Player::remove()
{
}
} // namespace
