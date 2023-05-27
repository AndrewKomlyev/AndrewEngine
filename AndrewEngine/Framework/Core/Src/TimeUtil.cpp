#include "Precompiled.h"
#include "../Inc/TimeUtil.h"

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;

float AndrewEngine::Core::TimeUtil::GetTime()
{
    //Gets the difference since the start
    static const auto startTime = high_resolution_clock::now();
    const auto currentTime = high_resolution_clock::now();
    const auto milliseconds = duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();
    return milliseconds / 1000.0f;
}

float AndrewEngine::Core::TimeUtil::GetDeltaTime()
{
    //Gets the difference since last check 
    static auto lastCallTime = high_resolution_clock::now();
    const auto currentTime = high_resolution_clock::now();
    const auto milliseconds = duration_cast<std::chrono::milliseconds>(currentTime - lastCallTime).count();
    lastCallTime = currentTime;
    return milliseconds / 1000.0f;
}