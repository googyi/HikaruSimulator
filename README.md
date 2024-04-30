# HikaruSimulator

Simple chess Monte Carlo simulator for winning streaks without draw handling

HikaruSimulator.exe <numberOfGames> <winningProbability>
HikaruSimulator.exe 2000 88

1 million rounds simulated, 1 round contains <numberOfGames> consecutive games.

Example output:

avg wins                = 1760.5
avg losses              = 239.502
avg win ratio           = 0.880249
avg 30+ win streaks     = 5.14693   (on average in every round 5 at least 30 long winning streaks are expected)
avg 45+ win streaks     = 0.753452  (on average in every round there is 75% chance to have a 45+ streak)
avg 55+ win streaks     = 0.209537
 
