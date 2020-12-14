#include "Random.h"



namespace turbohiker {

    Random::Random() {
        std::mt19937 randomGen(randomDevice());
        randGenerator = randomGen;
    }

    Random& Random::getInstance() {
        static Random random_instance;
        return random_instance;
    }

    std::mt19937& Random::getGenerator() {
        return randGenerator;
    }

    float Random::_randFloat(float min, float max) {
        if (fDist.min() != min || fDist.max() != max)
            fDist = std::uniform_real_distribution<> (min, max);

        return fDist(getInstance().getGenerator());
    }

    float Random::randFloat() {
        return getInstance()._randFloat();
    }

    float Random::randFloat(float max) {
        return getInstance()._randFloat(0.f, max);
    }

    float Random::randFloat(float min, float max) {
        return getInstance()._randFloat(min, max);
    }

}