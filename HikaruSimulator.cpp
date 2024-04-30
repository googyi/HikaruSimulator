// HikaruSimulator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <time.h>
#include <math.h>
#include <stdlib.h>

unsigned long long rounds = 1000000;
int numberOfGames;
double winProbality;

int* numberOfStreaks;

struct stats
{
    unsigned long long wins = 0;
    unsigned long long losses = 0;
    int streaks_30_54[55] = {};
    int streaks_30_plus = 0;
    int streaks_45_plus = 0;
    int streaks_55_plus = 0;
};

struct stats stats;

bool isWin()
{
    const int precision = 100;
    return rand() % precision < winProbality / 100.0 * precision;
}

void init()
{
    srand(time(0));
    numberOfStreaks = new int[numberOfGames + 1];
}

void cleanup()
{
    delete[] numberOfStreaks;
}

void cleanStreaks()
{
    for (int i = 0; i < numberOfGames; ++i)
        numberOfStreaks[i] = 0;
}

void collectStreakStats()
{
    for (int i = 30; i <= numberOfGames; ++i)
    {
        stats.streaks_30_plus += numberOfStreaks[i];
    }

    for (int i = 45; i <= numberOfGames; ++i)
    {
        stats.streaks_45_plus += numberOfStreaks[i];
    }

    for (int i = 30; i <= 54; ++i)
    {
        stats.streaks_30_54[i] += numberOfStreaks[i];
    }

    for (int i = 55; i < numberOfGames; ++i)
    {
        stats.streaks_55_plus += numberOfStreaks[i];
    }
}

void printStats(unsigned long long roundsSoFar)
{
    std::cout << "avg wins                = " << (double)stats.wins / roundsSoFar << "\n";
    std::cout << "avg losses              = " << (double)stats.losses / roundsSoFar << "\n";
    std::cout << "avg win ratio           = " << (double)stats.wins/ (numberOfGames * roundsSoFar) << "\n";
    
    //for (int i = 30; i <= 54; ++i)
    //{
    //    std::cout << "avg " << i << " long win streaks = " << (double)stats.streaks_30_54[i] / roundsSoFar << "\n";
    //}
    //
    std::cout << "avg 30+ win streaks     = " << (double)stats.streaks_30_plus / roundsSoFar << "\n";
    std::cout << "avg 45+ win streaks     = " << (double)stats.streaks_45_plus / roundsSoFar << "\n";
    std::cout << "avg 55+ win streaks     = " << (double)stats.streaks_55_plus / roundsSoFar << "\n";
}

void run()
{
    cleanStreaks();
    int wonGames = 0;
    int lostGames = 0;   

    int winCounter = 0;
    int bestStreak = 0;
    for (int i = 0; i < numberOfGames; ++i) 
    {
        if (isWin())
        {
            ++wonGames;
            ++winCounter;
        }
        else
        {
            ++lostGames;

            if (winCounter > 0)
                numberOfStreaks[winCounter]++;

            bestStreak = std::max(bestStreak, winCounter);
            winCounter = 0;
        }
    }

    stats.losses += lostGames;
    stats.wins += wonGames;

    collectStreakStats();
}

void multiRun()
{
    for (unsigned long long i = 1; i <= rounds; ++i)
    {
        run();
        if (i % 10000 == 0)
        {
            std::cout << i << " rounds done \n";
            printStats(i);
        }
    }
}

int main(int argc, char** argv)
{
    if (argc <= 2)
    {
        std::cout << "Not enough params. Usage: \"HikaruSimulator.exe <numberOfGames> <winProbability>\"\n";
        return 1;
    }

    numberOfGames = atoi(argv[1]);
    winProbality = atof(argv[2]);

    init();
    multiRun();
    cleanup();

    return 0;
}