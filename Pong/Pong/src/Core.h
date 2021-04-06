#pragma once
#include <iostream>
#define ASSERT(x, ...) if(!x) std::cout<<__VA_ARGS__<< "\n"; __debugbreak();
#define PRINT(x) std::cout<< x << "\n";