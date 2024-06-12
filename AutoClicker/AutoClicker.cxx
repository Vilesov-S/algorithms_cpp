#include <iostream>
#include <windows.h>
#include <thread>
#include <chrono>

int main()
{
    MessageBox(
        NULL, 
        "AutoClicker is running\n"
        "Right_ALT - start/pause\n"
        "END - to end the process",
        "Start AutoClicker", MB_OK | MB_ICONINFORMATION);
    
    bool alt_pressed = false;
    bool key_press = false;
    while (true)
    {
        if (!key_press && GetAsyncKeyState(VK_RMENU) & 0x8000)
        {
            alt_pressed = !alt_pressed;
        }
        else if (!key_press && GetAsyncKeyState(VK_END) & 0x8000)
        {
            break;
        }
        key_press = (GetAsyncKeyState(VK_RMENU) & 0x8000);
            
        if (alt_pressed)
        {
            mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    
    MessageBox(
        NULL, 
        "AutoClicker app has quit", 
        "End AutoClicker", 
        MB_OK | MB_ICONINFORMATION);

    return 0;
}