#pragma once
#include <chrono>

namespace bubble
{
namespace chrono
{
using namespace std::chrono;
}

using namespace std::chrono_literals;
using TimeStamp = chrono::high_resolution_clock;
using TimePoint = chrono::high_resolution_clock::time_point;

}
