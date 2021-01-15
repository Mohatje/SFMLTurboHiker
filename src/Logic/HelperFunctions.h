#pragma once

#include <ostream>

namespace turbohiker {
    class HelperFunctions {
    private:
        HelperFunctions() = default;
        HelperFunctions(const HelperFunctions& rhs) = default;
        ~HelperFunctions() = default;

    public:

        /**
         * Case insensitive comparison of strings
         * @param lhs first string
         * @param rhs second string
         * @return whether the strings are equal or not
         */
        static bool stringCompare(const std::string& lhs, const std::string& rhs);
    };

}