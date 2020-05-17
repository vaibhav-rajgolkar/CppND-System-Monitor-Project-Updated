#include <ctime>
#include <sstream>

#include "format.h"

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
std::string Format::ElapsedTime(float seconds) 
{ 
    std::string day{};
    std::string month{};
    std::string day_num{}; 
    std::string uptime{};

    std::time_t time(seconds);
    std::string ctimestring{ctime(&time)};
    std::istringstream ctimestream(ctimestring);
    ctimestream >> day >> month >> day_num >> uptime;
    return uptime; 
}