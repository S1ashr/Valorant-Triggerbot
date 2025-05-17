///// ******  ---- MADE BY S1ashr ---- ****** \\\\\


///// disc: s1ashr__
///// github: 

#include <Windows.h>
#include <iostream>

using namespace std;

bool isPurple(int red, int green, int blue) {
    return ((red >= 190 && green >= 100 && blue >= 200) ||
        (red >= 80 && red <= 100 && green >= 20 && green <= 30 && blue >= 100 && blue <= 110) ||
        (red >= 100 && red <= 190 && green >= 30 && green <= 90 && blue >= 110 && blue <= 200));
}

bool isYellow(int red, int green, int blue) {
    return ((red >= 170 && red <= 200 && green >= 165 && green <= 215 && blue >= 25 && blue <= 110) ||
        (red >= 145 && red <= 170 && green >= 140 && green <= 165 && blue >= 5 && blue <= 55) ||
        (red >= 200 && red <= 230 && green >= 200 && green <= 230 && blue >= 0 && blue <= 90) ||
        (red >= 230 && green >= 230 && blue >= 90 && blue <= 190));
}

void clickLeftMouse()
{
    INPUT input[2] = { 0 };
    input[0].type = INPUT_MOUSE;
    input[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    input[1].type = INPUT_MOUSE;
    input[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(2, input, sizeof(INPUT));
}

bool detectColors(int centerX, int centerY)
{
    HDC hdcScreen = GetDC(NULL);
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    if (centerX >= screenWidth || centerY >= screenHeight)
    {
        ReleaseDC(NULL, hdcScreen);
        return false;
    }

    COLORREF pixel = GetPixel(hdcScreen, centerX, centerY);
    int red = GetRValue(pixel);
    int green = GetGValue(pixel);
    int blue = GetBValue(pixel);

    ReleaseDC(NULL, hdcScreen);
    return isPurple(red, green, blue) || isYellow(red, green, blue);
}

int main() 
{
    int width, height;

    cout << "Enter your screen width: ";
    cin >> width;

    cout << "Enter your screen height: ";
    cin >> height;

    int centerX = width / 2;
    int centerY = height / 2;
    int actualWidth = GetSystemMetrics(SM_CXSCREEN);
    int actualHeight = GetSystemMetrics(SM_CYSCREEN);

    if (centerX >= actualWidth || centerY >= actualHeight)
    {
        cout << "Error: Center point exceeds actual screen dimensions!\n";
        return 1;
    }

    cout << "Monitoring center pixel (" << centerX << ", " << centerY << ")...\n";

    while (true)
    {
        if (detectColors(centerX, centerY)) {
            clickLeftMouse();
            Sleep(100); 
        }
        Sleep(10); 
    }
    return 0;
}