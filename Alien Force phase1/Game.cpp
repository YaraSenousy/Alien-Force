#include "Game.h"
#include "string"
#include <iostream>
#include <iomanip>
using namespace std;

Game::Game()
{
    RandGen.setGame(this);
    ESK = 0;
    ETK = 0;
    EGK = 0;
    ASK = 0;
    ADK = 0;
    AMK = 0;
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

void Game::print(int TS, int es, int et, int eg, int as, int ad1, int ad2, int am, LinkedQueue<unit*>& es_attacked, LinkedQueue<unit*>& et_attacked, LinkedQueue<unit*>& eg_attacked, LinkedQueue<unit*>& as_attacked, LinkedQueue<unit*>& ad_attacked, LinkedQueue<unit*>& am_attacked)
{
    cout << "Current Timestep " << TS << endl;
    //print alive earth units
    earth_army.print();
    cout << endl;
    //print alive alien units
    alien_army.print();
    cout << endl;
    //print fighting
    cout << "============== Units fighting at current step =================" << endl;
    if (es != 0) {
        cout << "ES " << es << " shots ";
        es_attacked.print();
        cout << endl;
    }
    if (et != 0) {
        cout << "ET " << et << " shots ";
        et_attacked.print();
        cout << endl;
    }
    if (eg != 0) {
        cout << "EG " << eg << " shots ";
        eg_attacked.print();
        cout << endl;
    }
    if (as != 0) {
        cout << "AS " << as << " shots ";
        as_attacked.print();
        cout << endl;
    }
    if (am != 0) {
        cout << "AM " << am << " shots ";
        am_attacked.print();
        cout << endl;
    }
    if (ad1 != 0) {
        cout << "AD " << ad1 << " & " << ad2 << " shots ";
        ad_attacked.print();
        cout << endl;
    }
    cout << endl;
    //print killed units
    cout << "============== Killed/Destructed Units =================" << endl;
    cout << KilledList.getCount() << " units ";
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

void Game::SaveToFile(string filename,string result)
{
    int width=10;
    int rightmargin = 3;
    //open file in write mode
    ofstream OutputFile(filename);
    //write headers for the columns
    OutputFile << setw(rightmargin)<<"Td";
    OutputFile << setw(width) << "ID";
    OutputFile << setw(width) << "Tj";
    OutputFile << setw(width) << "Df";
    OutputFile << setw(width) << "Dd";
    OutputFile << setw(width) << "Db" << endl;
    //unit pointer to dequeue
    unit* dead = nullptr;
    //variables to calculate averages need in file
    float AVGEDf=0, AVGEDd=0, AVGEDb=0;
    float AVGADf=0, AVGADd=0, AVGADb=0;
    //loop on killed list, calculate sums needed for averages and write needed information in file
    while (KilledList.dequeue(dead)) {
        float Df, Dd, Db;
        Df = dead->getTimeAttack() - dead->getTimeJoined();
        Dd = dead->getTimeDead() - dead->getTimeAttack();
        Db = Df + Dd;
        //check whether unit is of earth army or alien army
        if(dead->getID()<2000) {
            AVGEDf += Df;
            AVGEDd += Dd;
            AVGEDb += Db;
        }
        else {
            AVGADf += Df;
            AVGADd += Dd;
            AVGADb += Db;
        }
        //write to file in the correct format
        OutputFile <<setw(rightmargin)<<dead->getTimeDead();
        OutputFile <<setw(width)<<dead->getID();
        OutputFile <<setw(width)<<dead->getTimeJoined();
        OutputFile <<setw(width)<<Df;
        OutputFile <<setw(width) <<Dd;
        OutputFile <<setw(width) <<Db <<endl;
    }
    //calculate total destructed earth units
    float totalEarthDestructed=ESK+ETK+EGK;
    //calculate averages for earth army
    if (totalEarthDestructed != 0) {
        AVGEDf /= totalEarthDestructed;
        AVGEDd /= totalEarthDestructed;
        AVGEDb /= totalEarthDestructed;
    }
    else {
        AVGEDf = 0;
        AVGEDd = 0;
        AVGEDb = 0;
    }
    //total units of each type 
    float totalES, totalET, totalEG;
    totalES = ESK + earth_army.getESlist().getCount();
    totalET = ETK + earth_army.getETlist().getCount();
    totalEG = EGK + earth_army.getEGlist().getCount();
    //total of entire earth army
    float totalEarthUnits = totalES + totalET + totalEG;
    //output of statistics
    OutputFile << endl;
    OutputFile << "Battle result: " << result << endl;
    OutputFile << endl;
    OutputFile << "Earth army statistics"<<endl;
    OutputFile << "Total earth soliders: " << totalES << endl;
    OutputFile << "Total earth tanks: " << totalET << endl;
    OutputFile << "Total earth gunnery: " << totalEG << endl;
    OutputFile << "Percentage of destructed earth soliders relative to total soliders: ";
    if (totalES != 0) {
        OutputFile << (ESK / totalES) * 100 << "%" << endl;
    }
    else 
        OutputFile <<"0%" << endl;
    OutputFile << "Percentage of destructed earth tanks relative to total tanks: ";
    if (totalET != 0)
        OutputFile << (ETK / totalET) * 100 << "%" << endl;
    else
        OutputFile << "0%" << endl;
    OutputFile << "Percentage of destructed earth gunnery relative to total gunnery: ";
    if (totalEG != 0)
        OutputFile << (EGK / totalEG) * 100 << "%" << endl;
    else
        OutputFile << "0%" << endl;
    OutputFile << "Percentage of total destructed units relative to total units: ";
    if (totalEarthUnits != 0)
        OutputFile << (totalEarthDestructed / totalEarthUnits) * 100 << "%" << endl;
    else
        OutputFile << "0%" << endl;
    OutputFile << "Average Delay before first being shot: " << AVGEDf << endl;
    OutputFile << "Average time to destruction after first shot: " << AVGEDd << endl;
    OutputFile << "Average battle time: " << AVGEDb << endl;
    OutputFile << "Df/Db percentage: ";
    if (AVGEDb != 0)
        OutputFile << (AVGEDf / AVGEDb) * 100 << " %" << endl;
    else
        OutputFile << " 0%" << endl;
    OutputFile << "Dd/Db percentage: ";
    if (AVGEDb != 0)
        OutputFile << (AVGEDd / AVGEDb) * 100 << "%" << endl;
    else
        OutputFile << " 0%" << endl;
    OutputFile << endl;

    //calculate total destructed alien units
    float totalAlienDestructed = ASK + ADK + AMK;
    //calculate averages for alien army
    if (totalAlienDestructed != 0) {
        AVGADf /= totalAlienDestructed;
        AVGADd /= totalAlienDestructed;
        AVGADb /= totalAlienDestructed;
    }
    else {
        AVGADf = 0;
        AVGADd = 0;
        AVGADb = 0;
    }
    //total units of each type 
    float totalAS, totalAD, totalAM;
    totalAS = ASK + alien_army.getASlist().getCount();
    totalAD = ADK + alien_army.getADlist().getCount();
    totalAM = AMK + alien_army.getAMlist().getCount();
    //total of entire alien army
    float totalAlienUnits = totalAS + totalAD + totalAM;
    //output of statistics
    OutputFile << "Alien army statistics" << endl;
    OutputFile << "Total alien soliders: " << totalAS << endl;
    OutputFile << "Total alien drones: " << totalAD << endl;
    OutputFile << "Total alien monsters: " << totalAM << endl;
    OutputFile << "Percentage of destructed alien soliders relative to total soliders: ";
    if (totalAS != 0) {
        OutputFile << (ASK / totalAS) * 100 << "%" << endl;
    }
    else
        OutputFile << "0%" << endl;
    OutputFile << "Percentage of destructed alien drones relative to total drones: ";
    if (totalAD != 0)
        OutputFile << (ADK / totalAD) * 100 << "%" << endl;
    else
        OutputFile << "0%" << endl;
    OutputFile << "Percentage of destructed alien monsters relative to total monsters: ";
    if (totalAM != 0)
        OutputFile << (AMK / totalAM) * 100 << "%" << endl;
    else
        OutputFile << "0%" << endl;
    OutputFile << "Percentage of total destructed units relative to total units: ";
    if (totalAlienUnits != 0)
        OutputFile << (totalAlienDestructed / totalAlienUnits) * 100 << "%" << endl;
    else
        OutputFile << "0%" << endl;
    OutputFile << "Average Delay before first being shot: " << AVGADf << endl;
    OutputFile << "Average time to destruction after first shot: " << AVGADd << endl;
    OutputFile << "Average battle time: " << AVGADb << endl;
    OutputFile << "Df/Db percentage: ";
    if (AVGADb != 0)
        OutputFile << (AVGADf / AVGADb) * 100 << "%" << endl;
    else
        OutputFile << "0%" << endl;
    OutputFile << "Dd/Db percentage: ";
    if (AVGADb != 0)
        OutputFile << (AVGADd / AVGADb) * 100 << "%" << endl;
    else
        OutputFile << "0%" << endl;

    OutputFile << totalEarthUnits << endl;
    OutputFile << totalEarthDestructed << endl;
    OutputFile << totalAlienUnits << endl;
    OutputFile << totalAlienDestructed << endl;
}

bool Game::killed(unit* dead)
{
    if (!dead)
        return false;
    //adding the dead to the killed list
    KilledList.enqueue(dead);
    //incrementing the count of corresponding killed unit
    if (dead->getType() == "ES")
        ESK++;
    else if (dead->getType() == "ET")
        ETK++;
    else if (dead->getType() == "EG")
        EGK++;
    else if (dead->getType() == "AS")
        ASK++;
    else if (dead->getType() == "AD")
        ADK++;
    else
        AMK++;
    return true;
}

void Game::simulate()
{
    srand((int)time(0));
    LoadFromFile("input.txt");
    bool endgame = false; //indicates when the game ends
    string earth_status; //indicates who wins
    int ts = 1; //time step
    int interactive;
    cout << "Enter 1 for silent mode or 2 interactive mode" << endl;
    cin >> interactive;
    //validating the chosen mode
    while (interactive != 1 && interactive != 2) {
        cout << "invalid choice" << endl;
        cout << "Enter 1 for silent mode or 2 interactive mode" << endl;
        cin >> interactive;
    }
    //input a limit for the time steps
    int limit = 0;
    cout << "Enter a limit for the time steps, Must be greater than 40" << endl;
    cin >> limit;
    //validate the limit
    while (limit < 40) {
        cout << "Invalid limit" << endl;
        cout << "Enter a limit for the time steps, Must be greater than 40" << endl;
        cin >> limit;
    }
    //output of silent mode
    if (interactive == 1) {
        cout << "Silent Mode" << endl;
        cout << "Simulation Starts..." << endl;
    }

    while (!endgame) {
        //generate earth and army unit
        RandGen.AssignGenerated(ts);
        LinkedQueue<unit*> es_attacked, et_attacked, eg_attacked; //lists of the alien units attacked by earth army
        int es, et, eg; //ids of attacking earth units
        //earth army attack alien army
        earth_army.earth_attack(es, et, eg,es_attacked,et_attacked,eg_attacked, ts);
        LinkedQueue<unit*> as_attacked, ad_attacked, am_attacked; //lists of the earth units attacked by alien army
        int as, ad1,ad2, am; //ids of attacking alien units
        //alien army attack earth army
        alien_army.alien_attack(as, ad1, ad2, am, as_attacked, ad_attacked, am_attacked, ts);
        //check for winner if limit is reached or after 40 time steps
        if (ts == limit)
            earth_status = status(endgame,true);
        else if (ts >= 40) {
            earth_status = status(endgame,false);
        }
        //output of interactive mode
        if (interactive == 2) {
            print(ts, es, et, eg, as, ad1, ad2, am, es_attacked, et_attacked, eg_attacked, as_attacked, ad_attacked, am_attacked);
            cout << "Press Enter to continue..." << endl;
            cin.get();
        }
        //increment the time step
        ts++;
        
    }
    
    //creating output file
    SaveToFile("output.txt", earth_status);

    //rest of the output of silent mode
    if (interactive == 1) {
        cout << "Simulation ends, Output file is created" << endl;
    }
}

string Game::status(bool& endgame, bool limit_reached) //checks if earth won or lost
{
    int total_alien = alien_army.getASlist().getCount() + alien_army.getADlist().getCount() + alien_army.getAMlist().getCount();
    int total_earth = earth_army.getESlist().getCount() + earth_army.getETlist().getCount() + earth_army.getEGlist().getCount();
    if (limit_reached) {
        endgame = true; //if limit of time steps is reached end the game regardless of the numbers of units left
        if (total_alien < total_earth)
            return "Win";
        else if (total_alien > total_earth)
            return "Loss";
        else
            return "Draw";
    }
    else {
        if (total_alien == 0 && total_earth == 0) {
            endgame = true;
            return "Draw";
        }
        else if (total_alien == 0) {
            endgame = true;
            return "Win";
        }
        else if (total_earth == 0) {
            endgame = true;
            return "Loss";
        }
        else {
            endgame = false;
            return " ";
        }
    }
}
