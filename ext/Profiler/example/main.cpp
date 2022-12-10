#include <profiler/Profiler.hpp>
#include <thread>

void exampleFunction() {
    PROFILE_FUNCTION();
    int value = -1000000;
    for(int it = 0; it < 1000001; ++it)
        value += it;
}

void threadFunction() {
    PROFILE_FUNCTION();
    int value = -1000000;
    for(int it = 0; it < 1000001; ++it)
        value += it;
}

int main() {
    PROFILE_BEGIN("ProfilerLog", "example.json")
    {
        PROFILE_SCOPE("Example scope");
        exampleFunction();
    }
    {
        PROFILE_SCOPE("Thread scope");
        std::thread thread{threadFunction};
        if(thread.joinable())
            thread.join();
    }
    PROFILE_END();
    return 0;
}
