#include <iostream>
#include <windows.h>
#include <fstream>
#include <chrono>

void logActivity(const std::string& appName, const std::string& url) {
    std::ofstream logFile("activity.log", std::ios_base::app);
    if (logFile.is_open()) {
        auto now = std::chrono::system_clock::now();
        std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

        logFile << "Activity Time: " << std::ctime(&currentTime);
        logFile << "App Name: " << appName << std::endl;
        logFile << "URL: " << url << std::endl;
        logFile << std::endl;
        logFile.close();
    }
}

int main() {
    while (true) {
        HWND foregroundWindow = GetForegroundWindow();
        char windowTitle[256];
        GetWindowText(foregroundWindow, windowTitle, sizeof(windowTitle));

        std::string appName = windowTitle; // Use window title as app name
        std::string url = "Your URL"; // Replace with actual URL if applicable

        logActivity(appName, url);

        Sleep(5000); // Sleep for 5 seconds (adjust the interval as needed)
    }

    return 0;
}
