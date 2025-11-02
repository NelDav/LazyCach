#include "LazyCach/CachedEvaluation.h"
#include "LazyCach/CachedFunction.h"

#include <ctime>
#include <iostream>

long long calc (int a);

int main()
{
    // Example for LazyEval
    CachedEval val(&calc, 5);
    for (int i = 0; i<10; i++)
    {
        clock_t start = clock();
        std::cout << val() << "\n"; // val is only evaluated once.
        clock_t end = clock();
        std::cout << static_cast<float>(end - start) << "\n";
    }

    std::cout << "\n\n\n";

    // The benefit of LazyEval is that it is not evaluated in case it is not needed.
    CachedEval value1(&calc, 10);
    CachedEval<float, float> value2([](float f){ for(int i = 0; i<20000; ++i) f=f; return f; }, 5.4);
    for (int i = 0; i<10; i++)
    {
        if (true)
            std::cout << value2() << "\n"; // Value2 is evaluated only once.
        else
            std::cout << value1() << "\n"; // Value1 is never evaluated.
    }


    std::cout << "\n\n\n";


    // Example for CachedFunc
    CachedFunc func(&calc);
    for (int j = 0; j<10; j++)
    {
        for (int i = 0; i<10; i++)
        {
            clock_t start = clock();
            std::cout << func(5+j) << "\n"; // func is only evaluted if it wasn't evalued with same paramters before.
            clock_t end = clock();
            std::cout << static_cast<float>(end - start) << "\n";
        }
        std::cout << "Number of chaches:" << func.caches() << "\n";
    }
    return 0;
}

long long calc (int a)
{
    long long value = 1;

    for(int i = 0; i<900000000; i++) // Simulate slow function
    {
        int b = a;
        for(;b>0;--b)
            value *= a;
    }

    return value;
}
