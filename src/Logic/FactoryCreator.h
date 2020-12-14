#pragma once
#include "AbstractFactory.h"
#include <string>

namespace turbohiker {

    class FactoryCreator {
    public:
        static std::unique_ptr<AbstractFactory> getFactory(const std::string &factoryName);

    public:
        FactoryCreator() = delete;
        FactoryCreator(const FactoryCreator& cpy) = delete;
        ~FactoryCreator() = delete;
    };

}

