#pragma once
#include <numeric>
#include <vector>

#include "windows.h"

class WinConsole
{
private:
    DWORD fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
    std::vector<CHAR_INFO> flat_vect;
    
public:
    HWND hwnd_console;
    HANDLE hOutput;
    HANDLE hInput;
    
    COORD dwBufferSize ;
    COORD dwBufferCoord = { 0, 0 };
    std::vector<std::vector<CHAR_INFO>> buffer;
    SMALL_RECT rcRegion;

    WinConsole();

    /**
     * \brief Allow to transform the 2D buffer array to a 1D array
     * \return Flattened buffer
     */
    CHAR_INFO* GetFlatBuffer();
    
};

inline CHAR_INFO* WinConsole::GetFlatBuffer()
{
    flat_vect =
            std::accumulate(buffer.begin(), buffer.end(),
                            std::vector<CHAR_INFO>(),
                            [](std::vector<CHAR_INFO>& a, std::vector<CHAR_INFO>& b) {
                                a.insert(a.end(), b.begin(), b.end());
                                return a;
                            });

    return flat_vect.data();
}
