#include "Game.h"

EarthArmy* Game::getEarthArmy()
{
    return &earth_army;
}

AlienArmy* Game::getAlienArmy()
{
    return &alien_army;
}

randGen* Game::getRandGen()
{
    return &RandGen;
}

void Game::print()
{
    earth_army.print();
    alien_army.print();
    cout << "============== Killed/Destructed Units =================" << endl;
    cout << KilledList.getCount() << " units";
    KilledList.print();
}
