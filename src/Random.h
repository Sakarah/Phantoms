#ifndef RANDOM_H
#define RANDOM_H

#include <random>

class Random
{
public:
    static void initRandEngine();
    static int genUniformInt(int min, int max);
    static double genUniformFloat(double min = 0, double max = 1);
    static bool bernoulliTest(double proba = 0.5);
private:
    static std::default_random_engine _randEngine;
};

#endif // RANDOM_H
