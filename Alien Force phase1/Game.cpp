#include "Game.h"
#include "string"

Game::Game()
{
    RandGen.setGame(this);
}

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

void Game::print(int TS)
{
    cout << "Current Timestep " << TS << endl;
    //print alive earth units
    earth_army.print();
    cout << endl;
    //print alive alien units
    alien_army.print();
    cout << endl;
    cout << "============== Killed/Destructed Units =================" << endl;
    cout << KilledList.getCount() << " units";
    KilledList.print();
    cout << endl;
    cout << endl;
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
        //char z;
        //for (int i{}; i < 12; i++) {
        //    string y;
        //    while (InputFile >> z) {
        //        if (z == 45 || z == ' ') break;
        //        y = y + z;
        //    }
        //    arr[i] = stoi(y);
        //}

        //loop on the last lines
        string line;
        int index = 0;
        int arr[12];
        while (getline(InputFile, line)) {
            //creat a stream for each line
            istringstream linestream(line);
            string pair;
            //create a stream for each pair of numbers
            while (getline(linestream, pair, ' ')) {
                string min, max;
                istringstream pairstream(pair);
                //extract the first number by stopping when - is reached
                getline(pairstream, min, '-');
                //extract the second number by stopping at the end on the pair
                getline(pairstream, max);
                //convert the numbers from strings to integers and store it in an array
                arr[index++] = stoi(min);
                arr[index++] = stoi(max);
            }
        }
        //add the extracted ranges into their member data in randGen class
        RandGen.setEP(arr[0], arr[1]);
        RandGen.setEH(arr[2], arr[3]);
        RandGen.setEC(arr[4], arr[5]);
        RandGen.setAP(arr[6], arr[7]);
        RandGen.setAH(arr[8], arr[9]);
        RandGen.setAC(arr[10], arr[11]);

        //close the file
        InputFile.close();
    }
}
