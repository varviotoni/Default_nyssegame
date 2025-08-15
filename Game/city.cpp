#include "city.hh"
#include <QDebug>



namespace StudentSide{

City::City():
    gameclock_(),
    state_(1),
    actors_(),
    stops_()

{


}

City::~City()
{

}


void City::setBackground(QImage &basicbackground, QImage &bigbackground)
{
    background_ = basicbackground;
}

void City::setClock(QTime clock)
{
    if (clock.isValid())
    {
        gameclock_=clock;
    }
}

void City::addStop(std::shared_ptr<Interface::IStop> stop)
{
    stops_.push_back(stop);
}

void City::startGame()
{
    state_=1;
}

void City::addActor(std::shared_ptr<Interface::IActor> newactor)
{
    actors_.push_back(newactor);
}

void City::removeActor(std::shared_ptr<Interface::IActor> actor)
{
    actor->remove();
    actorRemoved(actor);
}

void City::actorRemoved(std::shared_ptr<Interface::IActor> actor)
{
    actors_.erase(std::find(actors_.begin(),actors_.end(),actor));
}

bool City::findActor(std::shared_ptr<Interface::IActor> actor) const
{
    if (std::find(actors_.begin(), actors_.end(), actor)!=actors_.end())
    {
        return true;
    }
    return false;
}

void City::actorMoved(std::shared_ptr<Interface::IActor> actor)
{
    // Not needed
}

std::vector<std::shared_ptr<Interface::IActor>> City::getNearbyActors(Interface::Location loc) const
{
    std::vector<std::shared_ptr<Interface::IActor>> nearby_actors = {};
    for( auto const  &actor : actors_) {
        if(actor->giveLocation().isClose(loc)){
            nearby_actors.push_back(actor);
        }
    }
    return nearby_actors;
}

bool City::isGameOver() const
{

    if(gameclock_>=GAME_END_TIME) {
        qDebug() << "GAME OVER";
        return true;
    }
    else {
        return false;
    }
}
const std::vector<std::shared_ptr<Interface::IActor>>& City::getActors() const
{
    return actors_;
}

const std::vector<std::shared_ptr<Interface::IStop>>& City::getStops() const
{
    return stops_;
}

void City::spawnPlayer(Interface::Location start_loc)
{
    StudentSide::Player* player = new StudentSide::Player(start_loc);
    player_ = std::shared_ptr<StudentSide::Player>(player);
}

void City::setup()
{
    spawnPlayer(PLAYER_START_LOC);
}

const std::shared_ptr<Player> &City::getPlayer() const
{
    return player_;
}

} // namespace
