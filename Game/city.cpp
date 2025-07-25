#include "city.hh"

city::city() {}


void city::setBackground(QImage &basicbackground, QImage &bigbackground)
{
}

void city::setClock(QTime clock)
{
}

void city::addStop(std::shared_ptr<Interface::IStop> stop)
{
}

void city::startGame()
{
}

void city::addActor(std::shared_ptr<Interface::IActor> newactor)
{
}

void city::removeActor(std::shared_ptr<Interface::IActor> actor)
{
}

void city::actorRemoved(std::shared_ptr<Interface::IActor> actor)
{
}

bool city::findActor(std::shared_ptr<Interface::IActor> actor) const
{
}

void city::actorMoved(std::shared_ptr<Interface::IActor> actor)
{
}

std::vector<std::shared_ptr<Interface::IActor> > city::getNearbyActors(Interface::Location loc) const
{
}

bool city::isGameOver() const
{
}
