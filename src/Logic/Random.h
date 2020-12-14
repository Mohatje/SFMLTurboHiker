#pragma once
#include <random>

namespace turbohiker {
    // Random number generator class
    class Random {
    public:

        /**
         * Static method to get the random class object, this is a unique object\n
         * @return random class object
         */
        static Random& getInstance();


        /**
         * Static method to return a random float number, between 0 and 1 by default\n
         * Additionally there are two other methods, namely randFloat(float min, float max) and randFloat(float max)\n
         *
         * @param min (optional) Specify the minimum value for the generator
         * @param max (optional) Specify the maximum value for the generator
         * @return a random float between the chosen (or not) min/max values.
         */
        static float randFloat();
        static float randFloat(float min, float max);
        static float randFloat(float max);
    private:

        Random(); // Use of a private constructor to prevent the construction of more than 1 instance

        Random(const Random& cpy);
        Random& operator=(const Random& rhs);
        ~Random() = default;

        std::mt19937& getGenerator();

        float _randFloat(float min = 0.f, float max = 1.f);

        std::random_device randomDevice;

        std::mt19937 randGenerator;

        std::uniform_real_distribution<> fDist;

    };

}

