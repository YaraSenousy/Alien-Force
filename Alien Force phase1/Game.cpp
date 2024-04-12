#include "Game.h"
#include "string"

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
    //check that the file is opened successfully
    if (InputFile.is_open()) {
        int x;
        InputFile >> x;
        RandGen.setN(x);
        InputFile >> x;
        RandGen.setES(x);
        InputFile >> x;
        RandGen.setET(x);
        InputFile >> x;
        RandGen.setEG(x);
        InputFile >> x;
        RandGen.setAS(x);
        InputFile >> x;
        RandGen.setAM(x);
        InputFile >> x;
        RandGen.setAD(x);
        InputFile >> x;
        RandGen.setProb(x);
        string y;
        char z;
        int arr[12];
        for (int i{}; i < 12; i++) {
            while (InputFile >> z) {
                if (z == ' - ') break;
                y = y + z;
            }
            arr[i] = stoi(y);
        }
        RandGen.setEP(arr[0], arr[1]);
        RandGen.setEH(arr[2], arr[3]);
        RandGen.setEC(arr[4], arr[5]);
        RandGen.setAP(arr[6], arr[7]);
        RandGen.setAH(arr[8], arr[9]);
        RandGen.setAC(arr[10], arr[11]);
    }
}
