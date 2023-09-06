#ifndef __ASSERTAL_HPP__
#define __ASSERTAL_HPP__

#include <iostream> // cout, cerr
#include <cmath>    // fabs for floating-point comparison
#include <atomic>   // std::atomic for thread-safe counter

/*******************************************************************************************
Custom Assertion-like Mechanism

Example of usage:
int main()
{
    int a = 5;
    int b = 10;

    // Test case 1
    {
        TestEqual(6, a);
        TestLarger(b, a, "b should be larger than a");
    }

    // Test case 2
    {
        TestUnEqual(5, b);
        TestExpression(a == b, "a should be equal to b");
    }

    // Test case 3
    {
        double x = 0.1;
        double y = 0.2;
        TestClose(x + y, 0.3, 1e-5, "x + y should be close to 0.3");
    }

    SumTest(); // Call this at the end to summarize the test results

    return 0;
}
*********************************************************************************************/

std::atomic<size_t> g_failureCount(0);

#define TestEqual(expected, received, ...) \
    do { \
        if (expected != received) { \
            std::cerr << "TestEqual failed: " #expected " == " #received \
                      << " in file " << __FILE__ \
                      << " at line " << __LINE__  \
                      << "; " << "failure number: " << ++g_failureCount << "; " \
                      << "Expected: " << expected << ", Received: " << received \
                      << "; " << "Message: " << (__VA_ARGS__) << std::endl; \
        } \
    } while (false)

#define TestLarger(expected, received, ...) \
    do { \
        if (expected <= received) { \
            std::cerr << "TestLarger failed: " #expected " > " #received \
                      << " in file " << __FILE__ \
                      << " at line " << __LINE__  \
                      << "; " << "failure number: " << ++g_failureCount << "; " \
                      << "Expected: " << expected << ", Received: " << received \
                      << "; " << "Message: " << (__VA_ARGS__) << std::endl; \
        } \
    } while (false)

#define TestSmaller(expected, received, ...) \
    do { \
        if (expected >= received) { \
            std::cerr << "TestLarger failed: " #expected " > " #received \
                      << " in file " << __FILE__ \
                      << " at line " << __LINE__  \
                      << "; " << "failure number: " << ++g_failureCount << "; " \
                      << "Expected: " << expected << ", Received: " << received \
                      << "; " << "Message: " << (__VA_ARGS__) << std::endl; \
        } \
    } while (false)

#define TestUnEqual(expected, received, ...) \
    do { \
        if (expected == received) { \
            std::cerr << "TestUnEqual failed: " #expected " != " #received \
                      << " in file " << __FILE__ \
                      << " at line " << __LINE__  \
                      << "; " << "failure number: " << ++g_failureCount << "; " \
                      << "Expected: " << expected << ", Received: " << received \
                      << "; " << "Message: " << (__VA_ARGS__) << std::endl; \
        } \
    } while (false)

#define TestExpression(expression, ...) \
    do { \
        if (!(expression)) { \
            std::cerr << "TestExpression failed: " #expression \
                      << " in file " << __FILE__ \
                      << " at line " << __LINE__  \
                      << "; " << "failure number: " << ++g_failureCount << "; " \
                      << "Message: " << (__VA_ARGS__) << std::endl; \
        } \
    } while (false)

#define TestDouble(expected, received, epsilon, ...) \
    do { \
        if (std::fabs(expected - received) > epsilon) { \
            std::cerr << "TestClose failed: |" #expected " - " #received \
                      << "| <= " #epsilon << " not satisfied" \
                      << " in file " << __FILE__ \
                      << " at line " << __LINE__  \
                      << "; " << "failure number: " << ++g_failureCount << "; " \
                      << "Expected: " << expected << ", Received: " << received \
                      << ", Epsilon: " << epsilon \
                      << "; " << "Message: " << (__VA_ARGS__) << std::endl; \
        } \
    } while (false)

#define SumTest() \
    do { \
        if (g_failureCount == 0) { \
            std::cout << "All tests passed!" << std::endl; \
        } else { \
            std::cout << "Number of failed tests: " << g_failureCount << std::endl; \
        } \
    } while (false)

#endif /* __ASSERTAL_HPP__ */
