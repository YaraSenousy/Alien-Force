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
    //print alive earth units
    earth_army.print();
    //print alive alien units
    alien_army.print();
    cout << "============== Killed/Destructed Units =================" << endl;
    cout << KilledList.getCount() << " units";
    KilledList.print();
}

void Game::LoadFromFile(string filename)
{
    //open the file in read mode
    ifstream InputFile(filename);
    //check that the file is opened successfuly
    if (InputFile.is_open()) {

    }
}
