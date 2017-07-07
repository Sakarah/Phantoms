#include "Random.h"
#include "resources/ReplayRecorder.h"
#include <ctime>

std::default_random_engine Random::_randEngine;

void Random::initRandEngine()
{
    time_t seed = std::time(nullptr);
    _randEngine.seed(seed);
}

int Random::genUniformInt(int min, int max)
{
    std::uniform_int_distribution<int> uniformDistrib(min, max);
    int randInt = uniformDistrib(_randEngine);
    ReplayRecorder::logValue(randInt);
    return randInt;
}

double Random::genUniformFloat(double min, double max)
{
    std::uniform_real_distribution<double> uniformDistrib(min, max);
    double randFloat = uniformDistrib(_randEngine);
    ReplayRecorder::logValue(randFloat);
    return randFloat;
}

bool Random::bernoulliTest(double proba)
{
    std::bernoulli_distribution bernouilliDistrib(proba);
    bool testSuccess = bernouilliDistrib(_randEngine);
    ReplayRecorder::logBool(testSuccess);
    return testSuccess;
}
