#include <iostream>
#include <Windows.h>

// Function to get the current time
void getCurrentTime(SYSTEMTIME& st) {
    GetLocalTime(&st);
}

// Function to calculate the time difference in seconds
double calculateTimeDifference(const SYSTEMTIME& start, const SYSTEMTIME& end) {
    FILETIME ftStart, ftEnd;
    SystemTimeToFileTime(&start, &ftStart);
    SystemTimeToFileTime(&end, &ftEnd);

    ULARGE_INTEGER ulStart, ulEnd;
    ulStart.LowPart = ftStart.dwLowDateTime;
    ulStart.HighPart = ftStart.dwHighDateTime;
    ulEnd.LowPart = ftEnd.dwLowDateTime;
    ulEnd.HighPart = ftEnd.dwHighDateTime;

    return static_cast<double>(ulEnd.QuadPart - ulStart.QuadPart) / 10000000.0; // Convert to seconds
}

int main() {
    SYSTEMTIME arrivalTime, leaveTime;
    double productiveTime = 0.0;
    double deskTime = 0.0;
    double timeAtWork = 0.0;
    double effectiveness = 0.0;
    double productivity = 0.0;

    std::cout << "Press Enter when you arrive at work: ";
    std::cin.ignore(); // Ignore any previous inputs and wait for Enter
    getCurrentTime(arrivalTime);

    std::cout << "Press Enter when you leave work: ";
    std::cin.ignore(); // Ignore any previous inputs and wait for Enter
    getCurrentTime(leaveTime);

    productiveTime = calculateTimeDifference(arrivalTime, leaveTime);
    
    // Here you can prompt the user to enter additional information
    // such as breaks, distractions, etc., and calculate deskTime accordingly.

    timeAtWork = productiveTime; // For simplicity, assuming no non-productive time

    std::cout << "Enter the number of tasks completed during this time: ";
    int tasksCompleted;
    std::cin >> tasksCompleted;
    if (tasksCompleted > 0) {
        effectiveness = tasksCompleted / timeAtWork;
    }

    std::cout << "Enter your productivity score (0.0 to 1.0): ";
    std::cin >> productivity;

    // Calculate other metrics if needed.

    // Display the results
    std::cout << "\nTime Tracker Results:\n";
    std::cout << "Arrival Time: " << arrivalTime.wHour << ":" << arrivalTime.wMinute << std::endl;
    std::cout << "Productive Time (in seconds): " << productiveTime << std::endl;
    std::cout << "Desk Time (in seconds): " << deskTime << std::endl;
    std::cout << "Time at Work (in seconds): " << timeAtWork << std::endl;
    std::cout << "Effectiveness: " << effectiveness << std::endl;
    std::cout << "Productivity: " << productivity << std::endl;

    return 0;
}
