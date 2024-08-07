#pragma once
#include <time.h>
#include <chrono>
#include "engine/utils/imexp.hpp"
#include "engine/utils/types.hpp"

namespace std
{
using namespace chrono;
using time_point = std::chrono::high_resolution_clock::time_point;
}

namespace bubble
{
class BUBBLE_ENGINE_EXPORT TimePoint
{
public:
    TimePoint() = default;
    // Time in seconds
    explicit TimePoint( f32 time );

    f32 Seconds();
    f32 Milliseconds();

private:
    f32 mTime = 0.0f;
};
typedef TimePoint DeltaTime;


class BUBBLE_ENGINE_EXPORT Timer
{
public:
    void OnUpdate();
    DeltaTime GetDeltaTime();

    // Time from the program start
    static TimePoint GetGlobalTime();
    static TimePoint GetGlobalStartTime();
    static DeltaTime GetFromStartTime();

private:
    static std::time_point Now();
    static std::time_point mGlobalStartTime;

    std::time_point mLastTime = Now();
    DeltaTime mDeltatime;
};

}
