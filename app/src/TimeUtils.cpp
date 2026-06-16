#include "TimeUtils.hpp"


#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>




// Makes the current time as text for example: "2024-06-01 12:34:56"
std::string getCurrentTimestamp()
{auto now = std::chrono::system_clock::now();

    std::time_t currentTime =
        std::chrono::system_clock::to_time_t(now);

    std::tm* localTime = std::localtime(&currentTime);

    std::ostringstream timestamp;

    timestamp << std::put_time(
        localTime,
        "%Y-%m-%d %H:%M:%S"
    );

    return timestamp.str();
}