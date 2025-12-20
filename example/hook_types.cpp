#include <iostream>
#include "hooking.h"

enum function_id : uint64_t
{
    DEAD_BEE,
};

uintptr_t func_address = 0x00DEADBEE;
using dead_bee_t = bool(*)(int a, int b);

bool my_dead_bee(dead_bee_t original, int a, int b)
{
    std::cout << "a < b = " <<  (a < b) << std::endl;
    return a < b;
}

int main()
{
    hooking h;

    // 1. Global function hook
    h.add_hook<DEAD_BEE>(func_address, my_dead_bee);

    // 2. Lambda Hook
    h.add_hook<DEAD_BEE>(func_address, [](dead_bee_t original, int a, int b){
        std::cout << "Hello from lambda" << std::endl;
        return original(a, b);
    });

    // 3. Callable hook
    class dead_bee_hook
    {
    public:
        bool operator()(dead_bee_t original, int a, int b)
        {
            std::cout << "Hello from callable" << std::endl;
            return original(a, b);
        }
    } dbh;

    h.add_hook<DEAD_BEE>(func_address, dbh);
}
