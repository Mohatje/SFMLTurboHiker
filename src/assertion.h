#pragma once

#include <iostream>

#ifndef NDEBUG
#   define ASSERT(condition, message) \
    if (!(condition)) {                \
        std::cerr   << "Assertion " << #condition << " failed in " \
                    << __FILE__ << " line " << __LINE__ << ": " \
                    << message << std::endl; \
    }
#else
#   define ASSERT(condition, message) ;
#endif

void _assertMacro(const char* expr_str, bool expr, const char* file, int line, const char* msg) {
    if (!expr)
    {
        std::cerr << "Assert failed:\t" << msg << "\n"
                  << "Expected:\t" << expr_str << "\n"
                  << "Source:\t\t" << file << ", line " << line << "\n";
        abort();
    }
}