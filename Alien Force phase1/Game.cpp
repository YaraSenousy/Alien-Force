#include "Game.h"
#include "string"

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
    //open file in write mode
    ofstream OutputFile(filename);
    //write headers for the columns
    OutputFile << "Td  ID  Tj  Df  Dd  Db" << endl;
    //unit pointer to dequeue
    unit* dead = nullptr;
    //variables to calculate averages need in file
    int AVGEDf=0, AVGEDd=0, AVGEDb=0;
    int AVGADf=0, AVGADd=0, AVGADb=0;
    //loop on killed list, calculate sums needed for averages and write needed information in file
    while (KilledList.dequeue(dead)) {
        int Df, Dd, Db;
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
            AVGADf += Dd;
            AVGADf += Db;
        }
        //write to file in the correct format
        OutputFile << dead->getTimeDead() << "  ";
        OutputFile << dead->getID() << "  ";
        OutputFile << dead->getTimeJoined() << "  ";
        OutputFile << Df << "  ";
        OutputFile << Dd << "  ";
        OutputFile << Db <<endl;
    }
    //calculate total destructed earth units
    int totalEarthDestructed=ESK+ETK+EGK;
    //calculate averages for earth army
    if (totalEarthDestructed != 0) {
        AVGEDf /= totalEarthDestructed;
        AVGEDd /= totalEarthDestructed;
        AVGEDb /= totalEarthDestructed;
    }
    //total units of each type 
    int totalES, totalET, totalEG;
    totalES = ESK + earth_army.getESlist().getCount();
    totalET = ETK + earth_army.getETlist().getCount();
    totalEG = EGK + earth_army.getEGlist().getCount();
    //total of entire earth army
    int totalEarthUnits = totalES + totalET + totalEG;
    //output of statistics
    OutputFile << endl;
    OutputFile << "Battle result: " << result << endl;
    OutputFile << endl;
    OutputFile << "Earth army statistics"<<endl;
    OutputFile << "Total earth soliders: " << totalES << endl;
    OutputFile << "Total earth tanks: " << totalET << endl;
    OutputFile << "Total earth gunnery: " << totalEG << endl;
    OutputFile << "Percentage of destructed earth soliders relative to total soliders: " << (ESK / totalES) * 100 << "%" << endl;
    OutputFile << "Percentage of destructed earth tanks relative to total tanks: " << (ETK / totalET) * 100 << "%" << endl;
    OutputFile << "Percentage of destructed earth gunnery relative to total gunnery: " << (EGK / totalEG) * 100 <<"%"<< endl;
    OutputFile << "Percentage of total destructed units relative to total units: " << (totalEarthDestructed / totalEarthUnits) * 100 << "%" << endl;
    OutputFile << "Average Delay before first being shot: " << AVGEDf << endl;
    OutputFile << "Average time to destruction after first shot: " << AVGEDd << endl;
    OutputFile << "Average battle time: " << AVGEDb << endl;
    OutputFile << "Df/Db percentage" << (AVGEDf / AVGEDb) * 100 << endl;
    OutputFile << "Df/Db percentage" << (AVGEDd / AVGEDb) * 100 << endl;
    OutputFile << endl;

    //calculate total destructed alien units
    int totalAlienDestructed = ASK + ADK + AMK;
    //calculate averages for alien army
    if (totalAlienDestructed != 0) {
        AVGADf /= totalAlienDestructed;
        AVGADd /= totalAlienDestructed;
        AVGADb /= totalAlienDestructed;
    }
    //total units of each type 
    int totalAS, totalAD, totalAM;
    totalAS = ASK + alien_army.getASlist().getCount();
    totalAD = ADK + alien_army.getADlist().getCount();
    totalAM = AMK + alien_army.getAMlist().getCount();
    //total of entire alien army
    int totalAlienUnits = totalAS + totalAD + totalAM;
    //output of statistics
    OutputFile << "Alien army statistics" << endl;
    OutputFile << "Total alien soliders: " << totalAS << endl;
    OutputFile << "Total alien drones: " << totalAD << endl;
    OutputFile << "Total alien monsters: " << totalAM << endl;
    OutputFile << "Percentage of destructed alien soliders relative to total soliders: " << (ASK / totalAS) * 100 << "%" << endl;
    OutputFile << "Percentage of destructed alien drones relative to total drones: " << (ADK / totalAD) * 100 << "%" << endl;
    OutputFile << "Percentage of destructed alien monsters relative to total monsters: " << (AMK / totalEG) * 100 << "%" << endl;
    OutputFile << "Percentage of total destructed units relative to total units: " << (totalEarthDestructed / totalAlienUnits) * 100 << "%" << endl;
    OutputFile << "Average Delay before first being shot: " << AVGADf << endl;
    OutputFile << "Average time to destruction after first shot: " << AVGADd << endl;
    OutputFile << "Average battle time: " << AVGADb << endl;
    OutputFile << "Df/Db percentage" << (AVGADf / AVGADb) * 100 << endl;
    OutputFile << "Df/Db percentage" << (AVGADd / AVGADb) * 100 << endl;
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
    bool endgame = false;
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

    while (!endgame) {
        //generate earth and army unit
        RandGen.AssignGenerated(ts);
        LinkedQueue<unit*> es, et, eg; //lists of the alien units attacked by earth army
        //earth army attack alien army
        earth_army.earth_attack(es, et, eg, ts);
        LinkedQueue<unit*> as_attacked, ad_attacked, am_attacked; //lists of the earth units attacked by alien army
        int as, ad1,ad2, am; //ids of attacking alien units
        //alien army attack earth army
        alien_army.alien_attack(as, ad1, ad2, am, as_attacked, ad_attacked, am_attacked, ts);
        //check for a winner
        if (ts > 40) {
        }
        //increment the time step
        ts++;
    }
}
