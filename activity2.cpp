#include <iostream>
#include <windows.h>
#include <fstream>
#include <chrono>
#include <string>
#include <vector> // Add this line to include the vector header

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

std::string getChromeTabURL(HWND tabWindow) {
    const int bufferSize = 1024;
    char buffer[bufferSize] = {0};

    if (SendMessageA(tabWindow, WM_GETTEXT, bufferSize, reinterpret_cast<LPARAM>(buffer))) {
        return buffer;
    }

    return "Unknown URL";
}

int main() {
    while (true) {
        HWND foregroundWindow = GetForegroundWindow();
        char windowTitle[256];
        GetWindowText(foregroundWindow, windowTitle, sizeof(windowTitle));

        std::string appName = windowTitle; // Use window title as app name

        // Check if the active window is Chrome
        if (appName.find("Google Chrome") != std::string::npos) {
            std::vector<HWND> chromeTabWindows;
            HWND chromeWindow = FindWindowA("Chrome_WidgetWin_1", nullptr);
            while (chromeWindow) {
                chromeTabWindows.push_back(chromeWindow);
                chromeWindow = FindWindowExA(nullptr, chromeWindow, "Chrome_WidgetWin_0", nullptr);
            }

            for (HWND tabWindow : chromeTabWindows) {
                std::string chromeURL = getChromeTabURL(tabWindow);
                logActivity(appName, chromeURL);
            }
        }

        Sleep(5000); // Sleep for 5 seconds (adjust the interval as needed)
    }

    return 0;
}
