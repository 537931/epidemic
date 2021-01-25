# epidemic
A simple model of a community infection spread.

The model is based on the following assumptions:
1. On the day 1 there is at least one infected person in the population.
2. Each infected person can contact up to N people every day.
3. Infected person becomes contagious only on the next day after getting infected.
4. Infected person is contagious for a limited number of days.
5. After a certain amount of day a sick person either dies or acquires permanent immunity.
6. A sick person is not contagious after gaining immunity.

The following initial parameters can be adjusted in the code:
1. Population size.
2. Number of sick people on day 1.
3. Duration of illness.
3. Number of contacts a sick person can make per day.
4. Transmissivity rate.
5. Mortality rate.
