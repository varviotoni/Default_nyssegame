#ifndef CITY_HH
#define CITY_HH
#include "interfaces/icity.hh"
#include "player.hh"
#include "QTime"

namespace StudentSide {

const QTime GAME_END_TIME = QTime(11, 10, 0);
// const Interface::Location PLAYER_START_LOC=
//     Interface::Location(6.82544e+06, 3.32823e+06);
const Interface::Location PLAYER_START_LOC=
    Interface::Location();

class City : public Interface::ICity
{
public:
    /**
      * @brief Default constructor of the interface (For documentation)
      * @post City is at initialization state.
      */
    City();

    /**
      * @brief Destructor
      */
    ~City();

    // ICity interface

    /**
     * @brief setBackground sets the bitmap picture of the game area.
     * @param basicbackground  Normal sized picture used as the game area. Bottom left position of the picture in pixelcoordinates can be found out using the offset()-method.
     * @param bigbackground  Background of the game that is bigger than normal. Used only if doing Scrolling map-expansion. Bottom left position of the picture in pixelcoordinates can be found out using the offset()-method.
     * @pre City is in init state.
     * @post Picture for the game area is set. Exception guarantee: basic.
     * @exception InitError Setting the picture was unsuccesful or the picture was invalid.
     */
    void setBackground(QImage &basicbackground, QImage &bigbackground) override;

    /**
     * @brief setClock sets the time of the game clock.
     * @param clock Game clock time at the function call.
     * @pre `kello.isValid() == true`.
     * @post Time is set. Exception guarantee: nothrow.
     */
    void setClock(QTime clock) override;

    /**
     * @brief addStop adds a stop to the city.
     * @param stop pointer to a stop object.
     * @pre City is in init state.
     * @post Stop is added to the city. Exception guarantee: basic
     * @exception InitError Stops position is not valid.
     */
    void addStop(std::shared_ptr<Interface::IStop> stop) override;

    /**
     * @brief startGame shofts city from init state to the gamestate.
     * @pre City is in init state. setBackground() and setClock() have been called.
     * @post City is in gamestate. Exception guarantee: nothrow.
     */
    void startGame() override;

    /**
     * @brief addActor adds a new actor to the city.
     * @param newactor actor to be added to the city that fulfills ActorIF.
     * @pre -
     * @post Actor is added to the city. Exception guarantee: basic.
     * @exception GameError Actor is already in the city.
     */
    void addActor(std::shared_ptr<Interface::IActor> newactor) override;

    /**
     * @brief removeActor removes the actor from the city.
     * @param actor Actor to be removed.
     * @pre City is in gamestate.
     * @post Actor is removed from the city. Exception guarantee: strong.
     * @exception GameError Actor not found in the city
     */
    void removeActor(std::shared_ptr<Interface::IActor> actor) override;

    /**
     * @brief actorRemoved tells the city that actor is removed ingame.
     * @param actor Actor that is set removed ingame.
     * @pre City is in gamestate. Given actor is found in the city. Actor has `actor.isRemoved() == true`.
     * @post Exception guarantee: strong.
     */
    void actorRemoved(std::shared_ptr<Interface::IActor> actor) override;

    /**
     * @brief findActor checks if the given actor is in the city.
     * @param actor Actor that that is looked for in the city.
     * @pre -
     * @return Boolean that tells wether the actor is in the city.
     * @post Exception guarantee: nothrow.
     */
    bool findActor(std::shared_ptr<Interface::IActor> actor) const override;

    /**
     * @brief actorMoved is an operation that is used to tell wether certain actor has moved.
     * @param actor Actor that has moved.
     * @pre City is in gamestate. Given actor is found in the city.
     * @post Exception guarantee: basic.
     */
    void actorMoved(std::shared_ptr<Interface::IActor> actor) override;

    /**
     * @brief getNearbyActors returns actors that are close to given position.
     * @param loc Location for getting the actors close to it.
     * @pre City is in gamestate.
     * @return Vector containing actors close to the location, that pass `getLocation().isClose(loc) == true`.
     * @post Exception guarantee: strong.
     */
    std::vector<std::shared_ptr<Interface::IActor> > getNearbyActors(Interface::Location loc) const override;

    /**
     * @brief isGameOver tells wether the game is overor not.
     * @pre City is in gamestate.
     * @return `true`, if game is over, else ´false´
     * @post Exception guarantee: nothrow.
     */
    bool isGameOver() const override;

    const std::vector<std::shared_ptr<Interface::IActor>>& getActors() const;

    const std::vector<std::shared_ptr<Interface::IStop>>& getStops() const;

    const std::shared_ptr<StudentSide::Player>& getPlayer() const;

    void spawnPlayer(Interface::Location start_loc);

    // initialize city ready to be handed over to logic
    void setup();

    QImage background_;
    QTime gameclock_;
    int state_;

private:
    std::vector<std::shared_ptr<Interface::IActor>> actors_;
    std::vector<std::shared_ptr<Interface::IStop>> stops_;
    std::shared_ptr<StudentSide::Player> player_;
};

}
#endif // CITY_HH
