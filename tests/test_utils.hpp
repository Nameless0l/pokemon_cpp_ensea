#pragma once

#include <cmath>
#include <iostream>
#include <string>

namespace testing
{
    inline int failures = 0;

    inline void check(bool condition, const std::string &label, const char *file, int line)
    {
        if (condition)
        {
            std::cerr << "  ok      " << label << std::endl;
        }
        else
        {
            failures++;
            std::cerr << "  ÉCHEC   " << label << "  (" << file << ":" << line << ")" << std::endl;
        }
    }

    // Deux double ne se comparent jamais avec == : on tolère un petit écart.
    inline bool almostEqual(double a, double b)
    {
        return std::fabs(a - b) < 0.000000001;
    }

    inline int report(const std::string &suiteName)
    {
        std::cerr << (failures == 0 ? "Tous les tests passent : " : "ÉCHECS dans : ")
                  << suiteName << std::endl;
        return failures == 0 ? 0 : 1;
    }
}

#define CHECK(condition) testing::check((condition), #condition, __FILE__, __LINE__)

#define CHECK_NEAR(a, b) testing::check(testing::almostEqual((a), (b)), #a " ~= " #b, __FILE__, __LINE__)

#define CHECK_THROWS(expression, ExceptionType)                                          \
    do                                                                                   \
    {                                                                                    \
        bool thrown = false;                                                             \
        try                                                                              \
        {                                                                                \
            expression;                                                                  \
        }                                                                                \
        catch (const ExceptionType &e)                                                   \
        {                                                                                \
            thrown = true;                                                               \
        }                                                                                \
        testing::check(thrown, #expression " lève " #ExceptionType, __FILE__, __LINE__); \
    } while (false)
