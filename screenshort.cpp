#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <windows.h>
#include <iostream>
#include <ctime>
#include <vector>

void SaveScreenshotAsJPG(const std::string& filename, HBITMAP hBitmap, int width, int height) {
    // ... (Same code as before) ...
}

int main() {
    // Get the handle to the desktop window
    HWND hDesktop = GetDesktopWindow();

    // Enumerate through all monitors
    std::vector<HMONITOR> monitors;
    EnumDisplayMonitors(NULL, NULL, [](HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData) -> BOOL {
        std::vector<HMONITOR>* monitorsPtr = reinterpret_cast<std::vector<HMONITOR>*>(dwData);
        monitorsPtr->push_back(hMonitor);
        return TRUE;
    }, reinterpret_cast<LPARAM>(&monitors));

    // Generate a timestamp for the filename
    std::time_t currentTime = std::time(nullptr);
    struct tm* localTime = std::localtime(&currentTime);
    char timestamp[20];
    std::strftime(timestamp, sizeof(timestamp), "%Y%m%d_%H%M%S", localTime);

    for (size_t i = 0; i < monitors.size(); ++i) {
        MONITORINFOEX monitorInfo;
        monitorInfo.cbSize = sizeof(MONITORINFOEX);
        GetMonitorInfo(monitors[i], &monitorInfo);

        int width = monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left;
        int height = monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top;

        HDC hdcScreen = GetDC(NULL);
        HDC hdcMonitor = CreateDC(NULL, monitorInfo.szDevice, NULL, NULL);
        HDC hdcMem = CreateCompatibleDC(hdcScreen);
        HBITMAP hBitmap = CreateCompatibleBitmap(hdcScreen, width, height);
        HBITMAP hBitmapOld = (HBITMAP)SelectObject(hdcMem, hBitmap);

        // Use BitBlt to capture the monitor content
        BitBlt(hdcMem, 0, 0, width, height, hdcMonitor, 0, 0, SRCCOPY);

        // Generate the filename with monitor information
        std::string monitorFileName = filename + "_monitor_" + std::to_string(i + 1) + ".jpg";

        // Save the screenshot
        SaveScreenshotAsJPG(monitorFileName, hBitmap, width, height);

        // Clean up
        SelectObject(hdcMem, hBitmapOld);
        DeleteObject(hBitmap);
        DeleteDC(hdcMem);
        DeleteDC(hdcMonitor);
        ReleaseDC(NULL, hdcScreen);
    }

    return 0;
}
