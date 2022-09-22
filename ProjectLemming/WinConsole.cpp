#include "WinConsole.h"

WinConsole::WinConsole()
{
    hOutput = (HANDLE)GetStdHandle( STD_OUTPUT_HANDLE );
    hInput = (HANDLE)GetStdHandle( STD_INPUT_HANDLE );

    LONG_PTR new_style =  WS_OVERLAPPEDWINDOW | WS_HSCROLL | WS_VSCROLL;
    setConsoleWindowStyle(GWL_STYLE,new_style);
    
    CONSOLE_FONT_INFO font_info;
    if(GetCurrentConsoleFont(hOutput, TRUE, &font_info))
    {
        CONSOLE_SCREEN_BUFFER_INFO info;
        if(GetConsoleScreenBufferInfo(hOutput, &info)) {
            COORD coord;
            coord.X = font_info.dwFontSize.X;
            coord.Y = font_info.dwFontSize.Y;
            dwBufferSize = { coord.X,coord.Y };
            rcRegion = { 0, 0, coord.X-1, coord.Y-1 };
            
            buffer.resize(coord.Y, std::vector<CHAR_INFO>(coord.X));
            CHAR_INFO c;
            flat_vect.resize(coord.Y * coord.X, c);

            buffer[0][0].Char.AsciiChar = '!';
            buffer[coord.Y/2][coord.X/2].Char.AsciiChar = '!';
        
            SetConsoleScreenBufferSize(hOutput, coord);
        }
    }

    SetConsoleMode(hInput, fdwMode);
    FlushConsoleInputBuffer(hInput);
}

//Si le new style est à 0, la fenetre n'a absolument rien à part son contenu
LONG_PTR WinConsole::setConsoleWindowStyle(INT n_index,LONG_PTR new_style)
{
    /*The function does not clear the last error information. if last value was zero.*/
    SetLastError(NO_ERROR);        

    HWND hwnd_console = GetConsoleWindow();
    SetConsoleTitleA("The Lemmings");
    LONG_PTR style_ptr = SetWindowLongPtr(hwnd_console,n_index,new_style);
    SMALL_RECT rcRegion;
    SetConsoleWindowInfo(hwnd_console, 1, &rcRegion);

    
    // SetWindowPos(hwnd_console,0,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,SWP_NOMOVE|SWP_DRAWFRAME);

    //show window after updating
    ShowWindow(hwnd_console,SW_MAXIMIZE);

    return style_ptr;  
}
